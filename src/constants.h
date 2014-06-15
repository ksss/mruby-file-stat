#ifndef FILE_STAT_CONSTANTS_H
#  define FILE_STAT_CONSTANTS_H


/**
 * define default value when system not defined
 */
#ifndef S_IFMT
# define S_IFMT 0170000
#endif
#ifndef S_IFSOCK
# define S_IFSOCK 0140000
#endif
#ifndef S_IFLNK
# define S_IFLNK 0120000
#endif
#ifndef S_IFREG
# define S_IFREG 0100000
#endif
#ifndef S_IFBLK
# define S_IFBLK 060000
#endif
#ifndef S_IFDIR
# define S_IFDIR 040000
#endif
#ifndef S_IFCHR
# define S_IFCHR 020000
#endif
#ifndef S_IFIFO
# define S_IFIFO 010000
#endif
#ifndef S_ISUID
# define S_ISUID 04000
#endif
#ifndef S_ISGID
# define S_ISGID 02000
#endif
#ifndef S_ISVTX
# define S_ISVTX 01000
#endif

#ifndef S_IRWXU
# define S_IRWXU 0700
#endif
#ifndef S_IRUSR
# define S_IRUSR 0400
#endif
#ifndef S_IWUSR
# define S_IWUSR 0200
#endif
#ifndef S_IXUSR
# define S_IXUSR 0100
#endif

#ifndef S_IRWXG
# define S_IRWXG 070
#endif
#ifndef S_IRGRP
# define S_IRGRP 040
#endif
#ifndef S_IWGRP
# define S_IWGRP 020
#endif
#ifndef S_IXGRP
# define S_IXGRP 010
#endif

#ifndef S_IRWXO
# define S_IRWXO 07
#endif
#ifndef S_IROTH
# define S_IROTH 04
#endif
#ifndef S_IWOTH
# define S_IWOTH 02
#endif
#ifndef S_IXOTH
# define S_IXOTH 01
#endif


#endif /* ifndef FILE_STAT_CONSTANTS_H */
