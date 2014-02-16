module EGL
  include EGL::Constants

  def eglChooseConfig(display, attr_list)
    _eglChooseConfig(display, to_attr_array(attr_list))
  end

  def eglCreateContext(display, config, shared_context, attr_list)
    _eglCreateContext(display, config, shared_context, to_attr_array(attr_list))
  end

  def eglCreatePbufferFromClientBuffer(display, buftype, buffer, config, attr_list)
    _eglCreatePbufferFromClientBuffer(display, buftype, buffer, config, to_attr_array(attr_list))
  end

  def eglCreatePbufferSurface(display, config, attr_list)
    _eglCreatePbufferSurface(display, config, to_attr_array(attr_list))
  end

  def eglCreatePixmapSurface(display, config, native_pixmap, attr_list)
    _eglCreatePixmapSurface(display, config, native_pixmap, to_attr_array(attr_list))
  end

  def eglCreateWindowSurface(display, config, native_window, attr_list)
    _eglCreateWindowSurface(display, config, native_window, to_attr_array(attr_list))
  end

  def eglGetConfigAttrib(display, config, attrib)
    _eglGetConfigAttrib(display, config, to_const_value(attrib))
  end

  def eglGetCurrentSurface(readdraw)
    _eglGetCurrentSurface(to_const_value(readdraw))
  end

  def eglQueryContext(display, context, attrib)
    _eglQueryContext(display, context, to_const_value(attrib))
  end

  def eglQueryString(display, name)
    _eglQueryString(display, to_const_value(name))
  end

  def eglQuerySurface(display, surface, attrib)
    _eglQuerySurface(display, surface, to_const_value(attrib))
  end

  def to_const_value(v)
    (v.class == Symbol)? Constants.const_get(v) : v
  end

  def to_attr_array(attr_list)
    if attr_list.kind_of?(Array)
      a = attr_list.dup
      0.step(attr_list.size() - 1, 2) do |i|
        a[i] = to_const_value(a[i])
      end
      if attr_list.last != EGL_NONE
        a << EGL_NONE
      end
    elsif attr_list.kind_of?(Hash)
      a = Array.new
      attr_list.each do |key, value|
        a << to_const_value(key)
        a << value
      end
      a << EGL_NONE
      a
    elsif attr_list.nil?
      nil
    else
      raise TypeError, "attr_list should be a kind of Array or Hash"
    end
  end
end

