#ifndef ANDO_OVERLAY_WINDOW
#define ANDO_OVERLAY_WINDOW

#ifdef _MSC_VER
#pragma once
#endif

#include <memory>
#include <vector>
#include <mutex>

#include "Vector2.hpp"
#include "Rect.hpp"

#include "ISurfaceQueuedRenderer.hpp"

#define ANDO_WINDOW_TITLEBAR_HEIGHT		24
#define ANDO_WINDOW_BORDER_WIDTH		3

namespace ando {
	namespace overlay {
		namespace gui {
			enum EElementType {
				ELEMENT_LABEL,
				ELEMENT_BUTTON,
				ELEMENT_CHECKBOX,
				ELEMENT_RADIO,
				ELEMENT_SLIDER,
				ELEMENT_DROPDOWN,
				ELEMENT_TEXTBOX
			};

			class CWindowElement {
			private: // Variables
				EElementType type;
				::ando::math::Vector2<float> coordinates;
				bool updated;

			public:
				CWindowElement(EElementType type, ::ando::math::Vector2<float> coordinates) {
					this->type = type;
					this->coordinates = coordinates;
					this->updated = true;
				}
				CWindowElement(EElementType type, float x, float y) {
					this->type = type;
					this->coordinates.setX(x);
					this->coordinates.setY(y);
					this->updated = true;
				}
				~CWindowElement() {

				}

			public:
				const EElementType getType() const {
					return this->type;
				}
				const ::ando::math::Vector2<float> &getCoordinates() const {
					return this->coordinates;
				}
				const bool isUpdated() const {
					return this->updated;
				}

			public:
				void setCoordinates(::ando::math::Vector2<float> coordinates) {
					this->coordinates = coordinates;
				}
				void setUpdated(bool updated) {
					this->updated = updated;
				}
			};

			class CWindowText : public CWindowElement {
			private: // Variables
				::std::string text;

			public:
				CWindowText(EElementType type, ::ando::math::Vector2<float> coordinates, ::std::string text) : CWindowElement(type, coordinates) {
					this->text = text;
				}

			public:
				::std::string getText() const {
					return this->text;
				}

			public:
				void setText(::std::string text) {
					this->text = text;
					this->setUpdated(true);
				}
			};

			class CWindowLabel : public CWindowText {
			public:
				CWindowLabel(::ando::math::Vector2<float> coordinates, ::std::string text) : CWindowText(ELEMENT_LABEL, coordinates, text) {
				}
			};

			class CWindowButton : public CWindowText {
			private:
				::ando::math::Vector2<float> size;

			public:
				CWindowButton(::ando::math::Rect<float> rect, ::std::string text) : CWindowText(ELEMENT_BUTTON, ::ando::math::Vector2<float>(rect.getX(), rect.getY()), text) {
					this->size = ::ando::math::Vector2<float>(rect.getWidth(), rect.getHeight());
				}

			public:
				const ::ando::math::Vector2<float> &getSize() const {
					return this->size;
				}

			public:
				void setSize(::ando::math::Vector2<float> size) {
					this->size = size;
				}
			};

			class CWindow {
			private: // Variables
				::std::mutex _mutex;
				::std::string windowName;
				::ando::math::Rect<float> rect;

				::ando::Color backgroundColor;
				::ando::Color forgroundColor;
				::ando::Color borderColor;

				::std::vector<::std::shared_ptr<CWindowElement>> elements;

				::std::shared_ptr<::ando::overlay::surface::ISurfaceQueuedRenderer> queuedRenderer;

			public:
				CWindow(::std::shared_ptr<::ando::overlay::surface::ISurfaceQueuedRenderer> queuedRenderer,
					::std::string windowName,
					::ando::math::Rect<float> rect = ::ando::math::Rect<float>(50, 100, 300, 350),
					::ando::Color backgroundColor = ::ando::Color(252, 252, 252, 255),
					::ando::Color forgroundColor = ::ando::Color(220, 230, 244, 255),
					::ando::Color borderColor = ::ando::Color(136, 230, 74, 170)) {
					this->queuedRenderer = queuedRenderer;
					this->windowName = windowName;
					this->rect = rect;
					this->backgroundColor = backgroundColor;
					this->forgroundColor = forgroundColor;
					this->borderColor = borderColor;
				}
				~CWindow() {

				}

			public:
				::std::shared_ptr<CWindowElement> addElement(CWindowElement *element) {
					auto newElement = ::std::shared_ptr<CWindowElement>(element);

					this->_mutex.lock();
					this->elements.emplace_back(newElement);
					this->_mutex.unlock();

					return newElement;
				}

