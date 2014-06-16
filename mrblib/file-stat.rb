class File
  class Stat
    include File::Stat::Constants
    include Comparable

    def <=>(other)
      if other.kind_of?(self.class)
        return self.mtime <=> other.mtime
      end
      nil
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
        (mode & IRUSR) != 0
      elsif grpowned?
        (mode & IRGRP) != 0
      else
        (mode & IROTH) == 0
      end
    end

    def readable_real?
      if Process.uid == 0
        true
      elsif owned_real?
        (mode & IRUSR) != 0
      elsif grpowned?
        (mode & IRGRP) != 0
      else
        (mode & IROTH) == 0
      end
    end

    def writable?
      if Process.euid == 0
        true
      elsif owned?
        (mode & IWUSR) != 0
      elsif grpowned?
        (mode & IWGRP) != 0
      else
        (mode & IWOTH) == 0
      end
    end

    def writable_real?
      if Process.uid == 0
        true
      elsif owned_real?
        (mode & IWUSR) != 0
      elsif grpowned?
        (mode & IWGRP) != 0
      else
        (mode & IWOTH) == 0
      end
    end

    def executable?
      if Process.euid == 0
        (mode & IXUGO) != 0
      elsif owned?
        (mode & IXUSR) != 0
      elsif grpowned?
        (mode & IXGRP) != 0
      else
        (mode & IXOTH) == 0
      end
    end

    def executable_real?
      if Process.uid == 0
        (mode & IXUGO) != 0
      elsif owned_real?
        (mode & IXUSR) != 0
      elsif grpowned?
        (mode & IXGRP) != 0
      else
        (mode & IXOTH) == 0
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
      (mode & ISUID) != 0
    end

    def setgid?
      (mode & ISGID) != 0
    end

    def sticky?
      (mode & ISVTX) != 0
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
