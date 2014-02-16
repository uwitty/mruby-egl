assert('EGL module') do
  Object.const_defined?(:EGL)
  EGL.const_defined?(:Constants)
end

assert('EGL constants') do
  EGL::Constants.constants.size() > 0
end

