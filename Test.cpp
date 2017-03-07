#define OVERLAY_RENDERER_NAME		D2D

#include <thread>

#include "OverlayIncluder.hpp"

int main(int argc, char *argv[]) {
	printf("Starting Overlay...\r\n");
	auto overlay = new OVERLAY_RENDERER();
	
	printf("Waiting for window...\r\n");
	overlay->waitForWindow("Calculator");
	
	printf("Creating overlay window...\r\n");
	if (overlay->createWindow()) {
		printf("Running overlay thread...\r\n");
		auto renderThread = overlay->runThreaded();

		printf("Waiting for overlay to close...\r\n");
		overlay->runExternal([&overlay](std::shared_ptr<ando::overlay::surface::ISurfaceQueuedRenderer> renderer) {
			renderer->DrawLine(10, 10, 20, 10, ando::colors::purples::wisteria);

			renderer->DrawOutlinedLine(0.f, 0.f, overlay->getLocal().getWidth<float>(), overlay->getLocal().getHeight<float>(), ando::colors::red);
			renderer->DrawOutlinedLine(overlay->getLocal().getWidth<float>(), 0.f, 0.f, overlay->getLocal().getHeight<float>(), ando::colors::red);
			renderer->FillOutlinedRectangle(50, 50, 100, 100, ando::colors::reds::mexicanRed);

			renderer->DrawOutlinedString(55, 55, ando::colors::blues::blizzardBlue, "Arial", "Sean sucks!");
			renderer->DrawOutlinedString(55, 75, ando::colors::blues::blizzardBlue, "Comic Sans MS", "Sean sucks!");
		});

		if(renderThread && renderThread->joinable())
			renderThread->join();
		printf("Overlay closed...\r\n");
	}
	
	return FALSE;
}