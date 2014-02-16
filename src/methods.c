#include <mruby.h>
#include <mruby/array.h>
#include <mruby/hash.h>
#include <mruby/value.h>
#include <mruby/variable.h>

#include <GLES2/gl2.h>
#include <EGL/egl.h>

#include <string.h>
#include <stdlib.h>

#include "egl.h"

static EGLint* create_attr_list(mrb_state* mrb, mrb_value attr)
{
	if (mrb_nil_p(attr)) {
		return NULL;
	}

	mrb_int len = mrb_ary_len(mrb, attr);
	GLint* alist = (GLint*)mrb_malloc(mrb, sizeof(GLint) * (len*2+1));
	int i;
	for (i = 0; i < len; i++) {
		alist[i*2  ] = mrb_fixnum(mrb_ary_ref(mrb, attr, i*2  ));
		alist[i*2+1] = mrb_fixnum(mrb_ary_ref(mrb, attr, i*2+1));
	}
	alist[len*2] = EGL_NONE;

	return alist;
}

// egl APIs

static mrb_value bindAPI(mrb_state* mrb, mrb_value self)
{
	mrb_int api;
	mrb_get_args(mrb, "i", &api);
	EGLBoolean b = eglBindAPI((EGLenum)api);
	return (b != EGL_FALSE)? mrb_true_value() : mrb_false_value();
}

static mrb_value bindTexImage(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_value surface_value;
	mrb_int buffer;
	mrb_get_args(mrb, "ooi", &display_value, &surface_value, &buffer);

	EGLDisplay display = mrb_cptr(display_value);
	EGLSurface surface = mrb_cptr(surface_value);

	EGLBoolean b = eglBindTexImage(display, surface, buffer);
	return (b != EGL_FALSE)? mrb_true_value() : mrb_false_value();
}

static mrb_value chooseConfig(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_value attr_list_value;
	mrb_get_args(mrb, "oo", &display_value, &attr_list_value);

	EGLDisplay display = mrb_cptr(display_value);

	EGLint* attr = NULL;
	if (!mrb_nil_p(attr_list_value)) {
		attr = create_attr_list(mrb, attr_list_value);
		if (attr == NULL) {
			mrb_raise(mrb, E_RUNTIME_ERROR, "no mem for attr_list");
			return mrb_nil_value();
		}
	}

	GLint max_configs;
	if (eglChooseConfig(display, attr, NULL, 0, &max_configs) == EGL_FALSE) {
		mrb_free(mrb, attr);
		mrb_raise(mrb, E_RUNTIME_ERROR, "eglChooseConfig(): failed to get max configs");
		return mrb_nil_value();
	}

	EGLConfig* configs = (EGLConfig*)mrb_malloc(mrb, sizeof(EGLConfig) * max_configs);
	if (configs == NULL) {
		mrb_free(mrb, attr);
		mrb_raise(mrb, E_RUNTIME_ERROR, "eglChooseConfig(): mrb_malloc() failed");
		return mrb_nil_value();
	}

	GLint num_config;
	if (eglChooseConfig(display, attr, configs, max_configs, &num_config) == EGL_FALSE) {
		mrb_free(mrb, configs);
		mrb_free(mrb, attr);
		return mrb_nil_value();
	}
	mrb_free(mrb, attr);
	attr = NULL;

	mrb_value ary = mrb_ary_new_capa(mrb, num_config);
	int i;
	for (i = 0; i < num_config; i++) {
		mrb_int ai = mrb_gc_arena_save(mrb);
		mrb_ary_set(mrb, ary, i, mrb_cptr_value(mrb, configs[i]));
		mrb_gc_arena_restore(mrb, ai);
	}
	mrb_free(mrb, configs);

	return ary;
}

