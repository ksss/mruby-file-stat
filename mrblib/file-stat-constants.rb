class File
  class Stat
    module Constants
      IRWXUGO = (IRWXU|IRWXG|IRWXO)
      IALLUGO = (ISUID|ISGID|ISVTX|IRWXUGO)
      IRUGO = (IRUSR|IRGRP|IROTH)
      IWUGO = (IWUSR|IWGRP|IWOTH)
      IXUGO = (IXUSR|IXGRP|IXOTH)
    end
  end
end
