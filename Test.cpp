#define OVERLAY_RENDERER_NAME		D2D
#define OVERLAY_WINDOW_NAME			"Counter-Strike: Global Offensive"

#include "OverlayIncluder.hpp"
#include "IFileLogger.hpp"
#include "IProcessHandler.hpp"
#include "Rect.hpp"
#include "CGlobalOffensiveInstance.hpp"

auto fileLogger = ::std::make_shared<ando::logger::IFileLogger>("_Ando.log", ando::logger::ELogLevel::LOG_CRITICAL, true);

int main(int argc, char *argv[]) {
	auto overlay = new OVERLAY_RENDERER(fileLogger);
	
	if (overlay->bindToWindow(OVERLAY_WINDOW_NAME)) {
		auto processHandler = ::std::make_shared<ando::memory::IProcessHandler>(overlay->getTarget()->getHwnd());
		auto clientModule = processHandler->addModuleToLoad("client.dll");
		auto engineModule = processHandler->addModuleToLoad("engine.dll");
		processHandler->initialize();

		auto renderThread = overlay->runThreaded();

		auto gameInstance = ::std::make_unique<::ando::process_specific::CounterStrike::CGlobalOffensiveInstance>(fileLogger, processHandler, overlay->getTarget());
		gameInstance->setShouldRunUpdater(true);

		overlay->render([&overlay, &processHandler, &gameInstance](::std::shared_ptr<ando::overlay::surface::ISurfaceQueuedRenderer> renderer) {
			auto localPlayer = gameInstance->getShared()->getLocalPlayer();

			ando::math::Rect<float> crosshair;
			crosshair.setWidth(20.0f);
			crosshair.setHeight(20.0f);

			// Crosshair
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

			renderer->DrawOutlinedRectangle(crosshair.getX(), crosshair.getY(), crosshair.getWidth(), crosshair.getHeight(), ando::Color(ando::colors::white).setA(75));
			renderer->DrawLine(crosshair.getX(), crosshair.getY(), crosshair.getX() + crosshair.getWidth(), crosshair.getY() + crosshair.getHeight(), ando::Color(ando::colors::green).setA(220));
			renderer->DrawLine(crosshair.getX(), crosshair.getY() + crosshair.getHeight(), crosshair.getX() + crosshair.getWidth(), crosshair.getY(), ando::Color(ando::colors::green).setA(220));

			gameInstance->walkEntityList([&renderer, &localPlayer, &gameInstance]
				(::std::size_t index, ::ando::process_specific::CounterStrike::CGlobalOffensiveShared &shared, ::ando::process_specific::CounterStrike::CGlobalOffensiveBaseEntity &entity) {
				if (entity.getIndex() <= 64) { // Player Entities
					ando::Color color = (entity.getTeam() == localPlayer.getTeam()) ? ando::colors::green : ando::colors::red;

					::ando::math::Vector2<> screenOrigin;
					::ando::math::Vector2<> screenHead;

					if (!gameInstance->worldToScreen(entity.getOrigin(), screenOrigin))
						return true;
					if (!gameInstance->worldToScreen(entity.getEyeOrigin(), screenHead))
						return true;

					renderer->DrawOutlinedLine(screenOrigin.getX(), screenOrigin.getY(), screenHead.getX(), screenHead.getY(), color);

					renderer->DrawString(screenOrigin.getX() - 6, screenOrigin.getY() - 1, ando::colors::black, "Verdana", "[%i]", entity.getHealth());
					renderer->DrawString(screenOrigin.getX() - 5, screenOrigin.getY(), color, "Verdana", "[%i]", entity.getHealth());
				}
				else { // World Entities
					::ando::math::Vector2<> screenOrigin;
					if (!gameInstance->worldToScreen(entity.getOrigin(), screenOrigin))
						return true;

					renderer->DrawString(screenOrigin.getX() - 2, screenOrigin.getY() - 1, ando::colors::black, "Verdana", "[%i]", entity.getClassId());
					renderer->DrawString(screenOrigin.getX() - 1, screenOrigin.getY(), ando::colors::white, "Verdana", "[%i]", entity.getClassId());
				}

				return true;
			});
		});
	}
	
	return FALSE;
}