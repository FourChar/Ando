#ifndef OVERLAY_INSTANCE_HPP
#define OVERLAY_INSTANCE_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <windows.h>
#include <string>

namespace ando {
	class OverlayInstance {
	private:
		std::string windowTitle;
		HWND hWnd;
		int x;
		int y;
		int width;
		int height;

	public:
		OverlayInstance();

		void setWindowTitle(std::string windowTitle);
		void setHwnd(HWND hWnd);

		std::string getWindowTitle() const;
		HWND getHwnd() const;

		// Getters
		template <typename R = int>
		R getX() {
			return static_cast<R>(this->x);
		}

		template <typename R = int>
		R getY() {
			return static_cast<R>(this->y);
		}

		template <typename R = int>
		R getWidth() {
			return static_cast<R>(this->width);
		}

		template <typename R = int>
		R getHeight() {
			return static_cast<R>(this->height);
		}

		// Setters
		template <typename R = int>
		void setX(R x) {
			this->x = static_cast<R>(x);
		}

		template <typename R = int>
		void setY(R y) {
			this->y = static_cast<R>(y);
		}

		template <typename R = int>
		void setWidth(R width) {
			this->width = static_cast<R>(width);
		}

		template <typename R = int>
		void setHeight(R height) {
			this->height = static_cast<R>(height);
		}
	};
}

#endif // OVERLAY_INSTANCE_HPP