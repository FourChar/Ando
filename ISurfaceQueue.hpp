#ifndef ISURFACE_QUEUE
#define ISURFACE_QUEUE

#ifdef _MSC_VER
#pragma once
#endif

#include <mutex>
#include <queue>

#include "ISurfaceBasicRenderer.hpp"
#include "ISurfaceFontRenderer.hpp"
#include "ISurfaceSlot.hpp"
#include "ISurfaceFont.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			namespace queue {
				class ISurfaceQueue : public ando::overlay::surface::ISurfaceBasicRenderer {
				private:
					std::mutex _mutex;
					std::queue<ando::overlay::surface::queue::ISurfaceSlot *> queue;
					ando::overlay::surface::ISurfaceFontRenderer *renderer;

				public:
					ISurfaceQueue(ando::overlay::surface::ISurfaceFontRenderer *renderer);

				public:
					void processQueue();
					void clear();

					bool isQueueEmpty();

				public:
					virtual void DrawRawString(float x, float y, uint8_t size, bool centered, ando::Color color, ::std::shared_ptr<ando::overlay::surface::ISurfaceFont> font, const char *string);
					virtual void DrawLine(float x1, float y1, float x2, float y2, ando::Color color);
					virtual void DrawRectangle(float x, float y, float width, float height, ando::Color color);
					virtual void FillRectangle(float x, float y, float width, float height, ando::Color color);
				};
			}
		}
	}
}

#endif // ISURFACE_QUEUE