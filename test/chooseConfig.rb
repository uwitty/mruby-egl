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

assert('chooseConfig') do
  display = initialize_egl

  attrs = Hash.new
  attrs[EGL_RED_SIZE]   = 8
  attrs[EGL_GREEN_SIZE] = 8
  attrs[EGL_BLUE_SIZE]  = 8
  attrs[EGL_ALPHA_SIZE] = EGL_DONT_CARE
  attrs[EGL_DEPTH_SIZE] = 24
  config = eglChooseConfig(display, attrs)
  assert_true(config)

  terminate_egl(display)
end

assert('chooseConfig_sym') do
  display = initialize_egl

  attrs = {EGL_RED_SIZE:8, EGL_GREEN_SIZE:8, EGL_BLUE_SIZE:8, EGL_ALPHA_SIZE:EGL_DONT_CARE, EGL_DEPTH_SIZE:24}
  config = eglChooseConfig(display, attrs)
  assert_true(config)

  terminate_egl(display)
end

assert('chooseConfig_ary') do
  display = initialize_egl

  attrs = [EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, EGL_DONT_CARE, EGL_DEPTH_SIZE, 24]
  config = eglChooseConfig(display, attrs)
  assert_true(config)

  terminate_egl(display)
end

assert('chooseConfig_ary_sym') do
  display = initialize_egl

  attrs = [:EGL_RED_SIZE, 8, :EGL_GREEN_SIZE, 8, :EGL_BLUE_SIZE, 8, :EGL_ALPHA_SIZE, EGL_DONT_CARE, :EGL_DEPTH_SIZE, 24]
  config = eglChooseConfig(display, attrs)
  assert_true(config)

  terminate_egl(display)
end

assert('invalid attr') do
  display = initialize_egl

  attrs = 123456
  assert_raise(TypeError) do
    config = eglChooseConfig(display, attrs)
  end

  terminate_egl(display)
end

