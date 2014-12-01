# mruby-file-stat

[![Build Status](https://travis-ci.org/ksss/mruby-file-stat.svg?branch=master)](https://travis-ci.org/ksss/mruby-file-stat)

**File::Stat** class in mruby

```ruby
stat = File::Stat.new('filename') # or File.stat('filename')
p stat.dev #=> device id
p stat.dev_major #=> device major id
p stat.dev_minor #=> device minor id
p stat.ino #=> i-node number
p stat.mode #=> permission value (st_mode)
p stat.nlink #=> hard link count
p stat.uid #=> user id
p stat.gid #=> group id
p stat.rdev #=> device type
p stat.rdev_major #=> rdev major id
p stat.rdev_minor #=> rdev minor id
p stat.atime #=> last access time
p stat.mtime #=> last modify time
p stat.ctime #=> last change attribute time
p stat.birthtime #=> file created time
p stat.size #=> file size(byte)
p stat.blksize #=> file I/O block size
p stat.blocks #=> attached block num
p stat.grpowned #=> same gid?
p stat.<=> #=> comparate mtime (-1,0,1 or nil)
p stat.size?
p stat.zero?
p stat.symlink?
p stat.file?
p stat.directory?
p stat.chardev?
p stat.blockdev?
p stat.pipe?
p stat.socket?
p stat.owned?
p stat.owned_real?
p stat.readable?
p stat.readable_real?
p stat.writable?
p stat.writable_real?
p stat.executable?
p stat.executable_real?
p stat.world_readable?
p stat.world_writable?
p stat.setuid?
p stat.setgid?
p stat.sticky?
p stat.ftype #=> socket, link, file, blockSpecial, directory, characterSpecial, fifo or unknown
```

This library is wrap of struct stat.

## Installation

### use github repository

Write in /mruby/build_config.rb

```ruby
MRuby::Build.new do |conf|
  conf.gem :github => 'ksss/mruby-file-stat', :branch => 'master'
end
```

## License

See [https://github.com/ruby/ruby/blob/trunk/file.c](https://github.com/ruby/ruby/blob/trunk/file.c)

## Doc

[http://ruby-doc.org/core-2.1.5/File/Stat.html](http://ruby-doc.org/core-2.1.5/File/Stat.html)
