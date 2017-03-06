# Ando Framework

## Overlay Example
```C++
ando::overlay::Overlay *overlay = new ando::overlay::concrete::D2DOverlay();
	
overlay->waitForWindow("Calculator");

if (overlay->createWindow()) {
    std::thread runThread(std::bind(&ando::overlay::Overlay::run, overlay));

    while (overlay->canRunExternaly()) {
        overlay->DrawOutlinedLine(0, 0, overlay->getLocal().getWidth(), overlay->getLocal().getHeight(), ando::colors::red);
        overlay->DrawOutlinedLine(overlay->getLocal().getWidth(), 0, 0, overlay->getLocal().getHeight(), ando::colors::red);
        overlay->FillOutlinedRectangle(50, 50, 500, 500, ando::Color(ando::colors::white).setA(200));

        overlay->DrawOutlinedString(55, 55, ando::colors::green, "Arial", "Sean sucks!");
    }
}
```
