#include <stdio.h>
#include <sys/time.h>

#include "benchmark.h"
#include "driver.h"

int main() {
  // fpcw_readable();
  // mxcsr_set_daz();
  // mxcsr_set_ftz();
  // mxcsr_readable();

  mul_benchmark();
  return 0;
}