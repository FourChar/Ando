# Ando Framework

## Overlay Example
```C++
ando::overlay::Overlay *overlay = new ando::overlay::concrete::D2DOverlay();
	
overlay->waitForWindow("Calculator");

if (overlay->createWindow()) {
    std::thread runThread(std::bind(&ando::overlay::concrete::D2DOverlay::run, overlay));

    while (overlay->canRunExternaly()) {
        overlay->DrawOutlinedLine(0.f, 0.f, overlay->getLocal().getWidth<float>(), overlay->getLocal().getHeight<float>(), ando::colors::red);
        overlay->DrawOutlinedLine(overlay->getLocal().getWidth<float>(), 0.f, 0.f, overlay->getLocal().getHeight<float>(), ando::colors::red);
        overlay->FillOutlinedRectangle(50, 50, 500, 500, ando::Color(ando::colors::white).setA(200));

        overlay->DrawOutlinedString(55, 55, ando::colors::green, "Arial", "Sean sucks!");
    }
}```