static mrb_value copyBuffers(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_value surface_value;
	mrb_value native_pixmap_value;
	mrb_get_args(mrb, "ooo", &display_value, &surface_value, &native_pixmap_value);

	EGLDisplay display = mrb_cptr(display_value);
	EGLSurface surface = mrb_cptr(surface_value);
	NativePixmapType native_pixmap = (NativePixmapType)mrb_cptr(native_pixmap_value);

	EGLBoolean b = eglCopyBuffers(display, surface, native_pixmap);
	return (b != EGL_FALSE)? mrb_true_value() : mrb_false_value();
}

static mrb_value createContext(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_value surface_value;
	mrb_value shared_context_value;
	mrb_value attr_list_value;
	mrb_get_args(mrb, "oooo", &display_value, &surface_value, &shared_context_value, &attr_list_value);

	EGLDisplay display        = mrb_cptr(display_value);
	EGLSurface surface        = mrb_cptr(surface_value);
	EGLContext shared_context = mrb_cptr(shared_context_value);
	EGLint* attr = NULL;
	if (!mrb_nil_p(attr_list_value)) {
		attr = create_attr_list(mrb, attr_list_value);
		if (attr == NULL) {
			mrb_raise(mrb, E_RUNTIME_ERROR, "no mem for attr_list");
			return mrb_nil_value();
		}
	}

	EGLContext context = eglCreateContext(display, surface, shared_context, attr);

	if (attr != NULL) {
		mrb_free(mrb, attr);
	}

	return (context != EGL_NO_CONTEXT)? mrb_cptr_value(mrb, context) : mrb_nil_value();
}

static mrb_value createPbufferFromClientBuffer(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_int   buftype;
	mrb_value buffer_value;
	mrb_value config_value;
	mrb_value attr_list_value;
	mrb_get_args(mrb, "oiooo", &display_value, &buftype, &buffer_value, &config_value, &attr_list_value);

	EGLDisplay      display   = mrb_cptr(display_value);
	EGLClientBuffer buffer    = mrb_cptr(buffer_value);
	EGLConfig       config    = mrb_cptr(config_value);
	EGLint* attr = NULL;
	if (!mrb_nil_p(attr_list_value)) {
		attr = create_attr_list(mrb, attr_list_value);
		if (attr == NULL) {
			mrb_raise(mrb, E_RUNTIME_ERROR, "no mem for attr_list");
			return mrb_nil_value();
		}
	}

	EGLSurface surface = eglCreatePbufferFromClientBuffer(display, buftype, buffer, config, attr);

	if (attr != NULL) {
		mrb_free(mrb, attr);
	}

	return (surface != EGL_NO_SURFACE)? mrb_cptr_value(mrb, surface) : mrb_nil_value();
}

static mrb_value createPbufferSurface(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_value config_value;
	mrb_value attr_list_value;
	mrb_get_args(mrb, "ooo", &display_value, &config_value, &attr_list_value);

	EGLDisplay      display   = mrb_cptr(display_value);
	EGLConfig       config    = mrb_cptr(config_value);
	EGLint* attr = NULL;
	if (!mrb_nil_p(attr_list_value)) {
		attr = create_attr_list(mrb, attr_list_value);
		if (attr == NULL) {
			mrb_raise(mrb, E_RUNTIME_ERROR, "no mem for attr_list");
			return mrb_nil_value();
		}
	}

	EGLSurface surface = eglCreatePbufferSurface(display, config, attr);

	if (attr != NULL) {
		mrb_free(mrb, attr);
	}

	return (surface != EGL_NO_SURFACE)? mrb_cptr_value(mrb, surface) : mrb_nil_value();
}

