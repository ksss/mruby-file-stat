/**
 * original is https://github.com/ruby/ruby/blob/trunk/file.c
 */

#include "mruby.h"
#include "mruby/string.h"
#include "mruby/data.h"
#include "mruby/error.h"
#include "mruby/class.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define STAT(p,s) stat(p,s)
#define GETGROUPS_T gid_t
#define MRB_MAX_GROUPS (65536)

struct mrb_data_type mrb_stat_type = { "File::Stat", mrb_free };

static struct stat *
mrb_stat_alloc(mrb_state *mrb)
{
  return (struct stat *)mrb_malloc(mrb, sizeof(struct stat));
}

static mrb_value
file_s_lstat(mrb_state *mrb, mrb_value klass)
{
  struct RClass *file_class;
  struct RClass *stat_class;
  struct stat st, *ptr;
  mrb_value fname;

  mrb_get_args(mrb, "S", &fname);

  if (lstat(RSTRING_PTR(fname), &st) == -1) {
    mrb_sys_fail(mrb, RSTRING_PTR(fname));
  }

  file_class = mrb_class_ptr(klass);
  stat_class = mrb_class_get_under(mrb, file_class, "Stat");
  ptr = mrb_stat_alloc(mrb);
  *ptr = st;

  return mrb_obj_value(Data_Wrap_Struct(mrb, stat_class, &mrb_stat_type, ptr));
}

static mrb_value
stat_initialize(mrb_state *mrb, mrb_value self)
{
  struct stat st, *ptr;
  mrb_value fname;

  mrb_get_args(mrb, "S", &fname);

  if (STAT(RSTRING_PTR(fname), &st) == -1) {
    mrb_sys_fail(mrb, RSTRING_PTR(fname));
  }

  ptr = DATA_PTR(self);
  if (ptr) {
    mrb_free(mrb, ptr);
  }

  ptr = mrb_stat_alloc(mrb);
  *ptr = st;

  DATA_TYPE(self) = &mrb_stat_type;
  DATA_PTR(self) = ptr;

  return mrb_nil_value();
}

static mrb_value
stat_initialize_copy(mrb_state *mrb, mrb_value copy)
{
  mrb_value orig;

  mrb_get_args(mrb, "o", &orig);

  if (mrb_obj_equal(mrb, copy, orig)) return copy;

  if (!mrb_obj_is_instance_of(mrb, orig, mrb_obj_class(mrb, copy))) {
    mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
  }

  if (DATA_PTR(copy)) {
    mrb_free(mrb, DATA_PTR(copy));
    DATA_PTR(copy) = 0;
  }

  if (DATA_PTR(orig)) {
    DATA_PTR(copy) = mrb_malloc(mrb, sizeof(struct stat));
    DATA_TYPE(copy) = &mrb_stat_type;
    *(struct stat *)DATA_PTR(copy) = *(struct stat *)DATA_PTR(orig);
  }
  return copy;
}

static struct stat *
get_stat(mrb_state *mrb, mrb_value self)
{
  struct stat *st;

  Data_Get_Struct(mrb, self, &mrb_stat_type, st);
  if (!st) mrb_raise(mrb, E_TYPE_ERROR, "uninitialized File::Stat");
  return st;
}

static mrb_value
check_fixnum_overflow(mrb_state *mrb, long long t)
{
  if (MRB_INT_MIN <= t && t <= MRB_INT_MAX) {
    return mrb_fixnum_value((mrb_int)t);
  } else {
    return mrb_nil_value(); // maybe overflow
  }
}

static mrb_value
mrb_ll2num(mrb_state *mrb, long long t)
{
  if (MRB_INT_MIN <= t && t <= MRB_INT_MAX) {
    return mrb_fixnum_value((mrb_int)t);
  } else {
    return mrb_float_value(mrb, (mrb_float)t);
  }
}

static mrb_value
stat_dev(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(get_stat(mrb, self)->st_dev);
}

static mrb_value
stat_dev_major(mrb_state *mrb, mrb_value self)
{
#if defined(major)
  return mrb_fixnum_value(major(get_stat(mrb, self)->st_dev));
#else
  return mrb_nil_value(); // NotImplemented
#endif
}

