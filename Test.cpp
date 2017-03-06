#include "D2DOverlay.hpp"

#include <thread>

ando::overlay::Overlay *overlay = nullptr;

int main(int argc, char *argv[]) {
	printf("Starting Overlay...\r\n");
	overlay = new ando::overlay::concrete::D2DOverlay();
	
	printf("Waiting for window...\r\n");
	overlay->waitForWindow("Calculator");
	
	printf("Creating overlay window...\r\n");
	if (overlay->createWindow()) {
		printf("Running overlay thread...\r\n");
		std::thread runThread(std::bind(&ando::overlay::Overlay::run, overlay));

		printf("Waiting for overlay to close...\r\n");
		while (overlay->canRunExternaly()) {
			overlay->DrawOutlinedLine(0.f, 0.f, overlay->getLocal().getWidth<float>(), overlay->getLocal().getHeight<float>(), ando::colors::red);
			overlay->DrawOutlinedLine(overlay->getLocal().getWidth<float>(), 0.f, 0.f, overlay->getLocal().getHeight<float>(), ando::colors::red);
			overlay->FillOutlinedRectangle(50, 50, 100, 100, ando::colors::reds::mexicanRed);

			overlay->DrawOutlinedString(55, 55, ando::colors::blues::jellyBean, "Arial", "Sean sucks!");
		}
	}
	
	return FALSE;
}