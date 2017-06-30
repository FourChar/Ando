#define OVERLAY_RENDERER_NAME		D2D
#define OVERLAY_WINDOW_NAME			"Counter-Strike: Global Offensive"

#include "OverlayIncluder.hpp"
#include "IProcessHandler.hpp"
#include "CFileAnalyser.hpp"
#include "IFileLogger.hpp"
#include "Rect.hpp"

#include "CGlobalOffensiveBone.hpp"
#include "CGlobalOffensiveInstance.hpp"
#include "EGlobalOffensiveClientClassID.hpp"
#include "CGlobalOffensivePlayerEntity.hpp"
#include "CGlobalOffensiveSkeletonChain.hpp"

using namespace ando::process_specific::CounterStrike::GlobalOffensive;
using namespace ando::overlay::surface;
using namespace ando::memory;
using namespace ando::logger;
using namespace ando::math;
using namespace std;

auto fileLogger = make_shared<IFileLogger>("_Ando.log", ELogLevel::LOG_CRITICAL, true);

int main(int argc, char *argv[]) {
	auto overlay = new OVERLAY_RENDERER(fileLogger);
	
	if (overlay->bindToWindow(OVERLAY_WINDOW_NAME)) {
		auto processHandler = make_shared<CProcessHandler>(overlay->getTarget()->getHwnd());
		auto clientModule = processHandler->addModuleToLoad("client.dll");
		auto engineModule = processHandler->addModuleToLoad("engine.dll");
		processHandler->initialize();

		auto renderThread = overlay->runThreaded();

		auto gameInstance = make_unique<CInstance>(fileLogger, processHandler, overlay->getTarget());
		gameInstance->setShouldRunUpdater(true);

		overlay->render([&overlay, &processHandler, &gameInstance](ISurfaceQueuedRenderer &renderer) {
			auto localPlayer = gameInstance->getShared()->getLocalPlayer();

			// Crosshair
			{
				static Rect<float> crosshair;
				if (crosshair.getWidth() == 0.0f) {
					crosshair.setWidth(20.0f);
					crosshair.setHeight(20.0f);
				}

				if (localPlayer.getAimPunchAngle()) {
					Vector2<> difference(overlay->getTarget()->getWidth() / 90.0f, overlay->getTarget()->getHeight() / 90.0f);
					Vector2<> punch(overlay->getTarget()->getWidth() / 2.0f, overlay->getTarget()->getHeight() / 2.0f);

					punch[0] -= (difference[0] * localPlayer.getAimPunchAngle()[1]);
					punch[1] += (difference[1] * localPlayer.getAimPunchAngle()[0]);

					crosshair.setX(punch[0] - (crosshair.getWidth() / 2.0f));
					crosshair.setY(punch[1] - (crosshair.getHeight() / 2.0f));
				}
				else {
					crosshair.setX((overlay->getTarget()->getWidth<>() / 2.f) - (crosshair.getWidth() / 2.f));
					crosshair.setY((overlay->getTarget()->getHeight<>() / 2.f) - (crosshair.getHeight() / 2.f));
				}

				renderer.DrawOutlinedRectangle(crosshair, ando::Color(ando::colors::white).setA(75));
				renderer.DrawLine(crosshair.getX(), crosshair.getY(), crosshair.getX() + crosshair.getWidth(), crosshair.getY() + crosshair.getHeight(), ando::Color(ando::colors::green).setA(220));
				renderer.DrawLine(crosshair.getX(), crosshair.getY() + crosshair.getHeight(), crosshair.getX() + crosshair.getWidth(), crosshair.getY(), ando::Color(ando::colors::green).setA(220));
			}

			gameInstance->walkEntityList([&renderer, &gameInstance, &localPlayer]
			(size_t index, GameShared &shared, CBaseEntity &entity) {
				using Client::EClientClassID;

				switch(entity.getClassId()) {
					case EClientClassID::CCSPlayer: {
						auto player = static_cast<CPlayerEntity &>(entity);

						if (player.getIndex() == localPlayer.getIndex())
							break;

						// Out of Sync Check
						if (player.getScoreboardPlayer()->getHealth() != player.getHealth())
							break;

						int colorAlpha;

						{ // Distance Fade
							auto distance = player.getOrigin().distanceTo(localPlayer.getOrigin());
							auto distancePercentage = 1.0f - (distance / 1600.0f) + 0.1f;

							if (distancePercentage > 0.65f)
								distancePercentage += 0.10f;

							if (distancePercentage < 0.40f)
								distancePercentage = 0.40f;
							if (distancePercentage > 1.0f)
								distancePercentage = 1.0f;

							if (distance > 2000.0f)
								distancePercentage = 0.1f;

							colorAlpha = static_cast<int>(255.0f * distancePercentage);
						}

						auto color = ando::Color((localPlayer.getTeam() == player.getTeam()) ? ando::colors::blues::halfBaked : ando::colors::reds::tallPoppy).setA(colorAlpha);
						auto outlineColor = ando::Color(ando::colors::black).setA(colorAlpha);

						{ // Skeleton
							const Bones::CSkeletonChain *skeletonChain;
							if (player.getTeam() == 2)
								skeletonChain = &Bones::terroristSkeleton;
							else
								skeletonChain = &Bones::counterTerroristSkeleton;

							if (skeletonChain != nullptr) {
								skeletonChain->iterateStructures([&gameInstance, &player, &renderer, color, outlineColor](const Bones::CConsecutiveBoneStructure *currentStructure) {
									if (!currentStructure->iterateBones([&gameInstance, &player, &renderer, color, outlineColor](const ::std::size_t previous, const ::std::size_t current, const ::std::size_t next) {
										if ((current != -1) && (next != -1)) {
											Vector2<> currentPos;
											Vector2<> nextPos;

											auto currentOrigin = player.getBoneManager().getBoneOrigin(current);
											auto nextOrigin = player.getBoneManager().getBoneOrigin(next);

											if (!gameInstance->worldToScreen(currentOrigin, currentPos) || !gameInstance->worldToScreen(nextOrigin, nextPos))
												return false;

											renderer.DrawOutlinedLine(currentPos, nextPos, color, outlineColor);
										}

										return true;
									})) {
										return false;
									}

									return true;
								});
							}
						}

						Vector2<> originPos;
						if (!gameInstance->worldToScreen(player.getOrigin(), originPos))
							break;

						auto headCoordinates = player.getBoneManager().getBoneOrigin(Bones::getBoneIdByName(Bones::terroristBones, "head"));

						Vector2<> headPos;
						if (!gameInstance->worldToScreen(headCoordinates, headPos))
							break;

						auto healthPercentage = static_cast<float>(player.getScoreboardPlayer()->getHealth()) / 100.0f;
						auto armorPercentage = static_cast<float>(player.getScoreboardPlayer()->getArmor()) / 100.0f;

						auto armorColor = ando::Color(color)
							.setR(static_cast<uint8_t>(static_cast<float>(color.r()) / 2.0f))
							.setG(static_cast<uint8_t>(static_cast<float>(color.g()) / 2.0f));

						auto nameXOffset = static_cast<float>(player.getScoreboardPlayer()->getName().length() * 5);

						renderer.DrawOutlinedRectangle(headPos - Vector2<>(2, 2), Vector2<>(4, 4), color, outlineColor);
						renderer.DrawOutlinedString(originPos - Vector2<>(nameXOffset, 20), 13, false, color, outlineColor, "Verdana", "[%s]", player.getScoreboardPlayer()->getName().c_str());
						renderer.DrawProgressBar(originPos - Vector2<>(25, 0), Vector2<>(50, 2), healthPercentage, color, outlineColor);
						renderer.DrawProgressBar(originPos - Vector2<>(25, -4), Vector2<>(50, 2), armorPercentage, armorColor, outlineColor);
						break;
					}

					case EClientClassID::CPlantedC4:
					case EClientClassID::CC4: {
						Vector2<> originPos;
						if (!gameInstance->worldToScreen(entity.getOrigin(), originPos))
							break;

						renderer.DrawOutlinedRectangle(originPos - Vector2<>(10, 10 + 5), Vector2<>(20, 20), ando::colors::white);
						break;
					}
				}

				return true;
			});

			return true;
		});
	}
	
	return FALSE;
}