static mrb_value
stat_dev_minor(mrb_state *mrb, mrb_value self)
{
#if defined(minor)
  return mrb_fixnum_value(minor(get_stat(mrb, self)->st_dev));
#else
  return mrb_nil_value(); // NotImplemented
#endif
}

static mrb_value
stat_ino(mrb_state *mrb, mrb_value self)
{
  return check_fixnum_overflow(mrb, get_stat(mrb, self)->st_ino);
}

static mrb_value
stat_mode(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(get_stat(mrb, self)->st_mode);
}

static mrb_value
stat_nlink(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(get_stat(mrb, self)->st_nlink);
}

static mrb_value
stat_uid(mrb_state *mrb, mrb_value self)
{
  return check_fixnum_overflow(mrb, get_stat(mrb, self)->st_uid);
}

static mrb_value
stat_gid(mrb_state *mrb, mrb_value self)
{
  return check_fixnum_overflow(mrb, get_stat(mrb, self)->st_gid);
}

static mrb_value
stat_rdev(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(get_stat(mrb, self)->st_rdev);
}

static mrb_value
stat_rdev_major(mrb_state *mrb, mrb_value self)
{
#if defined(major)
  return mrb_fixnum_value(major(get_stat(mrb, self)->st_rdev));
#else
  return mrb_nil_value(); // NotImplemented
#endif
}

static mrb_value
stat_rdev_minor(mrb_state *mrb, mrb_value self)
{
#if defined(minor)
  return mrb_fixnum_value(minor(get_stat(mrb, self)->st_rdev));
#else
  return mrb_nil_value(); // NotImplemented
#endif
}

static mrb_value
stat_atime(mrb_state *mrb, mrb_value self)
{
  return mrb_ll2num(mrb, get_stat(mrb, self)->st_atime);
}

static mrb_value
stat_mtime(mrb_state *mrb, mrb_value self)
{
  return mrb_ll2num(mrb, get_stat(mrb, self)->st_mtime);
}

static mrb_value
stat_ctime(mrb_state *mrb, mrb_value self)
{
  return mrb_ll2num(mrb, get_stat(mrb, self)->st_ctime);
}

static mrb_value
stat_size(mrb_state *mrb, mrb_value self)
{
  return mrb_ll2num(mrb, get_stat(mrb, self)->st_size);
}

static mrb_value
stat_blksize(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(get_stat(mrb, self)->st_blksize);
}

static mrb_value
stat_blocks(mrb_state *mrb, mrb_value self)
{
  return mrb_ll2num(mrb, get_stat(mrb, self)->st_blocks);
}

static mrb_value
stat_inspect(mrb_state *mrb, mrb_value self)
{
  mrb_value str;
  static const struct {
    const char *name;
    mrb_value (*func)(mrb_state*, mrb_value);
  } member [] = {
    {"dev",     stat_dev},
    {"ino",     stat_ino},
    {"mode",    stat_mode},
    {"nlink",   stat_nlink},
    {"uid",     stat_uid},
    {"gid",     stat_gid},
    {"rdev",    stat_rdev},
    {"size",    stat_size},
    {"blksize", stat_blksize},
    {"blocks",  stat_blocks},
    {"atime",   stat_atime},
    {"mtime",   stat_mtime},
    {"ctime",   stat_ctime},
  };
  struct stat *st = get_stat(mrb, self);
  int i;

  if (!st) {
    return mrb_str_new_cstr(mrb, "#<File::Stat uninitialized>");
  }

  str = mrb_str_new_cstr(mrb, "#<");
  mrb_str_cat_cstr(mrb, str, mrb_obj_classname(mrb, self));
  mrb_str_cat_cstr(mrb, str, " ");
  for (i = 0; i < sizeof(member)/sizeof(member[0]); i++) {
    if (0 < i) {
      mrb_str_cat_cstr(mrb, str, ", ");
    }
    mrb_str_cat_cstr(mrb, str, member[i].name);
    mrb_str_cat_cstr(mrb, str, "=");
    mrb_str_concat(mrb, str, mrb_funcall(mrb, member[i].func(mrb, self), "inspect", 0));
  }
  mrb_str_cat_cstr(mrb, str, ">");
  return str;
}

