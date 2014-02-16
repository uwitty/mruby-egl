include EGL

def config_to_s(display, config)
  config.inspect + " {" +
  ", EGL_RED_SIZE:#{eglGetConfigAttrib(display, config, EGL_RED_SIZE)}" +
  ", EGL_GREEN_SIZE:#{eglGetConfigAttrib(display, config, EGL_GREEN_SIZE)}" +
  ", EGL_BLUE_SIZE:#{eglGetConfigAttrib(display, config, EGL_BLUE_SIZE)}" +
  ", EGL_ALPHA_SIZE:#{eglGetConfigAttrib(display, config, EGL_ALPHA_SIZE)}" +
  ", EGL_DEPTH_SIZE:#{eglGetConfigAttrib(display, config, EGL_DEPTH_SIZE)}" +
  #", EGL_MAX_PBUFFER_WIDTH:#{eglGetConfigAttrib(display, config, EGL_MAX_PBUFFER_WIDTH)}" +
  #", EGL_MAX_PBUFFER_HEIGHT:#{eglGetConfigAttrib(display, config, EGL_MAX_PBUFFER_HEIGHT)}" +
  #", EGL_SURFACE_TYPE:#{eglGetConfigAttrib(display, config, EGL_SURFACE_TYPE)}" +
  ", EGL_STENCIL_SIZE:#{eglGetConfigAttrib(display, config, EGL_STENCIL_SIZE)}" +
  ", EGL_BIND_TO_TEXTURE_RGBA:#{eglGetConfigAttrib(display, config, EGL_BIND_TO_TEXTURE_RGBA)}" +
  "}"
end

display = eglGetDisplay(EGL_DEFAULT_DISPLAY)
print "display:#{display}\n"

initialized, major, minor = eglInitialize(display)
print "initialized:#{initialized}, major:#{major}, minor:#{minor}\n"

print "queryAPI:0x#{eglQueryAPI().to_s(16)}\n"
print "queryString(EGL_CLIENT_APIS):\"#{eglQueryString(display, EGL_CLIENT_APIS)}\"\n"
print "queryString(EGL_VENDOR):\"#{eglQueryString(display, EGL_VENDOR)}\"\n"
print "queryString(EGL_VERSION):\"#{eglQueryString(display, EGL_VERSION)}\"\n"
print "queryString(EGL_EXTENSIONS):\"#{eglQueryString(display, EGL_EXTENSIONS)}\"\n"

configs = eglChooseConfig(display, nil)
if configs
  print "confings:[num:#{configs.size()}, \n"
  for i in 0...configs.size()
    print "  #{config_to_s(display, configs[i])}, \n"
  end
  print "]\n"
end

eglTerminate(display)

