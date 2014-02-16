include EGL
include EGL::Constants

def initialize_egl
  display = eglGetDisplay(EGL_DEFAULT_DISPLAY)
  assert_true(display != nil)

  result, major, minor = eglInitialize(display)
  assert_true result
  assert_true major
  assert_true minor

  display
end

def terminate_egl(display)
  assert_true(eglTerminate(display))
end

def create_config(display)
  attrs = {
    EGL_RED_SIZE:8,
    EGL_GREEN_SIZE:8,
    EGL_BLUE_SIZE:8,
    EGL_ALPHA_SIZE:EGL_DONT_CARE,
    EGL_DEPTH_SIZE:24,
  }
  configs = eglChooseConfig(display, attrs)
  assert_true(configs)

  (configs.size() > 0)? configs[0] : nil
end

def create_pbuffer_surface(display, config)
  attrs = {
    EGL_WIDTH:960,
    EGL_HEIGHT:540,
  }
  surface = eglCreatePbufferSurface(display, config, attrs)
  assert_true(surface)

  assert_equal(960, eglQuerySurface(display, surface, EGL_WIDTH))
  assert_equal(540, eglQuerySurface(display, surface, EGL_HEIGHT))

  surface
end

def destroy_surface(display, surface)
  assert_true(eglDestroySurface(display, surface))
end

def create_context(display, config, shared_context) 
  attrs = {EGL_CONTEXT_CLIENT_VERSION:2}
  context = eglCreateContext(display, config, shared_context, attrs)
  assert_true(context)

  assert_equal(2, eglQueryContext(display, context, EGL_CONTEXT_CLIENT_VERSION))
  assert_equal(2, eglQueryContext(display, context, :EGL_CONTEXT_CLIENT_VERSION))
  context
end

def destroy_context(display, context)
  assert_true(eglDestroyContext(display, context))
end

def make_current(display, drawsurface, readsurface, context)
  assert_true(eglMakeCurrent(display, drawsurface, readsurface, context))

  if context
    assert_equal(display, eglGetCurrentDisplay())
  end
  assert_equal(drawsurface, eglGetCurrentSurface(:EGL_DRAW))
  assert_equal(readsurface, eglGetCurrentSurface(EGL_READ))
  assert_equal(context, eglGetCurrentContext())
end

assert('initialize-terminate') do
  display = initialize_egl
  config  = create_config(display)
  surface = create_pbuffer_surface(display, config)
  context = create_context(display, config, nil);

  assert_nil(eglGetCurrentContext)
  assert_nil(eglGetCurrentDisplay)
  assert_nil(eglGetCurrentSurface(:EGL_DRAW))
  assert_nil(eglGetCurrentSurface(EGL_READ))

  make_current(display, surface, surface, context)
  assert_true(eglSwapBuffers(display, surface))
  make_current(display, nil, nil, nil)

  assert_true(eglWaitClient())
  assert_true(eglWaitGL())
  assert_true(eglWaitNative(EGL_CORE_NATIVE_ENGINE))

  destroy_context(display, context)
  destroy_surface(display, surface)
  terminate_egl(display)
end

