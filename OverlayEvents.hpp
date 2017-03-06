#ifndef OVERLAY_EVENTS_HPP
#define OVERLAY_EVENTS_HPP

#ifdef _MSC_VER
#pragma once
#endif

namespace ando {
	class OverlayEvents {
	protected:
		virtual void onDestroy() = 0;
		virtual void onReset() = 0;
		virtual void onRelease() = 0;
		virtual void onResize() = 0;
	};
}

#endif // OVERLAY_EVENTS_HPP