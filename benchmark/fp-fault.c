#include <stdio.h>
#include <sys/time.h>

#include "benchmark.h"
#include "driver.h"

int main() {
  fpcw_readable();
  mxcsr_readable();

  mul_benchmark();
  add_benchmark();
  return 0;
}