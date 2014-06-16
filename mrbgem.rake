require 'mkmf'

MRuby::Gem::Specification.new('mruby-file-stat') do |spec|
  spec.license = 'MIT'
  spec.author  = 'ksss <co000ri@gmail.com>'

  # check timespec
  have_struct_member 'struct stat', 'st_atim.tv_nsec'
  have_struct_member 'struct stat', 'st_atimespec.tv_nsec'
  have_struct_member 'struct stat', 'st_atimensec'
  have_struct_member 'struct stat', 'st_mtim.tv_nsec'
  have_struct_member 'struct stat', 'st_mtimespec.tv_nsec'
  have_struct_member 'struct stat', 'st_mtimensec'
  have_struct_member 'struct stat', 'st_ctim.tv_nsec'
  have_struct_member 'struct stat', 'st_ctimespec.tv_nsec'
  have_struct_member 'struct stat', 'st_ctimensec'

  create_header("#{File.dirname(__FILE__)}/src/extconf.h")
end
