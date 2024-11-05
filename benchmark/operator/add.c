#include <stdio.h>

#include "benchmark.h"

double __attribute__((target("fpmath=387"))) add_x87(double init_val,
                                                     double step,
                                                     uint64_t iteration) {
  double mx = init_val * init_val;
  for (uint64_t i = 0; i < iteration; i++) mx += step;
  return mx;
}

double __attribute__((target("fpmath=sse"))) add_sse(double init_val,
                                                     double step,
                                                     uint64_t iteration) {
  double mx = init_val * init_val;
  for (uint64_t i = 0; i < iteration; i++) mx += step;
  return mx;
}

double __attribute__((target("avx2"))) add_avx(double init_val, double step,
                                               uint64_t iteration) {
  double mx = init_val * init_val;
  for (uint64_t i = 0; i < iteration; i++) mx += step;
  return mx;
}

void add_benchmark() {
  double pinf_val = __builtin_inf();
  double nan_val  = __builtin_nan("0x7ff");
  double step     = 1.000000001;

  TestSettings normal = {"add_norm", step, step, 100000001.02353060245, 1e8};
  TestSettings pinf   = {"add_pinf", __DBL_MAX__, step, pinf_val, 1e8};
  TestSettings ninf = {"add_ninf", -__DBL_MAX__, step, pinf_val, 1e8};  // pinf?
  TestSettings nan  = {"add_nan", __builtin_nan("0x7ff"), step, nan_val, 1e8};
  TestSettings underflow   = {"add_uflow", __DBL_MIN__, __DBL_MIN__, 0.0, 1e8};
  TestSettings* settings[] = {&normal, &pinf, &ninf, &nan, &underflow};

  double duration;
  for (uint64_t i = 0; i < sizeof(settings) / sizeof(TestSettings*); i++) {
    Log(">>> Tesing %s on x87 <<<", settings[i]->name);
    duration = do_test(add_x87, *settings[i]);
    Log(">>> Result: %fs\n", duration);
    Log(">>> Tesing %s on SSE <<<", settings[i]->name);
    duration = do_test(add_sse, *settings[i]);
    Log(">>> Result: %fs\n", duration);
    Log(">>> Tesing %s on AVX <<<", settings[i]->name);
    duration = do_test(add_avx, *settings[i]);
    Log(">>> Result: %fs\n", duration);
  }
}