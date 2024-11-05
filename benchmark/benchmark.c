#include "benchmark.h"

#include <math.h>
#include <sys/time.h>

double do_test(test_func test, TestSettings setting) {
  struct timeval global_tv;
  double time_start, time_end;

  // Start timer
  gettimeofday(&global_tv, NULL);
  time_start = (double)(global_tv.tv_sec) + (double)(global_tv.tv_usec) * 1e-6;

  double res = test(setting.init_val, setting.step, setting.iteration);

  // End timer
  gettimeofday(&global_tv, NULL);
  time_end = (double)(global_tv.tv_sec) + (double)(global_tv.tv_usec) * 1e-6;

  if (isnan(res) && isnan(setting.target)) {
    printf(GREEN "  Passed: %.15f\n" CLEAR, res);
  } else if (isinf(res) && isinf(setting.target)) {
    printf(GREEN "  Passed: %.15f\n" CLEAR, res);
  } else if (fabs(res - setting.target) > 1e-10) {
    printf(RED "  Failed:\n" CLEAR);
    printf(RED "    Expected: %.15f, Got: %.15f\n" CLEAR, setting.target, res);
  } else {
    printf(GREEN "  Passed: %.15f\n" CLEAR, res);
  }

  double duration = time_end - time_start;
  return duration;
}