static mrb_value
stat_dir_p(mrb_state *mrb, mrb_value self)
{
  if (S_ISDIR(get_stat(mrb, self)->st_mode))
    return mrb_true_value();
  return mrb_false_value();
}

static mrb_value
stat_size_p(mrb_state *mrb, mrb_value self)
{
  return get_stat(mrb, self)->st_size == 0
    ? mrb_nil_value()
    : mrb_ll2num(mrb, get_stat(mrb, self)->st_size);
}

static mrb_value
stat_owned_p(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value(get_stat(mrb, self)->st_uid == geteuid());
}

static mrb_value
stat_rowned_p(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value(get_stat(mrb, self)->st_uid == getuid());
}

static int
mrb_group_member(mrb_state *mrb, GETGROUPS_T gid)
{
#ifdef _WIN32
  return FALSE;
#else
  int rv = FALSE;
  int groups = 16;
  GETGROUPS_T *gary = NULL;
  int anum = -1;

  if (getgid() == gid || getegid() == gid)
    return TRUE;

  /*
   * On Mac OS X (Mountain Lion), NGROUPS is 16. But libc and kernel
   * accept more larger value.
   * So we don't trunk NGROUPS anymore.
   */
  while (groups <= MRB_MAX_GROUPS) {
    gary = (GETGROUPS_T*)mrb_realloc(mrb, gary, sizeof(GETGROUPS_T) * groups);
    anum = getgroups(groups, gary);
    if (anum != -1 && anum != groups)
      break;
    groups *= 2;
  }
  if (anum == -1)
    return FALSE;

  while (--anum >= 0) {
    if (gary[anum] == gid) {
      rv = TRUE;
      break;
    }
  }

  mrb_free(mrb, gary);
  return rv;
#endif
}

static mrb_value
stat_grpowned_p(mrb_state *mrb, mrb_value self)
{
#ifndef _WIN32
  if (mrb_group_member(mrb, get_stat(mrb, self)->st_gid)) return mrb_true_value();
#endif
  return mrb_false_value();
}

static mrb_value
stat_read_p(mrb_state *mrb, mrb_value self)
{
  struct stat *st = get_stat(mrb, self);

  if (geteuid() == 0)
    return mrb_true_value();
#ifdef S_IRUSR
  if (mrb_test(stat_owned_p(mrb, self)))
    return st->st_mode & S_IRUSR ? mrb_true_value() : mrb_false_value();
#endif
#ifdef S_IRGRP
  if (mrb_test(stat_grpowned_p(mrb, self)))
    return st->st_mode & S_IRGRP ? mrb_true_value() : mrb_false_value();
#endif
#ifdef S_IROTH
  if (!(st->st_mode & S_IROTH))
    return mrb_false_value();
#endif
  return mrb_true_value();
}

static mrb_value
stat_read_real_p(mrb_state *mrb, mrb_value self)
{
  struct stat *st = get_stat(mrb, self);

  if (getuid() == 0)
    return mrb_true_value();
#ifdef S_IRUSR
  if (mrb_test(stat_rowned_p(mrb, self)))
    return st->st_mode & S_IRUSR ? mrb_true_value() : mrb_false_value();
#endif
#ifdef S_IRGRP
  if (mrb_group_member(mrb, get_stat(mrb, self)->st_gid))
    return st->st_mode & S_IRGRP ? mrb_true_value() : mrb_false_value();
#endif
#ifdef S_IROTH
  if (!(st->st_mode & S_IROTH))
    return mrb_false_value();
#endif
  return mrb_true_value();
}

static mrb_value
stat_write_p(mrb_state *mrb, mrb_value self)
{
  struct stat *st = get_stat(mrb, self);

  if (geteuid() == 0)
    return mrb_true_value();
#ifdef S_IRUSR
  if (mrb_test(stat_owned_p(mrb, self)))
    return st->st_mode & S_IWUSR ? mrb_true_value() : mrb_false_value();
#endif
#ifdef S_IRGRP
  if (mrb_test(stat_grpowned_p(mrb, self)))
    return st->st_mode & S_IWGRP ? mrb_true_value() : mrb_false_value();
#endif
#ifdef S_IROTH
  if (!(st->st_mode & S_IWOTH))
    return mrb_false_value();
#endif
  return mrb_true_value();
}

