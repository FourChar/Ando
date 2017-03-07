#include "DX9Overlay.hpp"
#include "Helpers.hpp"

namespace ando {
	namespace overlay {
		namespace concrete {
			DX9Overlay::DX9Overlay() : Overlay() { }

			bool DX9Overlay::initialize() {
				if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &this->object)))
					return false;

				ZeroMemory(&this->presentParams, sizeof(D3DPRESENT_PARAMETERS));

				this->presentParams.Windowed = TRUE;
				this->presentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
				this->presentParams.hDeviceWindow = this->localInstance.getHwnd();
				this->presentParams.MultiSampleType = D3DMULTISAMPLE_NONE;
				this->presentParams.MultiSampleQuality = D3DMULTISAMPLE_NONE;
				this->presentParams.BackBufferFormat = D3DFMT_A8R8G8B8;
				this->presentParams.BackBufferWidth = this->localInstance.getWidth();
				this->presentParams.BackBufferHeight = this->localInstance.getHeight();
				this->presentParams.EnableAutoDepthStencil = TRUE;
				this->presentParams.AutoDepthStencilFormat = D3DFMT_D16;
				this->presentParams.PresentationInterval = 0x80000000L;

				DWORD multiSampleQuality = 0;
				if (SUCCEEDED(this->object->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_A8R8G8B8, true, D3DMULTISAMPLE_NONMASKABLE, &multiSampleQuality))) {
					this->presentParams.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
					this->presentParams.MultiSampleQuality = multiSampleQuality - 1;
				}

				if (FAILED(this->object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->localInstance.getHwnd(), D3DCREATE_HARDWARE_VERTEXPROCESSING, &this->presentParams, 0, &this->renderDevice))) {
					this->onDestroy();
					return false;
				}

				if (FAILED(D3DXCreateLine(this->renderDevice, &this->line))) {
					this->onDestroy();
					return false;
				}

				return true;
			}

			bool DX9Overlay::BeginFrame() {
				printf("BeginFrame\r\n");
				if (FAILED(this->renderDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0)))
					return false;

				if (FAILED(this->renderDevice->BeginScene()))
					return false;

				return true;
			}
			bool DX9Overlay::RenderFrame() {
				printf("RenderFrame\r\n");
				this->DrawLine(10, 10, 20, 20, ando::colors::green);
				this->DrawRectangle(this->localInstance.getX() + 5.f, this->localInstance.getY() + 5.f, 200.f, 200.f, ando::Color(0xFFFFFFFF));
				return true;
			}
			bool DX9Overlay::EndFrame() {
				if (FAILED(this->renderDevice->EndScene()))
					return false;

				if (FAILED(this->renderDevice->PresentEx(0, 0, 0, 0, 0)))
					return false;

				printf("EndFrame\r\n");
				return true;
			}

			void DX9Overlay::onDestroy() {
				this->setRunning(false);

				SafeRelease(&this->line);
				SafeRelease(&this->renderDevice);
				SafeRelease(&this->object);
			}
			void DX9Overlay::onReset() {
				if (this->renderDevice)
					this->renderDevice->Reset(&this->presentParams);
				if (this->line)
					this->line->OnResetDevice();
			}
			void DX9Overlay::onRelease() {
				if (this->line)
					this->line->OnLostDevice();
				if (this->renderDevice)
					this->renderDevice->Release();
			}
			void DX9Overlay::onResize() {
				this->alignToTarget();
			}

			bool DX9Overlay::FontInitializer(const ando::overlay::surface::ISurfaceFont *font) {
				return false;
			}

			void DX9Overlay::DrawRawString(float x, float y, float scale, bool centered, ando::Color color, ando::overlay::surface::ISurfaceFont *font, const char *string) {

			}
			void DX9Overlay::DrawLine(float x1, float y1, float x2, float y2, ando::Color color) {
				if (this->line->GetWidth() != 1)
					this->line->SetWidth(1);

				D3DXVECTOR2 coordinates[2];

				coordinates[0].x = x1;
				coordinates[0].y = y1;

				coordinates[1].x = x2;
				coordinates[1].y = y2;

				this->line->Draw(coordinates, sizeof(coordinates), color.rgba());
			}
			void DX9Overlay::DrawRectangle(float x, float y, float width, float height, ando::Color color) {
			}
			void DX9Overlay::FillRectangle(float x, float y, float width, float height, ando::Color color) {
				D3DRECT rect = { (long)x, (long)y, (long)(x + width), (long)(y + height) };

				this->renderDevice->Clear(1, &rect, D3DCLEAR_TARGET, color.rgba(), 1.0f, 0);
			}
		}
	}
}