class File
  class Stat
    include Comparable
    include File::Stat::Constants

    def <=>(other)
      if other.kind_of?(self.class)
        self.mtime <=> other.mtime
      else
        nil
      end
    end

    def inspect
      _dev = dev
      _dev = "0x#{_dev.to_s(16)}" if _dev.kind_of?(Fixnum)
      _mode = mode
      _mode = "0#{_mode.to_s(8)}" if _mode.kind_of?(Fixnum)
      _rdev = rdev
      _rdev = "0x#{_rdev.to_s(16)}" if _rdev.kind_of?(Fixnum)

      stats = {
        'dev' => _dev,
        'ino' => ino,
        'mode' => _mode,
        'nlink' => nlink,
        'uid' => uid,
        'gid' => gid,
        'rdev' => _rdev,
        'size' => size,
        'blksize' => blksize,
        'blocks' => blocks,
        'atime' => atime,
        'mtime' => mtime,
        'ctime' => ctime,
      }
      if respond_to? :birthtime
        stats['birthtime'] = birthtime
      end

      "#<#{self.class.to_s} #{stats.map{|k, v| "#{k}=#{v}"}.join(', ')}>"
    end

    def size?
      s = size
      s == 0 ? nil : s
    end

    def zero?
      size == 0
    end

    def symlink?
      (mode & IFMT) == IFLNK
    end

    def file?
      (mode & IFMT) == IFREG
    end

    def directory?
      (mode & IFMT) == IFDIR
    end

    def chardev?
      (mode & IFMT) == IFCHR
    end

    def blockdev?
      (mode & IFMT) == IFBLK
    end

    def pipe?
      (mode & IFMT) == IFIFO
    end

    def socket?
      (mode & IFMT) == IFSOCK
    end

    def owned?
      uid == Process.euid
    end

    def owned_real?
      uid == Process.uid
    end

    def readable?
      if Process.euid == 0
        true
      elsif owned?
        (mode & IRUSR) == IRUSR
      elsif grpowned?
        (mode & IRGRP) == IRGRP
      else
        (mode & IROTH) == IROTH
      end
    end

    def writable?
      if Process.euid == 0
        true
      elsif owned?
        (mode & IWUSR) == IWUSR
      elsif grpowned?
        (mode & IWGRP) == IWGRP
      else
        (mode & IWOTH) == IWOTH
      end
    end

    def executable?
      if Process.euid == 0
        (mode & IXUGO) == IXUGO
      elsif owned?
        (mode & IXUSR) == IXUSR
      elsif grpowned?
        (mode & IXGRP) == IXGRP
      else
        (mode & IXOTH) == IXOTH
      end
    end

    def executable_real?
      if Process.uid == 0
        (mode & IXUGO) == IXUGO
      elsif owned_real?
        (mode & IXUSR) == IXUSR
      elsif grpowned?
        (mode & IXGRP) == IXGRP
      else
        (mode & IXOTH) == IXOTH
      end
    end

    def world_readable?
      m = mode
      if (m & IROTH) == IROTH
        m & (IRUGO|IWUGO|IXUGO)
      else
        nil
      end
    end

    def world_writable?
      m = mode
      if (m & IWOTH) == IWOTH
        m & (IRUGO|IWUGO|IXUGO)
      else
        nil
      end
    end

    def setuid?
      (mode & ISUID) == ISUID
    end

    def setgid?
      (mode & ISGID) == ISGID
    end

    def sticky?
      (mode & ISVTX) == ISVTX
    end

    def ftype
      case mode & IFMT
      when IFSOCK
        "socket"
      when IFLNK
        "link"
      when IFREG
        "file"
      when IFBLK
        "blockSpecial"
      when IFDIR
        "directory"
      when IFCHR
        "characterSpecial"
      when IFIFO
        "fifo"
      else
        "unknown"
      end
    end
  end
end