static mrb_value
stat_write_real_p(mrb_state *mrb, mrb_value self)
{
  struct stat *st = get_stat(mrb, self);

  if (getuid() == 0)
    return mrb_true_value();
#ifdef S_IRUSR
  if (mrb_test(stat_rowned_p(mrb, self)))
    return st->st_mode & S_IWUSR ? mrb_true_value() : mrb_false_value();
#endif
#ifdef S_IRGRP
  if (mrb_group_member(mrb, get_stat(mrb, self)->st_gid))
    return st->st_mode & S_IWGRP ? mrb_true_value() : mrb_false_value();
#endif
#ifdef S_IROTH
  if (!(st->st_mode & S_IWOTH))
    return mrb_false_value();
#endif
  return mrb_true_value();
}

static mrb_value
stat_exec_p(mrb_state *mrb, mrb_value self)
{
  struct stat *st = get_stat(mrb, self);

  if (geteuid() == 0)
    return mrb_true_value();
#ifdef S_IRUSR
  if (mrb_test(stat_owned_p(mrb, self)))
    return st->st_mode & S_IXUSR ? mrb_true_value() : mrb_false_value();
#endif
#ifdef S_IRGRP
  if (mrb_test(stat_grpowned_p(mrb, self)))
    return st->st_mode & S_IXGRP ? mrb_true_value() : mrb_false_value();
#endif
#ifdef S_IROTH
  if (!(st->st_mode & S_IXOTH))
    return mrb_false_value();
#endif
  return mrb_true_value();
}

static mrb_value
stat_exec_real_p(mrb_state *mrb, mrb_value self)
{
  struct stat *st = get_stat(mrb, self);

  if (getuid() == 0)
    return mrb_true_value();
#ifdef S_IRUSR
  if (mrb_test(stat_rowned_p(mrb, self)))
    return st->st_mode & S_IXUSR ? mrb_true_value() : mrb_false_value();
#endif
#ifdef S_IRGRP
  if (mrb_group_member(mrb, get_stat(mrb, self)->st_gid))
    return st->st_mode & S_IXGRP ? mrb_true_value() : mrb_false_value();
#endif
#ifdef S_IROTH
  if (!(st->st_mode & S_IXOTH))
    return mrb_false_value();
#endif
  return mrb_true_value();
}

static mrb_value
mrb_file_ftype(mrb_state *mrb, const struct stat *st)
{
  const char *t;

  if (S_ISREG(st->st_mode)) {
    t = "file";
  }
  else if (S_ISDIR(st->st_mode)) {
    t = "directory";
  }
  else if (S_ISCHR(st->st_mode)) {
    t = "characterSpecial";
  }
#ifdef S_ISBLK
  else if (S_ISBLK(st->st_mode)) {
    t = "blockSpecial";
  }
#endif
#ifdef S_ISFIFO
  else if (S_ISFIFO(st->st_mode)) {
    t = "fifo";
  }
#endif
#ifdef S_ISLNK
  else if (S_ISLNK(st->st_mode)) {
    t = "link";
  }
#endif
#ifdef S_ISSOCK
  else if (S_ISSOCK(st->st_mode)) {
    t = "socket";
  }
#endif
  else {
    t = "unknown";
  }

  return mrb_str_new_cstr(mrb, t);
}

static mrb_value
stat_ftype(mrb_state *mrb, mrb_value self)
{
  return mrb_file_ftype(mrb, get_stat(mrb, self));
}

static mrb_value
stat_file_p(mrb_state *mrb, mrb_value self)
{
  if (S_ISREG(get_stat(mrb, self)->st_mode))
    return mrb_true_value();
  return mrb_false_value();
}

static mrb_value
stat_zero_p(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value(get_stat(mrb, self)->st_size == 0);
}

