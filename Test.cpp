#define OVERLAY_RENDERER_NAME		D2D
#define OVERLAY_WINDOW_NAME			"Counter-Strike: Global Offensive"

#include "OverlayIncluder.hpp"
#include "IFileLogger.hpp"
#include "IProcessHandler.hpp"
#include "Rect.hpp"
#include "CGlobalOffensiveInstance.hpp"
#include "EGlobalOffensiveClientClassID.hpp"
#include "CFileAnalyser.hpp"

static const char *Ranks[ ] = 
{
	"-",
	"Silver I",
	"Silver II",
	"Silver III",
	"Silver IV",
	"Silver Elite",
	"Silver Elite Master",

	"Gold Nova I",
	"Gold Nova II",
	"Gold Nova III",
	"Gold Nova Master",
	"Master Guardian I",
	"Master Guardian II",

	"Master Guardian Elite",
	"Distinguished Master Guardian",
	"Legendary Eagle",
	"Legendary Eagle Master",
	"Supreme Master First Class",
	"The Global Elite"
};

auto fileLogger = ::std::make_shared<ando::logger::IFileLogger>("_Ando.log", ando::logger::ELogLevel::LOG_CRITICAL, true);

int main(int argc, char *argv[]) {
	auto overlay = new OVERLAY_RENDERER(fileLogger);
	
	if (overlay->bindToWindow(OVERLAY_WINDOW_NAME)) {
		auto processHandler = ::std::make_shared<ando::memory::CProcessHandler>(overlay->getTarget()->getHwnd());
		auto clientModule = processHandler->addModuleToLoad("client.dll");
		auto engineModule = processHandler->addModuleToLoad("engine.dll");
		processHandler->initialize();

		auto renderThread = overlay->runThreaded();

		auto gameInstance = ::std::make_unique<::ando::process_specific::CounterStrike::GlobalOffensive::CInstance>(fileLogger, processHandler, overlay->getTarget());
		gameInstance->setShouldRunUpdater(true);

		overlay->render([&overlay, &processHandler, &gameInstance](ando::overlay::surface::ISurfaceQueuedRenderer &renderer) {
			auto localPlayer = gameInstance->getShared()->getLocalPlayer();

			// Crosshair
			{
				static ando::math::Rect<float> crosshair;
				if (crosshair.getWidth() == 0.0f) {
					crosshair.setWidth(20.0f);
					crosshair.setHeight(20.0f);
				}

				if (localPlayer.getAimPunchAngle()) {
					ando::math::Vector2<> difference(overlay->getTarget()->getWidth() / 90.0f, overlay->getTarget()->getHeight() / 90.0f);
					ando::math::Vector2<> punch(overlay->getTarget()->getWidth() / 2.0f, overlay->getTarget()->getHeight() / 2.0f);

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

			/*{ // Scoreboard
				::std::size_t index = 0;

				::ando::process_specific::CounterStrike::GlobalOffensive::CScoreboardPlayer *scoreboardPlayer;
				::std::size_t validCount = 0;

				auto x = overlay->getTarget()->getWidth() - 500;
				auto y = 100;

				while ((scoreboardPlayer = gameInstance->getShared()->getPlayerResource().getScoreboardPlayer(index++)) != nullptr) {
					if (scoreboardPlayer->getTeam() != 2 && scoreboardPlayer->getTeam() != 3)
						continue;

					//renderer.DrawOutlinedString(x + 15, y + 25 + (validCount * 25), ando::colors::white, "Verdana", "%s", scoreboardPlayer->getName().c_str());
					renderer.DrawOutlinedString(x + 100, y + 25 + (validCount++ * 25), ando::colors::white, "Verdana", "Rank: [%s]", Ranks[scoreboardPlayer->getCompetitiveRank()]);
				}
			}*/

			gameInstance->walkEntityList([&renderer, &gameInstance, &localPlayer]
			(size_t index, ando::process_specific::CounterStrike::GlobalOffensive::GameShared &shared, ando::process_specific::CounterStrike::GlobalOffensive::CBaseEntity &entity) {
				using ando::process_specific::CounterStrike::GlobalOffensive::Client::EClientClassID;

				switch(entity.getClassId()) {
					case EClientClassID::CCSPlayer: {
						auto color = (localPlayer.getTeam() == entity.getTeam()) ? ando::colors::blues::halfBaked : ando::colors::reds::tallPoppy;

						ando::math::Vector2<> originPos;
						if (!gameInstance->worldToScreen(entity.getOrigin(), originPos))
							return true;

						renderer.DrawString(originPos.getX(), originPos.getY(), color, "Verdana", "[%i]", entity.getHealth());
						break;
					}

					case EClientClassID::CPlantedC4:
					case EClientClassID::CC4: {
						ando::math::Vector2<> originPos;
						if (!gameInstance->worldToScreen(entity.getOrigin(), originPos))
							return true;

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