static mrb_value createPixmapSurface(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_value config_value;
	mrb_value native_pixmap_value;
	mrb_value attr_list_value;
	mrb_get_args(mrb, "oooo", &display_value, &config_value, &native_pixmap_value, &attr_list_value);

	EGLDisplay       display       = mrb_cptr(display_value);
	EGLConfig        config        = mrb_cptr(config_value);
	NativePixmapType native_pixmap = (NativePixmapType)mrb_cptr(native_pixmap_value);
	EGLint* attr = NULL;
	if (!mrb_nil_p(attr_list_value)) {
		attr = create_attr_list(mrb, attr_list_value);
		if (attr == NULL) {
			mrb_raise(mrb, E_RUNTIME_ERROR, "no mem for attr_list");
			return mrb_nil_value();
		}
	}

	EGLSurface surface = eglCreatePixmapSurface(display, config, native_pixmap, attr);

	if (attr != NULL) {
		mrb_free(mrb, attr);
	}

	return (surface != EGL_NO_SURFACE)? mrb_cptr_value(mrb, surface) : mrb_nil_value();
}

static mrb_value createWindowSurface(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_value config_value;
	mrb_value native_window_value;
	mrb_value attr_list_value;
	mrb_get_args(mrb, "oooo", &display_value, &config_value, &native_window_value, &attr_list_value);

	EGLDisplay       display       = mrb_cptr(display_value);
	EGLConfig        config        = mrb_cptr(config_value);
	NativeWindowType native_window = (NativeWindowType)mrb_cptr(native_window_value);
	EGLint* attr = NULL;
	if (!mrb_nil_p(attr_list_value)) {
		attr = create_attr_list(mrb, attr_list_value);
		if (attr == NULL) {
			mrb_raise(mrb, E_RUNTIME_ERROR, "no mem for attr_list");
			return mrb_nil_value();
		}
	}

	EGLSurface surface = eglCreateWindowSurface(display, config, native_window, attr);

	if (attr != NULL) {
		mrb_free(mrb, attr);
	}

	return (surface != EGL_NO_SURFACE)? mrb_cptr_value(mrb, surface) : mrb_nil_value();
}

static mrb_value destroyContext(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_value context_value;
	mrb_get_args(mrb, "oo", &display_value, &context_value);

	EGLDisplay display = mrb_cptr(display_value);
	EGLContext context = mrb_cptr(context_value);

	EGLBoolean b = eglDestroyContext(display, context);

	return (b != EGL_FALSE)? mrb_true_value() : mrb_false_value();
}

static mrb_value destroySurface(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_value surface_value;
	mrb_get_args(mrb, "oo", &display_value, &surface_value);

	EGLDisplay display = mrb_cptr(display_value);
	EGLSurface surface = mrb_cptr(surface_value);

	EGLBoolean b = eglDestroySurface(display, surface);

	return (b != EGL_FALSE)? mrb_true_value() : mrb_false_value();
}

static mrb_value getConfigAttrib(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_value config_value;
	mrb_int attrib;
	mrb_get_args(mrb, "ooi", &display_value, &config_value, &attrib);

	EGLDisplay display = mrb_cptr(display_value);
	EGLConfig  config  = mrb_cptr(config_value);

	EGLint value;
	EGLBoolean b = eglGetConfigAttrib(display, config, attrib, &value);
	return (b != EGL_FALSE)? mrb_fixnum_value(value) : mrb_nil_value();
}

static mrb_value getConfigs(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_int num;
	int num_args = mrb_get_args(mrb, "o|i", &display_value, &num);

	EGLDisplay display = mrb_cptr(display_value);
	if (num_args >= 1) {
		eglGetConfigs(display, NULL, 0, &num);
	}

	EGLConfig* configs = (EGLConfig*)mrb_malloc(mrb, num * sizeof(EGLConfig));
	if (configs == NULL) {
		mrb_raise(mrb, E_RUNTIME_ERROR, "no mem for configs buffer");
		return mrb_nil_value();
	}
	int num_configs = 0;
	eglGetConfigs(display, configs, num, &num_configs);

	mrb_value configs_value = mrb_ary_new_capa(mrb, num_configs);
	int i;
	for (i = 0; i < num; i++) {
		mrb_int ai = mrb_gc_arena_save(mrb);
		mrb_ary_set(mrb, configs_value, i, mrb_cptr_value(mrb, configs[i]));
		mrb_gc_arena_restore(mrb, ai);
	}

	mrb_free(mrb, configs);

	return configs_value;
}

