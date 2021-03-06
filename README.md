# Ando Framework

## Overlay Example
```C++
auto overlay = new OVERLAY_RENDERER();

if (overlay->bindToWindow("Calculator")) {
    overlay->runThreaded();

    overlay->render([&overlay](std::shared_ptr<ando::overlay::surface::ISurfaceQueuedRenderer> renderer) {
        renderer->DrawLine(10, 10, 100, 10, ando::colors::purples::wisteria);

        renderer->DrawOutlinedLine(0, 0, overlay->getLocal().getWidth<>(), overlay->getLocal().getHeight<>(), ando::colors::red);
        renderer->DrawOutlinedLine(overlay->getLocal().getWidth<>(), 0, 0, overlay->getLocal().getHeight<>(), ando::colors::red);
        renderer->FillOutlinedRectangle(50, 50, 100, 100, ando::colors::reds::mexicanRed);

        renderer->DrawOutlinedString(55, 55, ando::colors::blues::blizzardBlue, "Arial", "Ando Overlay Arial");
        renderer->DrawOutlinedString(55, 75, ando::colors::blues::blizzardBlue, "Comic Sans MS", "Sean sucks!");
		
        /* Crosshair Example */
        ando::math::Rect<> crosshair;
        crosshair.setWidth(20.0f);
        crosshair.setHeight(20.0f);
        crosshair.setX((overlay->getTarget()->getWidth<>() / 2.f) - (crosshair.getWidth() / 2.f));
        crosshair.setY((overlay->getTarget()->getHeight<>() / 2.f) - (crosshair.getHeight() / 2.f));
		
        renderer->DrawOutlinedRectangle(crosshair.getX(), crosshair.getY(), crosshair.getWidth(), crosshair.getHeight(), ando::Color(ando::colors::white).setA(75));
        renderer->DrawLine(crosshair.getX(), crosshair.getY(), crosshair.getX() + crosshair.getWidth(), crosshair.getY() + crosshair.getHeight(), ando::Color(ando::colors::green).setA(220));
        renderer->DrawLine(crosshair.getX(), crosshair.getY() + crosshair.getHeight(), crosshair.getX() + crosshair.getWidth(), crosshair.getY(), ando::Color(ando::colors::green).setA(220));
    });
}
```

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

## Drawing Methods
The drawing methods you should be concerned with reside in `ando::overlay::surface::ISurfaceQueuedRenderer` and are as follows:

### Strings

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

### Lines

| Function Name    | Arguments |
| ---------------- | --------- |
| DrawLine         | `float x1`, `float y1`, `float x2`, `float y2`, `ando::Color color` |
| DrawOutlinedLine | `float x1`, `float y1`, `float x2`, `float y2`, `ando::Color color`, `ando::Color outlineColor = ando::colors::black` |

### Rectangles

| Function Name         | Arguments |
| --------------------- | --------- |
| DrawRectangle         | `float x`, `float y`, `float width`, `float height`, `ando::Color color` |
| DrawOutlinedRectangle | `float x`, `float y`, `float width`, `float height`, `ando::Color color`, `ando::Color outlineColor = ando::colors::black` |
| FillRectangle         | `float x`, `float y`, `float width`, `float height`, `ando::Color color` |
| FillOutlinedRectangle | `float x`, `float y`, `float width`, `float height`, `ando::Color color`, `ando::Color outlineColor = ando::colors::black` |

## Game Process Instance

### Defining the Instance

Create a seperate class for each process (game in this case):
{Inheriting the IBaseGameInstance class}
```C++
class CGlobalOffensiveInstance : public IBaseGameInstance<CGlobalOffensiveShared /*static shared data*/, CGlobalOffensiveBaseEntity> {
public:
	virtual ~CGlobalOffensiveInstance();
	
public:
	virtual bool worldToScreen(::ando::math::Vector3<float> from, ::ando::math::Vector2<float> &to) override;

protected:
	virtual void initialize() override;
	
	virtual void processUpdate() override;
}
```

Then create a custom base entity (probably the player's class):
{Inheriting the IBaseAndoEntity class}
```C++
class CGlobalOffensiveInstance;

class CGlobalOffensiveBaseEntity : public IBaseAndoEntity {
	friend CGlobalOffensiveInstance;
	
private:
	__int32 m_iHealth;
	__int32 m_iTeamNum;
	__int32 m_ArmorValue;
	
	::ando::math::Vector3<float> m_vecOrigin;
	
	bool m_bIsDefusing;
	
public:
	CGlobalOffensiveBaseEntity &operator(const CGlobalOffensiveBaseEntity &rhs) {
		this->m_iHealth = rhs.m_iHealth;
		this->m_iTeamNum = rhs.m_iTeamNum;
		this->m_ArmorValue = rhs.m_ArmorValue;
		
		this->m_vecOrigin = rhs.m_vecOrigin;
		
		this->m_bIsDefusing = rhs.m_bIsDefusing;
	}
	
	/*etc...*/
};
```

The Shared class is a simple means of sharing data between all the various functions:
```C++
class CGlobalOffensiveShared : public IBaseGameShared {
private:
	::ando::math::Matrix<float, 4, 4> viewMatrix;
	
public:
	CGlobalOffensiveShared();
	
public:
	::ando::math::Matrix<float, 4, 4> &getViewMatrix();
}
```

### Creating the Instance

You could either instantiate a new instance of that `CGlobalOffensiveInstance` class with the correct parameters or the overlay provides a convenient wrapper:
```C++
auto gameInstance = overlay->makeProcessInstance<ando::process_specific::CounterStrike::CGlobalOffensiveInstance>();

gameInstance->setShouldRunUpdater(true);

gameInstance->getShared()->getViewMatrix(); /*etc...*/
```