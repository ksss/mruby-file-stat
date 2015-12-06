require 'mkmf'
require 'rake/clean'

MRuby::Gem::Specification.new('mruby-file-stat') do |spec|
  spec.license = 'MIT'
  spec.author  = 'ksss <co000ri@gmail.com>'
  spec.add_dependency('mruby-time')

  extconf = "#{File.dirname(__FILE__)}/src/extconf.h"
  unless File.exist? extconf
    if RUBY_PLATFORM !~ /mingw|mswin/
      have_struct_member "struct stat", "st_birthtimespec", "sys/stat.h"
    end
    create_header extconf
  end
  CLOBBER << extconf
end
