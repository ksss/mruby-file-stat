class File
  class Stat
    include Comparable

    def <=>(other)
      if other.kind_of?(self.class)
        return self.mtime <=> other.mtime
      end
      nil
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
  end
end

class File
  def self.stat(fname)
    File::Stat.new(fname)
  end
end
