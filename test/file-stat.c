#include <mruby.h>
#include <stdlib.h>

mrb_value
test_system(mrb_state *mrb, mrb_value klass)
{
  char *cmd = NULL;
  mrb_get_args(mrb, "z", &cmd);
  system(cmd);
  return mrb_nil_value();
}

void mrb_mruby_file_stat_gem_test(mrb_state *mrb)
{
  struct RClass *t;

  t = mrb_define_class(mrb, "FileStatTest", mrb->object_class);
  mrb_define_module_function(mrb, t, "system", test_system, MRB_ARGS_REQ(1));
}
