#include <mruby.h>
#include "egl.h"

#include <EGL/egl.h>

struct RClass* mrb_egl_define_constants(mrb_state* mrb, struct RClass* outer)
{
	struct RClass* constants = mrb_define_module_under(mrb, outer, "Constants");

#ifdef EGL_VERSION_1_0
		mrb_define_const(mrb, constants, "EGL_VERSION_1_0", mrb_fixnum_value(EGL_VERSION_1_0));
#endif
#ifdef EGL_VERSION_1_1
		mrb_define_const(mrb, constants, "EGL_VERSION_1_1", mrb_fixnum_value(EGL_VERSION_1_1));
#endif
#ifdef EGL_VERSION_1_2
		mrb_define_const(mrb, constants, "EGL_VERSION_1_2", mrb_fixnum_value(EGL_VERSION_1_2));
#endif
#ifdef EGL_VERSION_1_3
		mrb_define_const(mrb, constants, "EGL_VERSION_1_3", mrb_fixnum_value(EGL_VERSION_1_3));
#endif
#ifdef EGL_VERSION_1_4
		mrb_define_const(mrb, constants, "EGL_VERSION_1_4", mrb_fixnum_value(EGL_VERSION_1_4));
#endif
#ifdef EGL_FALSE
		mrb_define_const(mrb, constants, "EGL_FALSE", mrb_fixnum_value(EGL_FALSE));
#endif
#ifdef EGL_TRUE
		mrb_define_const(mrb, constants, "EGL_TRUE", mrb_fixnum_value(EGL_TRUE));
#endif
#ifdef EGL_DEFAULT_DISPLAY
		mrb_define_const(mrb, constants, "EGL_DEFAULT_DISPLAY", mrb_cptr_value(mrb, EGL_DEFAULT_DISPLAY));
#endif
#ifdef EGL_NO_CONTEXT
		mrb_define_const(mrb, constants, "EGL_NO_CONTEXT", mrb_cptr_value(mrb, EGL_NO_CONTEXT));
#endif
#ifdef EGL_NO_DISPLAY
		mrb_define_const(mrb, constants, "EGL_NO_DISPLAY", mrb_cptr_value(mrb, EGL_NO_DISPLAY));
#endif
#ifdef EGL_NO_SURFACE
		mrb_define_const(mrb, constants, "EGL_NO_SURFACE", mrb_cptr_value(mrb, EGL_NO_SURFACE));
#endif
#ifdef EGL_DONT_CARE
		mrb_define_const(mrb, constants, "EGL_DONT_CARE", mrb_fixnum_value(EGL_DONT_CARE));
#endif
#ifdef EGL_SUCCESS
		mrb_define_const(mrb, constants, "EGL_SUCCESS", mrb_fixnum_value(EGL_SUCCESS));
#endif
#ifdef EGL_NOT_INITIALIZED
		mrb_define_const(mrb, constants, "EGL_NOT_INITIALIZED", mrb_fixnum_value(EGL_NOT_INITIALIZED));
#endif
#ifdef EGL_BAD_ACCESS
		mrb_define_const(mrb, constants, "EGL_BAD_ACCESS", mrb_fixnum_value(EGL_BAD_ACCESS));
#endif
#ifdef EGL_BAD_ALLOC
		mrb_define_const(mrb, constants, "EGL_BAD_ALLOC", mrb_fixnum_value(EGL_BAD_ALLOC));
#endif
#ifdef EGL_BAD_ATTRIBUTE
		mrb_define_const(mrb, constants, "EGL_BAD_ATTRIBUTE", mrb_fixnum_value(EGL_BAD_ATTRIBUTE));
#endif
#ifdef EGL_BAD_CONFIG
		mrb_define_const(mrb, constants, "EGL_BAD_CONFIG", mrb_fixnum_value(EGL_BAD_CONFIG));
#endif
#ifdef EGL_BAD_CONTEXT
		mrb_define_const(mrb, constants, "EGL_BAD_CONTEXT", mrb_fixnum_value(EGL_BAD_CONTEXT));
#endif
#ifdef EGL_BAD_CURRENT_SURFACE
		mrb_define_const(mrb, constants, "EGL_BAD_CURRENT_SURFACE", mrb_fixnum_value(EGL_BAD_CURRENT_SURFACE));
#endif
#ifdef EGL_BAD_DISPLAY
		mrb_define_const(mrb, constants, "EGL_BAD_DISPLAY", mrb_fixnum_value(EGL_BAD_DISPLAY));
#endif
#ifdef EGL_BAD_MATCH
		mrb_define_const(mrb, constants, "EGL_BAD_MATCH", mrb_fixnum_value(EGL_BAD_MATCH));
#endif
#ifdef EGL_BAD_NATIVE_PIXMAP
		mrb_define_const(mrb, constants, "EGL_BAD_NATIVE_PIXMAP", mrb_fixnum_value(EGL_BAD_NATIVE_PIXMAP));
#endif
#ifdef EGL_BAD_NATIVE_WINDOW
		mrb_define_const(mrb, constants, "EGL_BAD_NATIVE_WINDOW", mrb_fixnum_value(EGL_BAD_NATIVE_WINDOW));
#endif
#ifdef EGL_BAD_PARAMETER
		mrb_define_const(mrb, constants, "EGL_BAD_PARAMETER", mrb_fixnum_value(EGL_BAD_PARAMETER));
#endif
#ifdef EGL_BAD_SURFACE
		mrb_define_const(mrb, constants, "EGL_BAD_SURFACE", mrb_fixnum_value(EGL_BAD_SURFACE));
#endif
#ifdef EGL_CONTEXT_LOST
		mrb_define_const(mrb, constants, "EGL_CONTEXT_LOST", mrb_fixnum_value(EGL_CONTEXT_LOST));
#endif
#ifdef EGL_BUFFER_SIZE
		mrb_define_const(mrb, constants, "EGL_BUFFER_SIZE", mrb_fixnum_value(EGL_BUFFER_SIZE));
#endif
#ifdef EGL_ALPHA_SIZE
		mrb_define_const(mrb, constants, "EGL_ALPHA_SIZE", mrb_fixnum_value(EGL_ALPHA_SIZE));
#endif
#ifdef EGL_BLUE_SIZE
		mrb_define_const(mrb, constants, "EGL_BLUE_SIZE", mrb_fixnum_value(EGL_BLUE_SIZE));
#endif
#ifdef EGL_GREEN_SIZE
		mrb_define_const(mrb, constants, "EGL_GREEN_SIZE", mrb_fixnum_value(EGL_GREEN_SIZE));
#endif
#ifdef EGL_RED_SIZE
		mrb_define_const(mrb, constants, "EGL_RED_SIZE", mrb_fixnum_value(EGL_RED_SIZE));
#endif
#ifdef EGL_DEPTH_SIZE
		mrb_define_const(mrb, constants, "EGL_DEPTH_SIZE", mrb_fixnum_value(EGL_DEPTH_SIZE));
#endif
#ifdef EGL_STENCIL_SIZE
		mrb_define_const(mrb, constants, "EGL_STENCIL_SIZE", mrb_fixnum_value(EGL_STENCIL_SIZE));
#endif
#ifdef EGL_CONFIG_CAVEAT
		mrb_define_const(mrb, constants, "EGL_CONFIG_CAVEAT", mrb_fixnum_value(EGL_CONFIG_CAVEAT));
#endif
#ifdef EGL_CONFIG_ID
		mrb_define_const(mrb, constants, "EGL_CONFIG_ID", mrb_fixnum_value(EGL_CONFIG_ID));
#endif
#ifdef EGL_LEVEL
		mrb_define_const(mrb, constants, "EGL_LEVEL", mrb_fixnum_value(EGL_LEVEL));
#endif
#ifdef EGL_MAX_PBUFFER_HEIGHT
		mrb_define_const(mrb, constants, "EGL_MAX_PBUFFER_HEIGHT", mrb_fixnum_value(EGL_MAX_PBUFFER_HEIGHT));
#endif
#ifdef EGL_MAX_PBUFFER_PIXELS
		mrb_define_const(mrb, constants, "EGL_MAX_PBUFFER_PIXELS", mrb_fixnum_value(EGL_MAX_PBUFFER_PIXELS));
#endif
#ifdef EGL_MAX_PBUFFER_WIDTH
		mrb_define_const(mrb, constants, "EGL_MAX_PBUFFER_WIDTH", mrb_fixnum_value(EGL_MAX_PBUFFER_WIDTH));
#endif
#ifdef EGL_NATIVE_RENDERABLE
		mrb_define_const(mrb, constants, "EGL_NATIVE_RENDERABLE", mrb_fixnum_value(EGL_NATIVE_RENDERABLE));
#endif
#ifdef EGL_NATIVE_VISUAL_ID
		mrb_define_const(mrb, constants, "EGL_NATIVE_VISUAL_ID", mrb_fixnum_value(EGL_NATIVE_VISUAL_ID));
#endif
#ifdef EGL_NATIVE_VISUAL_TYPE
		mrb_define_const(mrb, constants, "EGL_NATIVE_VISUAL_TYPE", mrb_fixnum_value(EGL_NATIVE_VISUAL_TYPE));
#endif
#ifdef EGL_SAMPLES
		mrb_define_const(mrb, constants, "EGL_SAMPLES", mrb_fixnum_value(EGL_SAMPLES));
#endif
#ifdef EGL_SAMPLE_BUFFERS
		mrb_define_const(mrb, constants, "EGL_SAMPLE_BUFFERS", mrb_fixnum_value(EGL_SAMPLE_BUFFERS));
#endif
#ifdef EGL_SURFACE_TYPE
		mrb_define_const(mrb, constants, "EGL_SURFACE_TYPE", mrb_fixnum_value(EGL_SURFACE_TYPE));
#endif
#ifdef EGL_TRANSPARENT_TYPE
		mrb_define_const(mrb, constants, "EGL_TRANSPARENT_TYPE", mrb_fixnum_value(EGL_TRANSPARENT_TYPE));
#endif
#ifdef EGL_TRANSPARENT_BLUE_VALUE
		mrb_define_const(mrb, constants, "EGL_TRANSPARENT_BLUE_VALUE", mrb_fixnum_value(EGL_TRANSPARENT_BLUE_VALUE));
#endif
#ifdef EGL_TRANSPARENT_GREEN_VALUE
		mrb_define_const(mrb, constants, "EGL_TRANSPARENT_GREEN_VALUE", mrb_fixnum_value(EGL_TRANSPARENT_GREEN_VALUE));
#endif
#ifdef EGL_TRANSPARENT_RED_VALUE
		mrb_define_const(mrb, constants, "EGL_TRANSPARENT_RED_VALUE", mrb_fixnum_value(EGL_TRANSPARENT_RED_VALUE));
#endif
#ifdef EGL_NONE
		mrb_define_const(mrb, constants, "EGL_NONE", mrb_fixnum_value(EGL_NONE));
#endif
#ifdef EGL_BIND_TO_TEXTURE_RGB
		mrb_define_const(mrb, constants, "EGL_BIND_TO_TEXTURE_RGB", mrb_fixnum_value(EGL_BIND_TO_TEXTURE_RGB));
#endif
#ifdef EGL_BIND_TO_TEXTURE_RGBA
		mrb_define_const(mrb, constants, "EGL_BIND_TO_TEXTURE_RGBA", mrb_fixnum_value(EGL_BIND_TO_TEXTURE_RGBA));
#endif
#ifdef EGL_MIN_SWAP_INTERVAL
		mrb_define_const(mrb, constants, "EGL_MIN_SWAP_INTERVAL", mrb_fixnum_value(EGL_MIN_SWAP_INTERVAL));
#endif
#ifdef EGL_MAX_SWAP_INTERVAL
		mrb_define_const(mrb, constants, "EGL_MAX_SWAP_INTERVAL", mrb_fixnum_value(EGL_MAX_SWAP_INTERVAL));
#endif
#ifdef EGL_LUMINANCE_SIZE
		mrb_define_const(mrb, constants, "EGL_LUMINANCE_SIZE", mrb_fixnum_value(EGL_LUMINANCE_SIZE));
#endif
#ifdef EGL_ALPHA_MASK_SIZE
		mrb_define_const(mrb, constants, "EGL_ALPHA_MASK_SIZE", mrb_fixnum_value(EGL_ALPHA_MASK_SIZE));
#endif
#ifdef EGL_COLOR_BUFFER_TYPE
		mrb_define_const(mrb, constants, "EGL_COLOR_BUFFER_TYPE", mrb_fixnum_value(EGL_COLOR_BUFFER_TYPE));
#endif
#ifdef EGL_RENDERABLE_TYPE
		mrb_define_const(mrb, constants, "EGL_RENDERABLE_TYPE", mrb_fixnum_value(EGL_RENDERABLE_TYPE));
#endif
#ifdef EGL_MATCH_NATIVE_PIXMAP
		mrb_define_const(mrb, constants, "EGL_MATCH_NATIVE_PIXMAP", mrb_fixnum_value(EGL_MATCH_NATIVE_PIXMAP));
#endif
#ifdef EGL_CONFORMANT
		mrb_define_const(mrb, constants, "EGL_CONFORMANT", mrb_fixnum_value(EGL_CONFORMANT));
#endif
#ifdef EGL_SLOW_CONFIG
		mrb_define_const(mrb, constants, "EGL_SLOW_CONFIG", mrb_fixnum_value(EGL_SLOW_CONFIG));
#endif
#ifdef EGL_NON_CONFORMANT_CONFIG
		mrb_define_const(mrb, constants, "EGL_NON_CONFORMANT_CONFIG", mrb_fixnum_value(EGL_NON_CONFORMANT_CONFIG));
#endif
#ifdef EGL_TRANSPARENT_RGB
		mrb_define_const(mrb, constants, "EGL_TRANSPARENT_RGB", mrb_fixnum_value(EGL_TRANSPARENT_RGB));
#endif
#ifdef EGL_RGB_BUFFER
		mrb_define_const(mrb, constants, "EGL_RGB_BUFFER", mrb_fixnum_value(EGL_RGB_BUFFER));
#endif
#ifdef EGL_LUMINANCE_BUFFER
		mrb_define_const(mrb, constants, "EGL_LUMINANCE_BUFFER", mrb_fixnum_value(EGL_LUMINANCE_BUFFER));
#endif
#ifdef EGL_NO_TEXTURE
		mrb_define_const(mrb, constants, "EGL_NO_TEXTURE", mrb_fixnum_value(EGL_NO_TEXTURE));
#endif
#ifdef EGL_TEXTURE_RGB
		mrb_define_const(mrb, constants, "EGL_TEXTURE_RGB", mrb_fixnum_value(EGL_TEXTURE_RGB));
#endif
#ifdef EGL_TEXTURE_RGBA
		mrb_define_const(mrb, constants, "EGL_TEXTURE_RGBA", mrb_fixnum_value(EGL_TEXTURE_RGBA));
#endif
#ifdef EGL_TEXTURE_2D
		mrb_define_const(mrb, constants, "EGL_TEXTURE_2D", mrb_fixnum_value(EGL_TEXTURE_2D));
#endif
#ifdef EGL_PBUFFER_BIT
		mrb_define_const(mrb, constants, "EGL_PBUFFER_BIT", mrb_fixnum_value(EGL_PBUFFER_BIT));
#endif
#ifdef EGL_PIXMAP_BIT
		mrb_define_const(mrb, constants, "EGL_PIXMAP_BIT", mrb_fixnum_value(EGL_PIXMAP_BIT));
#endif
#ifdef EGL_WINDOW_BIT
		mrb_define_const(mrb, constants, "EGL_WINDOW_BIT", mrb_fixnum_value(EGL_WINDOW_BIT));
#endif
#ifdef EGL_VG_COLORSPACE_LINEAR_BIT
		mrb_define_const(mrb, constants, "EGL_VG_COLORSPACE_LINEAR_BIT", mrb_fixnum_value(EGL_VG_COLORSPACE_LINEAR_BIT));
#endif
#ifdef EGL_VG_ALPHA_FORMAT_PRE_BIT
		mrb_define_const(mrb, constants, "EGL_VG_ALPHA_FORMAT_PRE_BIT", mrb_fixnum_value(EGL_VG_ALPHA_FORMAT_PRE_BIT));
#endif
#ifdef EGL_MULTISAMPLE_RESOLVE_BOX_BIT
		mrb_define_const(mrb, constants, "EGL_MULTISAMPLE_RESOLVE_BOX_BIT", mrb_fixnum_value(EGL_MULTISAMPLE_RESOLVE_BOX_BIT));
#endif
#ifdef EGL_SWAP_BEHAVIOR_PRESERVED_BIT
		mrb_define_const(mrb, constants, "EGL_SWAP_BEHAVIOR_PRESERVED_BIT", mrb_fixnum_value(EGL_SWAP_BEHAVIOR_PRESERVED_BIT));
#endif
#ifdef EGL_OPENGL_ES_BIT
		mrb_define_const(mrb, constants, "EGL_OPENGL_ES_BIT", mrb_fixnum_value(EGL_OPENGL_ES_BIT));
#endif
#ifdef EGL_OPENVG_BIT
		mrb_define_const(mrb, constants, "EGL_OPENVG_BIT", mrb_fixnum_value(EGL_OPENVG_BIT));
#endif
#ifdef EGL_OPENGL_ES2_BIT
		mrb_define_const(mrb, constants, "EGL_OPENGL_ES2_BIT", mrb_fixnum_value(EGL_OPENGL_ES2_BIT));
#endif
#ifdef EGL_OPENGL_BIT
		mrb_define_const(mrb, constants, "EGL_OPENGL_BIT", mrb_fixnum_value(EGL_OPENGL_BIT));
#endif
#ifdef EGL_VENDOR
		mrb_define_const(mrb, constants, "EGL_VENDOR", mrb_fixnum_value(EGL_VENDOR));
#endif
#ifdef EGL_VERSION
		mrb_define_const(mrb, constants, "EGL_VERSION", mrb_fixnum_value(EGL_VERSION));
#endif
#ifdef EGL_EXTENSIONS
		mrb_define_const(mrb, constants, "EGL_EXTENSIONS", mrb_fixnum_value(EGL_EXTENSIONS));
#endif
#ifdef EGL_CLIENT_APIS
		mrb_define_const(mrb, constants, "EGL_CLIENT_APIS", mrb_fixnum_value(EGL_CLIENT_APIS));
#endif
#ifdef EGL_HEIGHT
		mrb_define_const(mrb, constants, "EGL_HEIGHT", mrb_fixnum_value(EGL_HEIGHT));
#endif
#ifdef EGL_WIDTH
		mrb_define_const(mrb, constants, "EGL_WIDTH", mrb_fixnum_value(EGL_WIDTH));
#endif
#ifdef EGL_LARGEST_PBUFFER
		mrb_define_const(mrb, constants, "EGL_LARGEST_PBUFFER", mrb_fixnum_value(EGL_LARGEST_PBUFFER));
#endif
#ifdef EGL_TEXTURE_FORMAT
		mrb_define_const(mrb, constants, "EGL_TEXTURE_FORMAT", mrb_fixnum_value(EGL_TEXTURE_FORMAT));
#endif
#ifdef EGL_TEXTURE_TARGET
		mrb_define_const(mrb, constants, "EGL_TEXTURE_TARGET", mrb_fixnum_value(EGL_TEXTURE_TARGET));
#endif
#ifdef EGL_MIPMAP_TEXTURE
		mrb_define_const(mrb, constants, "EGL_MIPMAP_TEXTURE", mrb_fixnum_value(EGL_MIPMAP_TEXTURE));
#endif
#ifdef EGL_MIPMAP_LEVEL
		mrb_define_const(mrb, constants, "EGL_MIPMAP_LEVEL", mrb_fixnum_value(EGL_MIPMAP_LEVEL));
#endif
#ifdef EGL_RENDER_BUFFER
		mrb_define_const(mrb, constants, "EGL_RENDER_BUFFER", mrb_fixnum_value(EGL_RENDER_BUFFER));
#endif
#ifdef EGL_VG_COLORSPACE
		mrb_define_const(mrb, constants, "EGL_VG_COLORSPACE", mrb_fixnum_value(EGL_VG_COLORSPACE));
#endif
#ifdef EGL_VG_ALPHA_FORMAT
		mrb_define_const(mrb, constants, "EGL_VG_ALPHA_FORMAT", mrb_fixnum_value(EGL_VG_ALPHA_FORMAT));
#endif
#ifdef EGL_HORIZONTAL_RESOLUTION
		mrb_define_const(mrb, constants, "EGL_HORIZONTAL_RESOLUTION", mrb_fixnum_value(EGL_HORIZONTAL_RESOLUTION));
#endif
#ifdef EGL_VERTICAL_RESOLUTION
		mrb_define_const(mrb, constants, "EGL_VERTICAL_RESOLUTION", mrb_fixnum_value(EGL_VERTICAL_RESOLUTION));
#endif
#ifdef EGL_PIXEL_ASPECT_RATIO
		mrb_define_const(mrb, constants, "EGL_PIXEL_ASPECT_RATIO", mrb_fixnum_value(EGL_PIXEL_ASPECT_RATIO));
#endif
#ifdef EGL_SWAP_BEHAVIOR
		mrb_define_const(mrb, constants, "EGL_SWAP_BEHAVIOR", mrb_fixnum_value(EGL_SWAP_BEHAVIOR));
#endif
#ifdef EGL_MULTISAMPLE_RESOLVE
		mrb_define_const(mrb, constants, "EGL_MULTISAMPLE_RESOLVE", mrb_fixnum_value(EGL_MULTISAMPLE_RESOLVE));
#endif
#ifdef EGL_BACK_BUFFER
		mrb_define_const(mrb, constants, "EGL_BACK_BUFFER", mrb_fixnum_value(EGL_BACK_BUFFER));
#endif
#ifdef EGL_SINGLE_BUFFER
		mrb_define_const(mrb, constants, "EGL_SINGLE_BUFFER", mrb_fixnum_value(EGL_SINGLE_BUFFER));
#endif
#ifdef EGL_VG_COLORSPACE_sRGB
		mrb_define_const(mrb, constants, "EGL_VG_COLORSPACE_sRGB", mrb_fixnum_value(EGL_VG_COLORSPACE_sRGB));
#endif
#ifdef EGL_VG_COLORSPACE_LINEAR
		mrb_define_const(mrb, constants, "EGL_VG_COLORSPACE_LINEAR", mrb_fixnum_value(EGL_VG_COLORSPACE_LINEAR));
#endif
#ifdef EGL_VG_ALPHA_FORMAT_NONPRE
		mrb_define_const(mrb, constants, "EGL_VG_ALPHA_FORMAT_NONPRE", mrb_fixnum_value(EGL_VG_ALPHA_FORMAT_NONPRE));
#endif
#ifdef EGL_VG_ALPHA_FORMAT_PRE
		mrb_define_const(mrb, constants, "EGL_VG_ALPHA_FORMAT_PRE", mrb_fixnum_value(EGL_VG_ALPHA_FORMAT_PRE));
#endif
#ifdef EGL_DISPLAY_SCALING
		mrb_define_const(mrb, constants, "EGL_DISPLAY_SCALING", mrb_fixnum_value(EGL_DISPLAY_SCALING));
#endif
#ifdef EGL_UNKNOWN
		mrb_define_const(mrb, constants, "EGL_UNKNOWN", mrb_fixnum_value(EGL_UNKNOWN));
#endif
#ifdef EGL_BUFFER_PRESERVED
		mrb_define_const(mrb, constants, "EGL_BUFFER_PRESERVED", mrb_fixnum_value(EGL_BUFFER_PRESERVED));
#endif
#ifdef EGL_BUFFER_DESTROYED
		mrb_define_const(mrb, constants, "EGL_BUFFER_DESTROYED", mrb_fixnum_value(EGL_BUFFER_DESTROYED));
#endif
#ifdef EGL_OPENVG_IMAGE
		mrb_define_const(mrb, constants, "EGL_OPENVG_IMAGE", mrb_fixnum_value(EGL_OPENVG_IMAGE));
#endif
#ifdef EGL_CONTEXT_CLIENT_TYPE
		mrb_define_const(mrb, constants, "EGL_CONTEXT_CLIENT_TYPE", mrb_fixnum_value(EGL_CONTEXT_CLIENT_TYPE));
#endif
#ifdef EGL_CONTEXT_CLIENT_VERSION
		mrb_define_const(mrb, constants, "EGL_CONTEXT_CLIENT_VERSION", mrb_fixnum_value(EGL_CONTEXT_CLIENT_VERSION));
#endif
#ifdef EGL_MULTISAMPLE_RESOLVE_DEFAULT
		mrb_define_const(mrb, constants, "EGL_MULTISAMPLE_RESOLVE_DEFAULT", mrb_fixnum_value(EGL_MULTISAMPLE_RESOLVE_DEFAULT));
#endif
#ifdef EGL_MULTISAMPLE_RESOLVE_BOX
		mrb_define_const(mrb, constants, "EGL_MULTISAMPLE_RESOLVE_BOX", mrb_fixnum_value(EGL_MULTISAMPLE_RESOLVE_BOX));
#endif
#ifdef EGL_OPENGL_ES_API
		mrb_define_const(mrb, constants, "EGL_OPENGL_ES_API", mrb_fixnum_value(EGL_OPENGL_ES_API));
#endif
#ifdef EGL_OPENVG_API
		mrb_define_const(mrb, constants, "EGL_OPENVG_API", mrb_fixnum_value(EGL_OPENVG_API));
#endif
#ifdef EGL_OPENGL_API
		mrb_define_const(mrb, constants, "EGL_OPENGL_API", mrb_fixnum_value(EGL_OPENGL_API));
#endif
#ifdef EGL_DRAW
		mrb_define_const(mrb, constants, "EGL_DRAW", mrb_fixnum_value(EGL_DRAW));
#endif
#ifdef EGL_READ
		mrb_define_const(mrb, constants, "EGL_READ", mrb_fixnum_value(EGL_READ));
#endif
#ifdef EGL_CORE_NATIVE_ENGINE
		mrb_define_const(mrb, constants, "EGL_CORE_NATIVE_ENGINE", mrb_fixnum_value(EGL_CORE_NATIVE_ENGINE));
#endif
#ifdef EGL_COLORSPACE
		mrb_define_const(mrb, constants, "EGL_COLORSPACE", mrb_fixnum_value(EGL_COLORSPACE));
#endif
#ifdef EGL_ALPHA_FORMAT
		mrb_define_const(mrb, constants, "EGL_ALPHA_FORMAT", mrb_fixnum_value(EGL_ALPHA_FORMAT));
#endif
#ifdef EGL_COLORSPACE_sRGB
		mrb_define_const(mrb, constants, "EGL_COLORSPACE_sRGB", mrb_fixnum_value(EGL_COLORSPACE_sRGB));
#endif
#ifdef EGL_COLORSPACE_LINEAR
		mrb_define_const(mrb, constants, "EGL_COLORSPACE_LINEAR", mrb_fixnum_value(EGL_COLORSPACE_LINEAR));
#endif
#ifdef EGL_ALPHA_FORMAT_NONPRE
		mrb_define_const(mrb, constants, "EGL_ALPHA_FORMAT_NONPRE", mrb_fixnum_value(EGL_ALPHA_FORMAT_NONPRE));
#endif
#ifdef EGL_ALPHA_FORMAT_PRE
		mrb_define_const(mrb, constants, "EGL_ALPHA_FORMAT_PRE", mrb_fixnum_value(EGL_ALPHA_FORMAT_PRE));
#endif

	return constants;
}