static mrb_value getError(mrb_state* mrb, mrb_value self)
{
	return mrb_fixnum_value(eglGetError());
}

static mrb_value getCurrentContext(mrb_state* mrb, mrb_value self)
{
	EGLContext context = eglGetCurrentContext();
	return (context != EGL_NO_CONTEXT)? mrb_cptr_value(mrb, context) : mrb_nil_value();
}

static mrb_value getCurrentDisplay(mrb_state* mrb, mrb_value self)
{
	EGLDisplay display = eglGetCurrentDisplay();
	return (display != EGL_NO_DISPLAY)? mrb_cptr_value(mrb, display) : mrb_nil_value();
}

static mrb_value getCurrentSurface(mrb_state* mrb, mrb_value self)
{
	mrb_int readdraw;
	mrb_get_args(mrb, "i", &readdraw);
	EGLSurface surface = eglGetCurrentSurface(readdraw);
	return (surface != EGL_NO_SURFACE)? mrb_cptr_value(mrb, surface) : mrb_nil_value();
}

static mrb_value getDisplay(mrb_state* mrb, mrb_value self)
{
	mrb_value a;
	mrb_get_args(mrb, "o", &a);
	void* p = mrb_cptr(a);
	return mrb_cptr_value(mrb, eglGetDisplay((NativeDisplayType)p));
}

static mrb_value getProcAddress(mrb_state* mrb, mrb_value self)
{
	const char* procname = NULL;
	mrb_get_args(mrb, "z", &procname);

	void* proc = eglGetProcAddress(procname);
	return (proc != NULL)? mrb_cptr_value(mrb, proc) : mrb_nil_value();
}

static mrb_value makeCurrent(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_value drawsurface_value;
	mrb_value readsurface_value;
	mrb_value context_value;
	mrb_get_args(mrb, "oooo", &display_value, &drawsurface_value, &readsurface_value, &context_value);

	EGLDisplay display = (!mrb_nil_p(display_value))? mrb_cptr(display_value) : EGL_NO_DISPLAY;
	EGLSurface draw    = (!mrb_nil_p(drawsurface_value))? mrb_cptr(drawsurface_value) : EGL_NO_SURFACE;
	EGLSurface read    = (!mrb_nil_p(readsurface_value))? mrb_cptr(readsurface_value) : EGL_NO_SURFACE;
	EGLContext context = (!mrb_nil_p(context_value))? mrb_cptr(context_value) : EGL_NO_CONTEXT;

	EGLBoolean b = eglMakeCurrent(display, draw, read, context);
	return (b != EGL_FALSE)? mrb_true_value() : mrb_false_value();
}

static mrb_value initialize(mrb_state* mrb, mrb_value self)
{
	mrb_value a;
	mrb_get_args(mrb, "o", &a);
	void* display = mrb_cptr(a);

	EGLint major, minor;
	EGLBoolean b = eglInitialize(display, &major, &minor);
	mrb_value ary[3] = {mrb_fixnum_value(b), mrb_fixnum_value(major), mrb_fixnum_value(minor)};
	return mrb_ary_new_from_values(mrb, 3, ary);
}

static mrb_value terminate(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_get_args(mrb, "o", &display_value);

	EGLDisplay display = mrb_cptr(display_value);

	EGLBoolean b = eglTerminate(display);

	return (b != EGL_FALSE)? mrb_true_value() : mrb_false_value();
}

static mrb_value queryAPI(mrb_state* mrb, mrb_value self)
{
	return mrb_fixnum_value(eglQueryAPI());
}

