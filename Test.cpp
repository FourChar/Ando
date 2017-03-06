#include "D2DOverlay.hpp"

#include <windows.h>
#include <stdio.h>
#include <thread>
#include <iostream>

ando::overlay::Overlay *overlay = nullptr;

int main(int argc, char *argv[]) {
	printf("Starting Overlay...\r\n");
	fflush(stdout);
	
	printf("Creating Overlay Instance...\r\n");
	overlay = new ando::overlay::concrete::D2DOverlay();
	
	printf("Waiting for window...\r\n");
	overlay->waitForWindow("Ando (Running) - Microsoft Visual Studio");
	
	printf("Creating overlay window...\r\n");
	if (overlay->createWindow()) {
		printf("Running overlay thread...\r\n");
		std::thread runThread(std::bind(&ando::overlay::concrete::D2DOverlay::run, overlay));

		printf("Waiting for overlay to close...\r\n");
		while (overlay->canRunExternaly()) {
			overlay->DrawOutlinedLine(0.f, 0.f, overlay->getLocal().getWidth<float>(), overlay->getLocal().getHeight<float>(), ando::colors::red);
			overlay->DrawOutlinedLine(overlay->getLocal().getWidth<float>(), 0.f, 0.f, overlay->getLocal().getHeight<float>(), ando::colors::red);
			overlay->FillOutlinedRectangle(50, 50, 500, 500, ando::Color(ando::colors::white).setA(200));

			overlay->DrawOutlinedString(55, 55, ando::colors::green, "Arial", "Sean sucks!");
		}
	}

	std::cin.get();
	
	return FALSE;
}