			private:
				bool renderWindow() {
					// Window
					this->getRenderer()->FillRectangle(
						this->getRect().getX(),
						this->getRect().getY(),
						this->getRect().getWidth(),
						ANDO_WINDOW_TITLEBAR_HEIGHT,
						this->getBorderColor());
					this->getRenderer()->FillRectangle(
						this->getRect().getX() + ANDO_WINDOW_BORDER_WIDTH,
						this->getRect().getY() + ANDO_WINDOW_TITLEBAR_HEIGHT,
						this->getRect().getWidth() - (ANDO_WINDOW_BORDER_WIDTH * 2),
						this->getRect().getHeight() - ANDO_WINDOW_TITLEBAR_HEIGHT - ANDO_WINDOW_BORDER_WIDTH,
						this->getForgroundColor());

					// Border
					this->getRenderer()->FillRectangle(
						this->getRect().getX(),
						this->getRect().getY() + ANDO_WINDOW_TITLEBAR_HEIGHT,
						ANDO_WINDOW_BORDER_WIDTH,
						this->getRect().getHeight() - ANDO_WINDOW_TITLEBAR_HEIGHT - ANDO_WINDOW_BORDER_WIDTH,
						this->getBorderColor()); // Left
					this->getRenderer()->FillRectangle(
						this->getRect().getX() + this->getRect().getWidth() - ANDO_WINDOW_BORDER_WIDTH,
						this->getRect().getY() + ANDO_WINDOW_TITLEBAR_HEIGHT,
						ANDO_WINDOW_BORDER_WIDTH,
						this->getRect().getHeight() - ANDO_WINDOW_TITLEBAR_HEIGHT - ANDO_WINDOW_BORDER_WIDTH,
						this->getBorderColor()); // Right
					this->getRenderer()->FillRectangle(
						this->getRect().getX(),
						this->getRect().getY() + this->getRect().getHeight() - ANDO_WINDOW_BORDER_WIDTH,
						this->getRect().getWidth(),
						ANDO_WINDOW_BORDER_WIDTH,
						this->getBorderColor()); // Bottom

					// Title
					this->getRenderer()->DrawOutlinedString(
						this->getRect().getX() + (ANDO_WINDOW_TITLEBAR_HEIGHT / 3),
						this->getRect().getY() + 1,
						this->getForgroundColor(),
						"Verdana", "%s", this->getWindowName().c_str());

					return true;
				}

			public:
				bool render() {
					::std::lock_guard<::std::mutex> lock(this->_mutex);

					if (!this->renderWindow())
						return false;

					for (auto it = this->getElements().begin(); it != this->getElements().end(); it++) {
						auto element = (*it);

						switch (element->getType()) {
							case ELEMENT_LABEL: {
								auto label = (CWindowLabel *)element.get();

								this->getRenderer()->DrawString(
									this->getRect().getX() + ANDO_WINDOW_BORDER_WIDTH + label->getCoordinates().getX(),
									this->getRect().getY() + ANDO_WINDOW_TITLEBAR_HEIGHT + label->getCoordinates().getY(),
									::ando::colors::black,
									"Verdana", "%s", label->getText().c_str());
								break;
							}
							case ELEMENT_BUTTON: {
								auto button = (CWindowButton *)element.get();

								this->getRenderer()->FillOutlinedRectangle(
									this->getRect().getX() + ANDO_WINDOW_BORDER_WIDTH + button->getCoordinates().getX(),
									this->getRect().getY() + ANDO_WINDOW_TITLEBAR_HEIGHT + button->getCoordinates().getY(),
									button->getSize().getX(),
									button->getSize().getY(),
									this->getBackgroundColor(),
									this->getBorderColor());
								this->getRenderer()->DrawString(
									this->getRect().getX() + ANDO_WINDOW_BORDER_WIDTH + button->getCoordinates().getX() + (button->getSize().getX() / 4),
									this->getRect().getY() + ANDO_WINDOW_TITLEBAR_HEIGHT + button->getCoordinates().getY() + (button->getSize().getY() / 2),
									this->getForgroundColor(),
									"Verdana", "%s", button->getText().c_str());
								break;
							}
							case ELEMENT_CHECKBOX: {
								break;
							}
							case ELEMENT_RADIO: {
								break;
							}
							case ELEMENT_SLIDER: {
								break;
							}
							case ELEMENT_DROPDOWN: {
								break;
							}
							case ELEMENT_TEXTBOX: {
								break;
							}
						}
					}

					return true;
				}

			protected:
				::std::string getWindowName() const {
					return this->windowName;
				}
				const ::ando::math::Rect<float> &getRect() const {
					return this->rect;
				}
				::ando::Color getBackgroundColor() const {
					return this->backgroundColor;
				}
				::ando::Color getForgroundColor() const {
					return this->forgroundColor;
				}
				::ando::Color getBorderColor() const {
					return this->borderColor;
				}
				const ::std::vector<::std::shared_ptr<CWindowElement>> &getElements() const {
					return this->elements;
				}
				const ::std::shared_ptr<::ando::overlay::surface::ISurfaceQueuedRenderer> &getRenderer() const {
					return this->queuedRenderer;
				}
			};
		}
	}
}

#endif // ANDO_OVERLAY_WINDOW