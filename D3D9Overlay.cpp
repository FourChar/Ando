#include "D3D9Overlay.hpp"
#include "Helpers.hpp"

namespace ando {
	namespace overlay {
		namespace concrete {
			D3D9Overlay::D3D9Overlay() : Overlay() { }

			bool D3D9Overlay::initialize() {
				if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &this->object)))
					return false;

				ZeroMemory(&this->presentParams, sizeof(D3DPRESENT_PARAMETERS));

				this->presentParams.Windowed = TRUE;
				this->presentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
				this->presentParams.hDeviceWindow = this->getLocal()->getHwnd();
				this->presentParams.MultiSampleType = D3DMULTISAMPLE_NONE;
				this->presentParams.MultiSampleQuality = D3DMULTISAMPLE_NONE;
				this->presentParams.BackBufferFormat = D3DFMT_A8R8G8B8;
				this->presentParams.BackBufferWidth = this->getLocal()->getWidth();
				this->presentParams.BackBufferHeight = this->getLocal()->getHeight();
				this->presentParams.EnableAutoDepthStencil = TRUE;
				this->presentParams.AutoDepthStencilFormat = D3DFMT_D16;
				this->presentParams.PresentationInterval = 0x80000000L;

				DWORD multiSampleQuality = 0;
				if (SUCCEEDED(this->object->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_A8R8G8B8, true, D3DMULTISAMPLE_NONMASKABLE, &multiSampleQuality))) {
					this->presentParams.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
					this->presentParams.MultiSampleQuality = multiSampleQuality - 1;
				}

				if (FAILED(this->object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->getLocal()->getHwnd(), D3DCREATE_HARDWARE_VERTEXPROCESSING, &this->presentParams, 0, &this->renderDevice))) {
					this->onDestroy();
					return false;
				}

				if (FAILED(D3DXCreateLine(this->renderDevice, &this->line))) {
					this->onDestroy();
					return false;
				}

				return true;
			}

			bool D3D9Overlay::BeginFrame() {
				printf("BeginFrame\r\n");
				if (FAILED(this->renderDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0)))
					return false;

				if (FAILED(this->renderDevice->BeginScene()))
					return false;

				return true;
			}
			bool D3D9Overlay::RenderFrame() {
				printf("RenderFrame\r\n");
				this->DrawLine(10, 10, 20, 20, ando::colors::green);
				this->DrawRectangle(this->getLocal()->getX() + 5.f, this->getLocal()->getY() + 5.f, 200.f, 200.f, ando::Color(0xFFFFFFFF));
				return true;
			}
			bool D3D9Overlay::EndFrame() {
				if (FAILED(this->renderDevice->EndScene()))
					return false;

				if (FAILED(this->renderDevice->PresentEx(0, 0, 0, 0, 0)))
					return false;

				printf("EndFrame\r\n");
				return true;
			}

			void D3D9Overlay::onDestroy() {
				this->setRunning(false);

				SafeRelease(&this->line);
				SafeRelease(&this->renderDevice);
				SafeRelease(&this->object);
			}
			void D3D9Overlay::onReset() {
				if (this->renderDevice)
					this->renderDevice->Reset(&this->presentParams);
				if (this->line)
					this->line->OnResetDevice();
			}
			void D3D9Overlay::onRelease() {
				if (this->line)
					this->line->OnLostDevice();
				if (this->renderDevice)
					this->renderDevice->Release();
			}
			void D3D9Overlay::onResize() {
				this->alignToTarget();
			}

			bool D3D9Overlay::FontInitializer(const ando::overlay::surface::ISurfaceFont *font) {
				return false;
			}

			void D3D9Overlay::DrawRawString(float x, float y, float scale, bool centered, ando::Color color, ando::overlay::surface::ISurfaceFont *font, const char *string) {

			}
			void D3D9Overlay::DrawLine(float x1, float y1, float x2, float y2, ando::Color color) {
				if (this->line->GetWidth() != 1)
					this->line->SetWidth(1);

				D3DXVECTOR2 coordinates[2];

				coordinates[0].x = x1;
				coordinates[0].y = y1;

				coordinates[1].x = x2;
				coordinates[1].y = y2;

				this->line->Draw(coordinates, sizeof(coordinates), color.rgba());
			}
			void D3D9Overlay::DrawRectangle(float x, float y, float width, float height, ando::Color color) {
			}
			void D3D9Overlay::FillRectangle(float x, float y, float width, float height, ando::Color color) {
				D3DRECT rect = { (long)x, (long)y, (long)(x + width), (long)(y + height) };

				this->renderDevice->Clear(1, &rect, D3DCLEAR_TARGET, color.rgba(), 1.0f, 0);
			}
		}
	}
}