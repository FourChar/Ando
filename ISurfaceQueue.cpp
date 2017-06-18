#include "ISurfaceQueue.hpp"

#include "ISurfaceSlotString.hpp"
#include "ISurfaceSlotLine.hpp"
#include "ISurfaceSlotRectangle.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			namespace queue {
				ISurfaceQueue::ISurfaceQueue(ando::overlay::surface::ISurfaceFontRenderer *renderer) {
					this->renderer = renderer;
				}

				void ISurfaceQueue::processQueue() {
					std::lock_guard<std::mutex> guard(this->_mutex);

					while (!this->queue.empty()) {
						auto next = this->queue.front();
						if (!next) {
							this->queue.pop();
							continue;
						}

						try {
							switch (next->getType()) {
							case ESurfaceCall::DRAW_RAW_STRING: {
								const ISurfaceSlotString *call = (const ISurfaceSlotString *)next;

								this->renderer->DrawRawString(call->getX(), call->getY(), call->getSize(), call->isCentered(), call->getColor(), call->getFont(), call->getText().c_str());
								break;
							}
							case ESurfaceCall::DRAW_LINE: {
								const ISurfaceSlotLine *call = (const ISurfaceSlotLine *)next;

								this->renderer->DrawLine(call->getX(), call->getY(), call->getX2(), call->getY2(), call->getColor());
								break;
							}
							case ESurfaceCall::DRAW_RECTANGLE: {
								const ISurfaceSlotRectangle *call = (const ISurfaceSlotRectangle *)next;

								this->renderer->DrawRectangle(call->getX(), call->getY(), call->getWidth(), call->getHeight(), call->getColor());
								break;
							}
							case ESurfaceCall::FILL_RECTANGLE: {
								const ISurfaceSlotRectangle *call = (const ISurfaceSlotRectangle *)next;

								this->renderer->FillRectangle(call->getX(), call->getY(), call->getWidth(), call->getHeight(), call->getColor());
								break;
							}
							}
						} catch(const ::std::exception e) { }

						this->queue.pop();

						delete next;
					}
				}

				void ISurfaceQueue::clear() {
					std::lock_guard<std::mutex> guard(this->_mutex);

					while (!this->queue.empty())
						this->queue.pop();
				}

				bool ISurfaceQueue::isQueueEmpty() {
					return this->queue.empty();
				}

				void ISurfaceQueue::DrawRawString(float x, float y, uint8_t size, bool centered, ando::Color color, ::std::shared_ptr<ISurfaceFont> font, const char *string) {
					auto newSlot = new ISurfaceSlotString();

					newSlot->setX(x);
					newSlot->setY(y);
					newSlot->setSize(size);
					newSlot->setCentered(centered);
					newSlot->setColor(color);
					newSlot->setFont(font);
					newSlot->setText(string);

					this->_mutex.lock();
					this->queue.push(newSlot);
					this->_mutex.unlock();
				}
				void ISurfaceQueue::DrawLine(float x1, float y1, float x2, float y2, ando::Color color) {
					auto newSlot = new ISurfaceSlotLine();

					newSlot->setX(x1);
					newSlot->setY(y1);
					newSlot->setX2(x2);
					newSlot->setY2(y2);
					newSlot->setColor(color);

					this->_mutex.lock();
					this->queue.push(newSlot);
					this->_mutex.unlock();
				}
				void ISurfaceQueue::DrawRectangle(float x, float y, float width, float height, ando::Color color) {
					auto newSlot = new ISurfaceSlotRectangle();

					newSlot->setX(x);
					newSlot->setY(y);
					newSlot->setWidth(width);
					newSlot->setHeight(height);
					newSlot->setColor(color);

					this->_mutex.lock();
					this->queue.push(newSlot);
					this->_mutex.unlock();
				}
				void ISurfaceQueue::FillRectangle(float x, float y, float width, float height, ando::Color color) {
					auto newSlot = new ISurfaceSlotRectangle(true);

					newSlot->setX(x);
					newSlot->setY(y);
					newSlot->setWidth(width);
					newSlot->setHeight(height);
					newSlot->setColor(color);

					this->_mutex.lock();
					this->queue.push(newSlot);
					this->_mutex.unlock();
				}
			}
		}
	}
}