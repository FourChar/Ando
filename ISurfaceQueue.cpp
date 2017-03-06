#include "ISurfaceQueue.hpp"

#include "ISurfaceSlotString.hpp"
#include "ISurfaceSlotLine.hpp"
#include "ISurfaceSlotRectangle.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			namespace queue {
				void ISurfaceQueue::processQueue(ISurfaceBasicRenderer *renderer) {
					std::lock_guard<std::mutex> lock(this->_mutex);

					while (!this->queue.empty()) {
						const ISurfaceSlot *next = this->queue.front();
						if (next == nullptr) {
							this->queue.pop();
							continue;
						}

						switch (next->getType()) {
							case ESurfaceCall::DRAW_RAW_STRING: {
								const ISurfaceSlotString *call = (const ISurfaceSlotString *)next;

								renderer->DrawRawString(call->getX(), call->getY(), call->getSize(), call->isCentered(), call->getColor(), call->getFont(), call->getText().c_str());
								break;
							}
							case ESurfaceCall::DRAW_LINE: {
								const ISurfaceSlotLine *call = (const ISurfaceSlotLine *)next;

								renderer->DrawLine(call->getX(), call->getY(), call->getX2(), call->getY2(), call->getColor());
								break;
							}
							case ESurfaceCall::DRAW_RECTANGLE: {
								const ISurfaceSlotRectangle *call = (const ISurfaceSlotRectangle *)next;

								renderer->DrawRectangle(call->getX(), call->getY(), call->getWidth(), call->getHeight(), call->getColor());
								break;
							}
							case ESurfaceCall::FILL_RECTANGLE: {
								const ISurfaceSlotRectangle *call = (const ISurfaceSlotRectangle *)next;

								renderer->FillRectangle(call->getX(), call->getY(), call->getWidth(), call->getHeight(), call->getColor());
								break;
							}
						}

						delete next;
						this->queue.pop();
					}
				}

				bool ISurfaceQueue::isQueueEmpty() const {
					return this->queue.empty();
				}

				void ISurfaceQueue::DrawRawString(float x, float y, uint8_t size, bool centered, ando::Color color, ISurfaceFont *font, const char *string) {
					std::lock_guard<std::mutex> lock(this->_mutex);

					ISurfaceSlotString *newSlot = new ISurfaceSlotString();

					newSlot->setX(x);
					newSlot->setY(y);
					newSlot->setSize(size);
					newSlot->setCentered(centered);
					newSlot->setColor(color);
					newSlot->setFont(font);
					newSlot->setText(string);

					this->queue.push(newSlot);
				}
				void ISurfaceQueue::DrawLine(float x1, float y1, float x2, float y2, ando::Color color) {
					std::lock_guard<std::mutex> lock(this->_mutex);

					ISurfaceSlotLine *newSlot = new ISurfaceSlotLine();

					newSlot->setX(x1);
					newSlot->setY(y1);
					newSlot->setX2(x2);
					newSlot->setY2(y2);
					newSlot->setColor(color);

					this->queue.push(newSlot);
				}
				void ISurfaceQueue::DrawRectangle(float x, float y, float width, float height, ando::Color color) {
					std::lock_guard<std::mutex> lock(this->_mutex);

					ISurfaceSlotRectangle *newSlot = new ISurfaceSlotRectangle();

					newSlot->setX(x);
					newSlot->setY(y);
					newSlot->setWidth(width);
					newSlot->setHeight(height);
					newSlot->setColor(color);

					this->queue.push(newSlot);
				}
				void ISurfaceQueue::FillRectangle(float x, float y, float width, float height, ando::Color color) {
					std::lock_guard<std::mutex> lock(this->_mutex);

					ISurfaceSlotRectangle *newSlot = new ISurfaceSlotRectangle(true);

					newSlot->setX(x);
					newSlot->setY(y);
					newSlot->setWidth(width);
					newSlot->setHeight(height);
					newSlot->setColor(color);

					this->queue.push(newSlot);
				}
			}
		}
	}
}