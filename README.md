# Ando Framework

## Overlay Example
```C++
#define OVERLAY_RENDERER_NAME		D2D

#include "OverlayIncluder.hpp"

auto overlay = new OVERLAY_RENDERER();
	
overlay->waitForWindow("Calculator");

if (overlay->createWindow()) {
    auto renderThread = overlay->runThreaded();

	overlay->runExternal([&overlay](std::shared_ptr<ando::overlay::surface::ISurfaceQueuedRenderer> renderer) {
		renderer->DrawLine(10, 10, 100, 10, ando::colors::purples::wisteria);

		renderer->DrawOutlinedLine(0, 0, overlay->getLocal().getWidth(), overlay->getLocal().getHeight(), ando::colors::red);
		renderer->DrawOutlinedLine(overlay->getLocal().getWidth(), 0, 0, overlay->getLocal().getHeight(), ando::colors::red);
		renderer->FillOutlinedRectangle(50, 50, 100, 100, ando::colors::reds::mexicanRed);

		renderer->DrawOutlinedString(55, 55, ando::colors::blues::blizzardBlue, "Arial", "Ando Overlay Arial");
		renderer->DrawOutlinedString(55, 75, ando::colors::blues::blizzardBlue, "Comic Sans MS", "Sean sucks!");
	});
}
```