static mrb_value
stat_pipe_p(mrb_state *mrb, mrb_value self)
{
#ifdef S_IFIFO
  if(S_ISFIFO(get_stat(mrb, self)->st_mode))
    return mrb_true_value();
#endif
  return mrb_false_value();
}

static mrb_value
stat_symlink_p(mrb_state *mrb, mrb_value self)
{
#ifdef S_ISLNK
  if (S_ISLNK(get_stat(mrb, self)->st_mode))
    return mrb_true_value();
#endif
  return mrb_false_value();
}

static mrb_value
stat_socket_p(mrb_state *mrb, mrb_value self)
{
#ifdef S_ISSOCK
  if (S_ISSOCK(get_stat(mrb, self)->st_mode))
    return mrb_true_value();
#endif
  return mrb_false_value();
}

static mrb_value
stat_blockdev_p(mrb_state *mrb, mrb_value self)
{
#ifdef S_ISBLK
  if (S_ISBLK(get_stat(mrb, self)->st_mode))
    return mrb_true_value();
#endif
  return mrb_false_value();
}

static mrb_value
stat_chardev_p(mrb_state *mrb, mrb_value self)
{
  if (S_ISCHR(get_stat(mrb, self)->st_mode))
    return mrb_true_value();
  return mrb_false_value();
}

static mrb_value
stat_setuid_p(mrb_state *mrb, mrb_value self)
{
#ifdef S_ISUID
  if (get_stat(mrb, self)->st_mode & S_ISUID)
    return mrb_true_value();
#endif
  return mrb_false_value();
}

static mrb_value
stat_setgid_p(mrb_state *mrb, mrb_value self)
{
#ifdef S_ISGID
  if (get_stat(mrb, self)->st_mode & S_ISGID)
    return mrb_true_value();
#endif
  return mrb_false_value();
}

static mrb_value
stat_sticky_p(mrb_state *mrb, mrb_value self)
{
#ifdef S_ISVTX
  if (get_stat(mrb, self)->st_mode & S_ISVTX)
    return mrb_true_value();
#endif
  return mrb_false_value();
}

void
mrb_mruby_file_stat_gem_init(mrb_state* mrb)
{
  struct RClass *io = mrb_define_class(mrb, "IO", mrb->object_class);
  struct RClass *file = mrb_define_class(mrb, "File", io);
  struct RClass *stat = mrb_define_class_under(mrb, file, "Stat", mrb->object_class);

  MRB_SET_INSTANCE_TT(stat, MRB_TT_DATA);

  mrb_define_class_method(mrb, file, "lstat", file_s_lstat, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, stat, "initialize", stat_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, stat, "initialize_copy", stat_initialize_copy, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, stat, "dev", stat_dev, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "dev_major", stat_dev_major, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "dev_minor", stat_dev_minor, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "ino", stat_ino, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "mode", stat_mode, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "nlink", stat_nlink, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "uid", stat_uid, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "gid", stat_gid, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "rdev", stat_rdev, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "rdev_major", stat_rdev_major, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "rdev_minor", stat_rdev_minor, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "atime", stat_atime, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "mtime", stat_mtime, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "ctime", stat_ctime, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "size", stat_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "blksize", stat_blksize, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "blocks", stat_blocks, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "inspect", stat_inspect, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "ftype", stat_ftype, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "directory?", stat_dir_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "readable?", stat_read_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "readable_real?", stat_read_real_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "writable?", stat_write_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "writable_real?", stat_write_real_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "executable?", stat_exec_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "executable_real?", stat_exec_real_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "file?", stat_file_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "zero?", stat_zero_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "size?", stat_size_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "owned?", stat_owned_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "grpowned?", stat_grpowned_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "pipe?", stat_pipe_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "symlink?", stat_symlink_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "socket?", stat_socket_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "blockdev?", stat_blockdev_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "chardev?", stat_chardev_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "setuid?", stat_setuid_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "setgid?", stat_setgid_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "sticky?", stat_sticky_p, MRB_ARGS_NONE());
}

void
mrb_mruby_file_stat_gem_final(mrb_state* mrb)
{
}
