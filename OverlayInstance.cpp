#include "OverlayInstance.hpp"

namespace ando {
	namespace overlay {
		OverlayInstance::OverlayInstance() {
			this->hWnd = NULL;
		}

		void OverlayInstance::setWindowTitle(std::string windowTitle) {
			this->windowTitle = windowTitle;
		}
		void OverlayInstance::setHwnd(HWND hWnd) {
			this->hWnd = hWnd;
		}

		std::string OverlayInstance::getWindowTitle() const {
			return this->windowTitle;
		}
		HWND OverlayInstance::getHwnd() const {
			return this->hWnd;
		}
	}
}