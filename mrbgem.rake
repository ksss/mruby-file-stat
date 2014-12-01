require 'mkmf'

MRuby::Gem::Specification.new('mruby-file-stat') do |spec|
  spec.license = 'MIT'
  spec.author  = 'ksss <co000ri@gmail.com>'

  have_struct_member "struct stat", "st_birthtimespec", "sys/stat.h"
  create_header "#{File.dirname(__FILE__)}/src/extconf.h"
end
