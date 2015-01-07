MRuby::Build.new do |conf|
  toolchain :gcc
  conf.gembox 'default'
  conf.gem :github => "iij/mruby-io"
  conf.gem '../mruby-file-stat'
end
