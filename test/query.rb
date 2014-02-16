include EGL
include EGL::Constants

assert('eglQueryAPI') do
  api = eglQueryAPI()
  assert_true(api)
end

assert('eglQueryString') do
  display = eglGetDisplay(EGL_DEFAULT_DISPLAY)
  assert_true(display)
  initialized, major, minor = eglInitialize(display)
  assert_true(initialized)

  apis = eglQueryString(display, EGL_CLIENT_APIS)
  assert_equal(EGL_SUCCESS, eglGetError())
  assert_true(apis)
  assert_equal(apis, eglQueryString(display, :EGL_CLIENT_APIS))

  vendor = eglQueryString(display, EGL_VENDOR)
  assert_equal(EGL_SUCCESS, eglGetError())
  assert_true(vendor)
  assert_equal(vendor, eglQueryString(display, :EGL_VENDOR))

  version = eglQueryString(display, EGL_VERSION)
  assert_equal(EGL_SUCCESS, eglGetError())
  assert_true(version)
  assert_equal(version, eglQueryString(display, :EGL_VERSION))

  extensions = eglQueryString(display, EGL_EXTENSIONS)
  assert_equal(EGL_SUCCESS, eglGetError())
  assert_true(extensions)
  assert_equal(extensions, eglQueryString(display, :EGL_EXTENSIONS))

  assert_true(eglTerminate(display))
end

