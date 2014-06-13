class File
  class Stat
    S_IRWXUGO = (S_IRWXU|S_IRWXG|S_IRWXO)
    S_IALLUGO = (S_ISUID|S_ISGID|S_ISVTX|S_IRWXUGO)
    S_IRUGO = (S_IRUSR|S_IRGRP|S_IROTH)
    S_IWUGO = (S_IWUSR|S_IWGRP|S_IWOTH)
    S_IXUGO = (S_IXUSR|S_IXGRP|S_IXOTH)

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
      symlink?:   S_IFLNK,
      file?:      S_IFREG,
      directory?: S_IFDIR,
      chardev?:   S_IFCHR,
      blockdev?:  S_IFBLK,
      pipe?:      S_IFIFO,
      socket?:    S_IFSOCK,
    }.each do |m, c|
      if S_IFMT && c
        define_method(m) do
          (mode & S_IFMT) == c
        end
      else
        define_method(m) do
          nil
        end
      end
    end

    def world_readable?
      m = mode
      if (m & S_IROTH) == S_IROTH
        m & (S_IRUGO|S_IWUGO|S_IXUGO)
      else
        nil
      end
    end

    def world_writable?
      m = mode
      if (m & S_IWOTH) == S_IWOTH
        m & (S_IRUGO|S_IWUGO|S_IXUGO)
      else
        nil
      end
    end

    def setuid?
      return nil unless S_ISUID
      (mode & S_ISUID) != 0
    end

    def setgid?
      return nil unless S_ISGID
      (mode & S_ISGID) != 0
    end

    def sticky?
      return nil unless S_ISVTX
      (mode & S_ISVTX) != 0
    end

    def ftype
      case mode & S_IFMT
      when S_IFSOCK
        "socket"
      when S_IFLNK
        "link"
      when S_IFREG
        "file"
      when S_IFBLK
        "blockSpecial"
      when S_IFDIR
        "directory"
      when S_IFCHR
        "characterSpecial"
      when S_IFIFO
        "fifo"
      else
        "unknown"
      end
    rescue TypeError
      "unknown"
    end
  end
end
