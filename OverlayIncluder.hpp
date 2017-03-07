#ifndef OVERLAY_INCLUDER
#define OVERLAY_INCLUDER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef OVERLAY_RENDERER_NAME
#define OVERLAY_RENDERER_NAME               D2D
#endif

#define OVERLAY_RENDERER_CLASS_NAME(x)      x ## Overlay
#define OVERLAY_RENDERER_COMPLETE(x)        ando::overlay::concrete:: ## OVERLAY_RENDERER_CLASS_NAME(x)
#define OVERLAY_RENDERER                    OVERLAY_RENDERER_COMPLETE(OVERLAY_RENDERER_NAME)

#if(OVERLAY_RENDERER_NAME == D2D)
#include "D2DOverlay.hpp"
#elif(OVERLAY_RENDERER_NAME == DX9)
#include "DX9Overlay.hpp"
#elif(OVERLAY_RENDERER_NAME == DX10)
#include "DX10Overlay.hpp"
#elif(OVERLAY_RENDERER_NAME == DX11)
#include "DX11Overlay.hpp"
#elif(OVERLAY_RENDERER_NAME == DX12)
#include "DX12Overlay.hpp"
#elif(OVERLAY_RENDERER_NAME == GDI)
#include "GDIOverlay.hpp"
#elif(OVERLAY_RENDERER_NAME == OGL)
#include "OGLOverlay.hpp"
#endif

#endif // OVERLAY_INCLUDER