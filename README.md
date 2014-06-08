# mruby-file-stat

**File::Stat** class in mruby

```ruby
stat = File::Stat.new('filename') # or File.stat('filename')
p stat.size #=> file size(byte)
p stat.mtime #=> last modify time
p stat.file? #=> is this file?
p stat.dir? #=> is this directory?
p stat.executable? #=> can execute this?
```

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

