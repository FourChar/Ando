#ifndef DX9_OVERLAY_HPP
#define DX9_OVERLAY_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <DXSDK/d3d9.h>
#include <DXSDK/d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "Overlay.hpp"

namespace ando {
	namespace overlay {
		namespace concrete {
			class DX9Overlay : public Overlay {
			private:
				D3DPRESENT_PARAMETERS presentParams;

				IDirect3D9Ex *object;
				IDirect3DDevice9Ex *renderDevice;

				ID3DXLine *line;

			public:
				DX9Overlay();

				virtual bool initialize();

				virtual bool BeginFrame();
				virtual bool RenderFrame();
				virtual bool EndFrame();

				virtual void onDestroy();
				virtual void onReset();
				virtual void onRelease();
				virtual void onResize();

				virtual bool FontInitializer(const ando::overlay::surface::ISurfaceFont *font);

				virtual void DrawRawString(float x, float y, float scale, bool centered, ando::Color color, ando::overlay::surface::ISurfaceFont *font, const char *string);
				virtual void DrawLine(float x1, float y1, float x2, float y2, ando::Color color);
				virtual void DrawRectangle(float x, float y, float width, float height, ando::Color color);
				virtual void FillRectangle(float x, float y, float width, float height, ando::Color color);
			};
		}
	}
}

#endif // DX9_OVERLAY_HPP