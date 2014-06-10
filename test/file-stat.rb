assert 'File::Stat.new' do
  assert_kind_of File::Stat, File::Stat.new('README.md')
  assert_raise(RuntimeError){ File::Stat.new('unknown.file') }
end

assert 'File.stat' do
  assert_kind_of File::Stat, File.stat('README.md')
end

assert 'File.lstat' do
  assert_kind_of File::Stat, File.lstat('README.md')
end

assert 'File::Stat#initialize_copy' do
  orig = File::Stat.new('README.md')
  copy = orig.dup
  assert_equal orig.inspect, copy.inspect
end

assert 'File::Stat#<=>' do
  stat1 = File::Stat.new('README.md')
  stat2 = File::Stat.new('README.md')
  assert_equal 0, stat1.<=>(stat2)
end

assert 'File::Stat#dev' do
  stat = File::Stat.new('README.md')
  assert_kind_of Fixnum, stat.dev
end

assert 'File::Stat#dev_major' do
  stat = File::Stat.new('README.md')
  assert_include [Fixnum, NilClass], stat.dev_major.class
end

assert 'File::Stat#dev_minor' do
  stat = File::Stat.new('README.md')
  assert_include [Fixnum, NilClass], stat.dev_minor.class
end

assert 'File::Stat#ino' do
  stat = File::Stat.new('README.md')
  assert_kind_of Fixnum, stat.ino
end

assert 'File::Stat#mode' do
  stat = File::Stat.new('README.md')
  assert_kind_of Fixnum, stat.mode
end

assert 'File::Stat#nlink' do
  stat = File::Stat.new('README.md')
  assert_kind_of Fixnum, stat.nlink
end

assert 'File::Stat#uid' do
  stat = File::Stat.new('README.md')
  assert_kind_of Fixnum, stat.uid
end

assert 'File::Stat#gid' do
  stat = File::Stat.new('README.md')
  assert_kind_of Fixnum, stat.gid
end

assert 'File::Stat#rdev' do
  stat = File::Stat.new('README.md')
  assert_kind_of Fixnum, stat.rdev
end

assert 'File::Stat#rdev_major' do
  stat = File::Stat.new('README.md')
  assert_include [Fixnum, NilClass], stat.rdev_major.class
end

assert 'File::Stat#rdev_minor' do
  stat = File::Stat.new('README.md')
  assert_include [Fixnum, NilClass], stat.rdev_minor.class
end

assert 'File::Stat#blocks' do
  stat = File::Stat.new('README.md')
  assert_kind_of Fixnum, stat.blocks
end

assert 'File::Stat#atime' do
  stat = File::Stat.new('README.md')
  assert_true 0 < stat.atime
end

assert 'File::Stat#mtime' do
  stat = File::Stat.new('README.md')
  assert_true 0 < stat.mtime
end

assert 'File::Stat#ctime' do
  stat = File::Stat.new('README.md')
  assert_true 0 < stat.ctime
end

assert 'File::Stat#size' do
  stat = File::Stat.new('README.md')
  assert_true 0 < stat.size
end

assert 'File::Stat#blksize' do
  stat = File::Stat.new('README.md')
  assert_true 0 < stat.blksize
end

assert 'File::Stat#inspect' do
  stat = File::Stat.new('README.md')
  assert_kind_of String, stat.inspect
end

assert 'File::Stat#ftype' do
  stat = File::Stat.new('README.md')
  assert_equal "file", stat.ftype

  stat = File::Stat.new('bin')
  assert_equal "directory", stat.ftype
end

assert 'File::Stat#directory?' do
  stat = File::Stat.new('README.md')
  assert_false stat.directory?

  stat = File::Stat.new('bin')
  assert_true stat.directory?
end

assert 'File::Stat#readable?' do
  stat = File::Stat.new('README.md')
  assert_true stat.readable?
end

assert 'File::Stat#readable_real?' do
  stat = File::Stat.new('README.md')
  assert_true stat.readable_real?
end

assert 'File::Stat#writable?' do
  stat = File::Stat.new('README.md')
  assert_true stat.writable?
end

assert 'File::Stat#writable_real?' do
  stat = File::Stat.new('README.md')
  assert_true stat.writable_real?
end

assert 'File::Stat#executable?' do
  stat = File::Stat.new('README.md')
  assert_false stat.executable?
end

assert 'File::Stat#writable_real?' do
  stat = File::Stat.new('README.md')
  assert_false stat.executable_real?
end

assert 'File::Stat#file?' do
  stat = File::Stat.new('README.md')
  assert_true stat.file?

  stat = File::Stat.new('bin')
  assert_false stat.file?
end

assert 'File::Stat#zero?' do
  stat = File::Stat.new('README.md')
  assert_false stat.zero?
end

assert 'File::Stat#size?' do
  stat = File::Stat.new('README.md')
  assert_true 0 < stat.size?
end

assert 'File::Stat#owned?' do
  stat = File::Stat.new('README.md')
  assert_true stat.owned?
end

assert 'File::Stat#grpowned?' do
  stat = File::Stat.new('README.md')
  assert_true stat.grpowned?
end

assert 'File::Stat#pipe?' do
  stat = File::Stat.new('README.md')
  assert_false stat.pipe?
end

assert 'File::Stat#symlink?' do
  stat = File::Stat.new('README.md')
  assert_false stat.symlink?
end

assert 'File::Stat#socket?' do
  stat = File::Stat.new('README.md')
  assert_false stat.socket?
end

assert 'File::Stat#blockdev?' do
  stat = File::Stat.new('README.md')
  assert_false stat.blockdev?
end

assert 'File::Stat#chardev?' do
  stat = File::Stat.new('README.md')
  assert_false stat.chardev?

  stat = File::Stat.new('/dev/tty')
  assert_true stat.chardev?
end

assert 'File::Stat#setuid?' do
  stat = File::Stat.new('README.md')
  assert_false stat.setuid?
end

assert 'File::Stat#setuid?' do
  stat = File::Stat.new('README.md')
  assert_false stat.setgid?
end

assert 'File::Stat#sticky?' do
  stat = File::Stat.new('README.md')
  assert_false stat.sticky?
end
