#include "GDIOverlay.hpp"

namespace ando {
	namespace overlay {
		namespace concrete {
			GDIOverlay::GDIOverlay() : Overlay() {
			}

			bool GDIOverlay::initialize() {
				return false;
			}

			bool GDIOverlay::BeginFrame() {
				return false;
			}
			bool GDIOverlay::RenderFrame() {
				return false;
			}
			bool GDIOverlay::EndFrame() {
				return false;
			}

			void GDIOverlay::onDestroy() {
				this->running = false;
			}
			void GDIOverlay::onReset() {
			}
			void GDIOverlay::onRelease() {
			}
			void GDIOverlay::onResize() {
			}

			bool GDIOverlay::FontInitializer(const ando::overlay::surface::ISurfaceFont *font) {
				return false;
			}

			void GDIOverlay::DrawRawString(float x, float y, float scale, bool centered, ando::Color color, ando::overlay::surface::ISurfaceFont *font, const char *format) {

			}
			void GDIOverlay::DrawLine(float x1, float y1, float x2, float y2, ando::Color color) {

			}
			void GDIOverlay::DrawRectangle(float x, float y, float width, float height, ando::Color color) {

			}
			void GDIOverlay::FillRectangle(float x, float y, float width, float height, ando::Color color) {

			}
		}
	}
}