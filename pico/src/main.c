#include "core.h"

int 
main(void)
{
  core_init();

  while (1)
  {
    core_run_tasks();
  }

  return 0;
}