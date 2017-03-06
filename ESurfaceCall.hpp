#ifndef ESURFACE_CALL
#define ESURFACE_CALL

#ifdef _MSC_VER
#pragma once
#endif

namespace ando {
	namespace overlay {
		namespace surface {
			enum ESurfaceCall {
				DRAW_RAW_STRING,
				DRAW_LINE,
				DRAW_RECTANGLE,
				FILL_RECTANGLE
			};
		}
	}
}

#endif // ESURFACE_CALL