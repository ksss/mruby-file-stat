class File
  class Stat
    include Comparable

    def <=>(other)
      if other.kind_of?(self.class)
        return self.mtime <=> other.mtime
      end
      nil
    end
  end

  def self.stat(fname)
    File::Stat.new(fname)
  end
end
