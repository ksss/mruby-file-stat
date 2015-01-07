require 'mkmf'
require 'rake/clean'

MRuby::Gem::Specification.new('mruby-file-stat') do |spec|
  spec.license = 'MIT'
  spec.author  = 'ksss <co000ri@gmail.com>'
  spec.add_dependency('mruby-time')
  spec.add_dependency('mruby-io')

  extconf = "#{File.dirname(__FILE__)}/src/extconf.h"
  unless File.exist? extconf
    have_struct_member "struct stat", "st_birthtimespec", "sys/stat.h"
    create_header extconf
  end
  CLOBBER << extconf
end
