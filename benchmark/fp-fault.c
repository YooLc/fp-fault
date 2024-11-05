#include <stdio.h>
#include <sys/time.h>

#include "common.h"
#include "operator.h"
#include "driver.h"

void do_test(test_func test) {
  struct timeval global_tv;
  double time_start, time_end;

  printf("Doing normal floating number test\n");

  gettimeofday(&global_tv, NULL);
  time_start = (double)(global_tv.tv_sec) + (double)(global_tv.tv_usec) * 1e-6;

  double res = test(1.000000001, 1.000000001, 1e8);

  gettimeofday(&global_tv, NULL);
  time_end = (double)(global_tv.tv_sec) + (double)(global_tv.tv_usec) * 1e-6;

  double normal_duration = time_end - time_start;
  printf("Time: %.2lf s, Result: %.6lf\n", normal_duration, res);

  printf("Doing subnormal floating number test\n");

  gettimeofday(&global_tv, NULL);
  time_start = (double)(global_tv.tv_sec) + (double)(global_tv.tv_usec) * 1e-6;

  res = test(__DBL_MAX__, 1.000000001, 1e8);

  gettimeofday(&global_tv, NULL);
  time_end = (double)(global_tv.tv_sec) + (double)(global_tv.tv_usec) * 1e-6;

  double subnormal_duration = time_end - time_start;
  printf("Time: %.2lf s, Result: %.6lf\n", subnormal_duration, res);
  printf(">> Result: Reached %.2lf%% performance <<<\n",
         normal_duration / subnormal_duration * 100);
}

int main() {
  fpcw_readable();
  mxcsr_set_daz();
  mxcsr_set_ftz();
  mxcsr_readable();
  
  printf(">>> Tesing on x87 <<<\n");
  do_test(mul_x87);
  printf("\n>>> Tesing on SSE <<<\n");
  do_test(mul_sse);
  printf("\n>>> Tesing on AVX <<<\n");
  do_test(mul_avx);
  printf("\n>>> Tesing on AVX512 <<<\n");
  do_test(mul_avx512);
  return 0;
}