static mrb_value queryContext(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_value context_value;
	mrb_int   attrib;
	mrb_get_args(mrb, "ooi", &display_value, &context_value, &attrib);

	EGLDisplay display = mrb_cptr(display_value);
	EGLContext context = mrb_cptr(context_value);

	mrb_int value;
	EGLBoolean b = eglQueryContext(display, context, attrib, &value);

	return (b != EGL_FALSE)? mrb_fixnum_value(value) : mrb_nil_value();
}

static mrb_value queryString(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_int   name;
	mrb_get_args(mrb, "oi", &display_value, &name);

	EGLDisplay display = mrb_cptr(display_value);

	const char* str = eglQueryString(display, name);
	return (str != NULL)? mrb_str_new_cstr(mrb, str) : mrb_nil_value();
}

static mrb_value querySurface(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_value surface_value;
	mrb_int   attrib;
	mrb_get_args(mrb, "ooi", &display_value, &surface_value, &attrib);

	EGLDisplay display = mrb_cptr(display_value);
	EGLSurface surface = mrb_cptr(surface_value);

	mrb_int value;
	EGLBoolean b = eglQuerySurface(display, surface, attrib, &value);

	return (b != EGL_FALSE)? mrb_fixnum_value(value) : mrb_nil_value();
}

static mrb_value releaseTexImage(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_value surface_value;
	mrb_int   buffer;
	mrb_get_args(mrb, "ooi", &display_value, &surface_value, &buffer);

	EGLDisplay display = mrb_cptr(display_value);
	EGLSurface surface = mrb_cptr(surface_value);

	EGLBoolean b = eglReleaseTexImage(display, surface, buffer);
	return (b != EGL_FALSE)? mrb_true_value() : mrb_false_value();
}

static mrb_value releaseThread(mrb_state* mrb, mrb_value self)
{
	EGLBoolean b = eglReleaseThread();
	return (b != EGL_FALSE)? mrb_true_value() : mrb_false_value();
}

static mrb_value surfaceAttrib(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_value surface_value;
	mrb_int   attrib;
	mrb_int   value;
	mrb_get_args(mrb, "ooii", &display_value, &surface_value, &attrib, &value);

	EGLDisplay display = mrb_cptr(display_value);
	EGLSurface surface = mrb_cptr(surface_value);

	EGLBoolean b = eglSurfaceAttrib(display, surface, attrib, value);
	return (b != EGL_FALSE)? mrb_true_value() : mrb_false_value();
}

static mrb_value swapBuffers(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_value surface_value;
	mrb_get_args(mrb, "oo", &display_value, &surface_value);

	EGLDisplay display = mrb_cptr(display_value);
	EGLSurface surface = mrb_cptr(surface_value);

	EGLBoolean b = eglSwapBuffers(display, surface);
	return (b != EGL_FALSE)? mrb_true_value() : mrb_false_value();
}

static mrb_value swapInterval(mrb_state* mrb, mrb_value self)
{
	mrb_value display_value;
	mrb_int   interval;
	mrb_get_args(mrb, "oi", &display_value, &interval);

	EGLDisplay display = mrb_cptr(display_value);

	EGLBoolean b = eglSwapInterval(display, interval);
	return (b != EGL_FALSE)? mrb_true_value() : mrb_false_value();
}

static mrb_value waitClient(mrb_state* mrb, mrb_value self)
{
	return (eglWaitClient() != EGL_FALSE)? mrb_true_value() : mrb_false_value();
}

static mrb_value waitGL(mrb_state* mrb, mrb_value self)
{
	return (eglWaitGL() != EGL_FALSE)? mrb_true_value() : mrb_false_value();
}
static mrb_value waitNative(mrb_state* mrb, mrb_value self)
{
	mrb_int engine;
	mrb_get_args(mrb, "i", &engine);

	return (eglWaitNative(engine) != EGL_FALSE)? mrb_true_value() : mrb_false_value();
}


