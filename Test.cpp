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
				static Rect<> crosshair;
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

				renderer.DrawOutlinedRectangle(crosshair.getX(), crosshair.getY(), crosshair.getWidth(), crosshair.getHeight(), ando::Color(ando::colors::white).setA(75));
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

						if (player.getScoreboardPlayer()->getHealth() != player.getHealth())
							break;

						auto distance = player.getOrigin().distanceTo(localPlayer.getOrigin());
						auto distancePercentage = 1.0f - (distance / 1600.0f) + 0.1f;
						if (distancePercentage > 0.65f)
							distancePercentage += 0.10f;

						if (distancePercentage < 0.30f)
							distancePercentage = 0.30f;
						if (distancePercentage > 1.0f)
							distancePercentage = 1.0f;

						if (distance > 2000.0f)
							distancePercentage = 0.1f;

						auto colorAlpha = static_cast<int>(255.0f * distancePercentage);

						auto color = ando::Color((localPlayer.getTeam() == player.getTeam()) ? ando::colors::blues::halfBaked : ando::colors::reds::tallPoppy).setA(colorAlpha);
						auto outlineColor = ando::Color(ando::colors::black).setA(colorAlpha);

						auto headBoneId = Bones::getBoneIdByName(Bones::terroristBones, "head");

						auto headCoordinates = player.getBoneManager().getBoneOrigin(headBoneId);

						/*for (auto it = skeletonBones.begin(); it != skeletonBones.end(); it++) {
							auto firstCoord = boneManager.getBoneOrigin(it->first.getId());
							auto secondCoord = boneManager.getBoneOrigin(it->second.getId());

							ando::math::Vector2<> firstPos;
							ando::math::Vector2<> secondPos;

							if (!gameInstance->worldToScreen(firstCoord, firstPos))
								break;
							if (!gameInstance->worldToScreen(secondCoord, secondPos))
								break;

							renderer.DrawOutlinedLine(firstPos.getX(), firstPos.getY(), secondPos.getX(), secondPos.getY(), color);
						}*/

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

										renderer.DrawOutlinedLine(currentPos.getX(), currentPos.getY(), nextPos.getX(), nextPos.getY(), color, outlineColor);
									}

									return true;
								})) {
									return false;
								}

								return true;
							});
						}

						Vector2<> originPos;
						if (!gameInstance->worldToScreen(player.getOrigin(), originPos))
							break;

						Vector2<> headPos;
						if (!gameInstance->worldToScreen(headCoordinates, headPos))
							break;

						auto healthPercentage = static_cast<float>(player.getScoreboardPlayer()->getHealth()) / 100.0f;
						auto nameXOffset = player.getScoreboardPlayer()->getName().length() * 5;

						renderer.DrawOutlinedRectangle(headPos.getX() - 2.0f, headPos.getY() - 2.0f, 4.0f, 4.0f, color, outlineColor);

						renderer.DrawOutlinedString(originPos.getX() - nameXOffset, originPos.getY() - 20, 13, false, color, outlineColor, "Verdana", "[%s]", player.getScoreboardPlayer()->getName().c_str());
						renderer.DrawProgressBar(originPos.getX() - 25.0f, originPos.getY(), 50.f, 2.f, healthPercentage, color, outlineColor);
						break;
					}

					case EClientClassID::CPlantedC4:
					case EClientClassID::CC4: {
						ando::math::Vector2<> originPos;
						if (!gameInstance->worldToScreen(entity.getOrigin(), originPos))
							break;

						renderer.DrawOutlinedRectangle(originPos.getX() - 10, originPos.getY() - 10 - 5, 20, 20, ando::colors::white);
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