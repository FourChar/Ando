#ifndef ISURFACE_QUEUE
#define ISURFACE_QUEUE

#ifdef _MSC_VER
#pragma once
#endif

#include <mutex>
#include <queue>

#include "ISurfaceBasicRenderer.hpp"
#include "ISurfaceSlot.hpp"
#include "ISurfaceFont.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			namespace queue {
				class ISurfaceQueue : public ISurfaceBasicRenderer {
				private:
					std::mutex _mutex;
					std::queue<ISurfaceSlot*> queue;

				public:
					void processQueue(ISurfaceBasicRenderer *renderer);

					bool isQueueEmpty() const;

				public:
					virtual void DrawRawString(float x, float y, uint8_t size, bool centered, ando::Color color, ISurfaceFont *font, const char *string);
					virtual void DrawLine(float x1, float y1, float x2, float y2, ando::Color color);
					virtual void DrawRectangle(float x, float y, float width, float height, ando::Color color);
					virtual void FillRectangle(float x, float y, float width, float height, ando::Color color);
				};
			}
		}
	}
}

#endif // ISURFACE_QUEUE