void mrb_egl_define_methods(mrb_state* mrb, struct RClass* outer)
{
	mrb_define_module_function(mrb, outer, "eglBindAPI", bindAPI, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, outer, "eglBindTexImage", bindTexImage, MRB_ARGS_REQ(3));
	mrb_define_module_function(mrb, outer, "_eglChooseConfig", chooseConfig, MRB_ARGS_REQ(2));
	mrb_define_module_function(mrb, outer, "eglCopyBuffers", copyBuffers, MRB_ARGS_REQ(3));
	mrb_define_module_function(mrb, outer, "_eglCreateContext", createContext, MRB_ARGS_REQ(4));
	mrb_define_module_function(mrb, outer, "_eglCreatePbufferFromClientBuffer", createPbufferFromClientBuffer, MRB_ARGS_REQ(5));
	mrb_define_module_function(mrb, outer, "_eglCreatePbufferSurface", createPbufferSurface, MRB_ARGS_REQ(3));
	mrb_define_module_function(mrb, outer, "_eglCreatePixmapSurface", createPixmapSurface, MRB_ARGS_REQ(4));
	mrb_define_module_function(mrb, outer, "_eglCreateWindowSurface", createWindowSurface, MRB_ARGS_REQ(4));
	mrb_define_module_function(mrb, outer, "eglDestroyContext", destroyContext, MRB_ARGS_REQ(2));
	mrb_define_module_function(mrb, outer, "eglDestroySurface", destroySurface, MRB_ARGS_REQ(2));
	mrb_define_module_function(mrb, outer, "_eglGetConfigAttrib", getConfigAttrib, MRB_ARGS_REQ(3));
	mrb_define_module_function(mrb, outer, "eglGetConfigs", getConfigs, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
	mrb_define_module_function(mrb, outer, "eglGetCurrentContext", getCurrentContext, MRB_ARGS_NONE());
	mrb_define_module_function(mrb, outer, "eglGetCurrentDisplay", getCurrentDisplay, MRB_ARGS_NONE());
	mrb_define_module_function(mrb, outer, "_eglGetCurrentSurface", getCurrentSurface, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, outer, "eglGetError", getError, MRB_ARGS_NONE());
	mrb_define_module_function(mrb, outer, "eglGetDisplay", getDisplay, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, outer, "eglGetProcAddress", getProcAddress, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, outer, "eglInitialize", initialize, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, outer, "eglMakeCurrent", makeCurrent, MRB_ARGS_REQ(4));
	mrb_define_module_function(mrb, outer, "eglQueryAPI", queryAPI, MRB_ARGS_NONE());
	mrb_define_module_function(mrb, outer, "_eglQueryContext", queryContext, MRB_ARGS_REQ(3));
	mrb_define_module_function(mrb, outer, "_eglQueryString", queryString, MRB_ARGS_REQ(2));
	mrb_define_module_function(mrb, outer, "_eglQuerySurface", querySurface, MRB_ARGS_REQ(3));
	mrb_define_module_function(mrb, outer, "eglReleaseTexImage", releaseTexImage, MRB_ARGS_REQ(3));
	mrb_define_module_function(mrb, outer, "eglReleaseThread", releaseThread, MRB_ARGS_NONE());
	mrb_define_module_function(mrb, outer, "eglSurfaceAttrib", surfaceAttrib, MRB_ARGS_REQ(4));
	mrb_define_module_function(mrb, outer, "eglSwapBuffers", swapBuffers, MRB_ARGS_REQ(2));
	mrb_define_module_function(mrb, outer, "eglSwapInterval", swapInterval, MRB_ARGS_REQ(2));
	mrb_define_module_function(mrb, outer, "eglTerminate", terminate, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, outer, "eglWaitClient", waitClient, MRB_ARGS_NONE());
	mrb_define_module_function(mrb, outer, "eglWaitGL", waitGL, MRB_ARGS_NONE());
	mrb_define_module_function(mrb, outer, "eglWaitNative", waitNative, MRB_ARGS_REQ(1));
}

