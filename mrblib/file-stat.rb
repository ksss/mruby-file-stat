class File
  class Stat
    IRWXUGO = (IRWXU|IRWXG|IRWXO)
    IALLUGO = (ISUID|ISGID|ISVTX|IRWXUGO)
    IRUGO = (IRUSR|IRGRP|IROTH)
    IWUGO = (IWUSR|IWGRP|IWOTH)
    IXUGO = (IXUSR|IXGRP|IXOTH)

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

    {
      symlink?:   IFLNK,
      file?:      IFREG,
      directory?: IFDIR,
      chardev?:   IFCHR,
      blockdev?:  IFBLK,
      pipe?:      IFIFO,
      socket?:    IFSOCK,
    }.each do |m, c|
      if IFMT && c
        define_method(m) do
          (mode & IFMT) == c
        end
      else
        define_method(m) do
          nil
        end
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
      return nil unless ISUID
      (mode & ISUID) != 0
    end

    def setgid?
      return nil unless ISGID
      (mode & ISGID) != 0
    end

    def sticky?
      return nil unless ISVTX
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
    rescue TypeError
      "unknown"
    end
  end
end
