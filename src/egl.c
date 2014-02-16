#include <mruby.h>

#include "egl.h"

void mrb_mruby_egl_gem_init(mrb_state* mrb)
{
	struct RClass* egl  = mrb_define_module(mrb, "EGL");
	mrb_egl_define_constants(mrb, egl);
	mrb_egl_define_methods(mrb, egl);
}

void mrb_mruby_egl_gem_final()
{
}

