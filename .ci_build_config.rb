def gem_config(conf)
  conf.gem :core => "mruby-time"
  conf.gem '../'
end

MRuby::Build.new do |conf|
  toolchain :gcc
  conf.enable_test

  gem_config(conf)
end
