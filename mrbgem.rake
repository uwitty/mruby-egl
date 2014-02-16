MRuby::Gem::Specification.new('mruby-egl') do |spec|
  spec.license = 'MIT'
  spec.authors = '@uwitty'

  # Add compile flags
  # spec.cc.flags << '-g'
  #spec.cc.flags << `pkg-config --cflags directfb`.strip
  spec.linker.flags << `pkg-config --libs egl glesv2`.strip
end
