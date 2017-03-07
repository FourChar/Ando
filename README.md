# Ando Framework

## How to use OverlayIncluder.hpp
You'll first have to define `OVERLAY_RENDERER_NAME` with the shorthand of the renderer you'd like to use:
```C++
#define OVERLAY_RENDERER_NAME D2D
```
You've got a choice of any of the following:

| Shorthand | Renderer    | Implemented |
| --------- | ----------- | ----------- |
| `D2D`     | Direct2D    | **Yes**     |
| `D3D9`    | Direct3D 9  | *No*        |
| `D3D10`   | Direct3D 10 | *No*        |
| `D3D11`   | Direct3D 11 | *No*        |
| `D3D12`   | Direct3D 12 | *No*        |
| `OGL`     | OpenGL      | *No*        |
| `GDI`     | Windows GDI | *No*        |
*I plan to add all the above mentioned renderers...*

Next, simply include **OverlayIncluder.hpp**:
```C++
#include "OverlayIncluder.hpp"
```

The define `OVERLAY_RENDERER` will now contain the class name with the correct namespace behind it.
For example:
```C++
#define OVERLAY_RENDERER_NAME D2D
#include "OverlayIncluder.hpp"

auto overlayInstance = new OVERLAY_RENDERER();
// Same as:
// auto overlayInstance = new ando::overlay::concrete::D2DOverlay();
```

## Overlay Example
```C++
auto overlay = new OVERLAY_RENDERER();

if (overlay->bindToWindow("Calculator")) {
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

## Drawing Methods
The drawing methods you should be concerned with reside in `ando::overlay::surface::ISurfaceQueuedRenderer` and are as follows:

#### Strings

| Function Name      | Arguments |
| ------------------ | --------- |
| DrawRawString      | `float x`, `float y`, `uint8_t size`, `bool centered`, `ando::Color color`, `std::shared_ptr<ISurfaceFont> font`, `const char *string` |
| DrawString         | `float x`, `float y`, `ando::Color color`, `std::string fontName`, `const char *format`, `...` |
| DrawString         | `float x`, `float y`, `uint8_t size`, `bool centered`, `ando::Color color`, `std::string fontName`, `const char *format`, `...` |
| DrawOutlinedString | `float x`, `float y`, `uint8_t size`, `bool centered`, `ando::Color color`, `ando::Color outlineColor`, `std::string fontName`, `const char *format`, `...` |
| DrawOutlinedString | `float x`, `float y`, `uint8_t size`, `bool centered`, `ando::Color color`, `std::string fontName`, `const char *format`, `...` |
| DrawOutlinedString | `float x`, `float y`, `uint8_t size`, `ando::Color color`, `std::string fontName`, `const char *format`, `...` |
| DrawOutlinedString | `float x`, `float y`, `ando::Color color`, `ando::Color outlineColor`, `std::string fontName`, `const char *format`, `...` |
| DrawOutlinedString | `float x`, `float y`, `ando::Color color`, `std::string fontName`, `const char *format`, `...`

#### Lines

| Function Name    | Arguments |
| ---------------- | --------- |
| DrawLine         | `float x1`, `float y1`, `float x2`, `float y2`, `ando::Color color` |
| DrawOutlinedLine | `float x1`, `float y1`, `float x2`, `float y2`, `ando::Color color`, `ando::Color outlineColor = ando::colors::black` |

#### Rectangles

| Function Name         | Arguments |
| --------------------- | --------- |
| DrawRectangle         | `float x`, `float y`, `float width`, `float height`, `ando::Color color` |
| DrawOutlinedRectangle | `float x`, `float y`, `float width`, `float height`, `ando::Color color`, `ando::Color outlineColor = ando::colors::black` |
| FillRectangle         | `float x`, `float y`, `float width`, `float height`, `ando::Color color` |
| FillOutlinedRectangle | `float x`, `float y`, `float width`, `float height`, `ando::Color color`, `ando::Color outlineColor = ando::colors::black` |
