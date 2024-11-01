#include "operator.h"

double __attribute__((target("fpmath=387"))) mul_x87(double init_val,
                                                     double step,
                                                     uint64_t iteration) {
  double mx = init_val * init_val;
  for (uint64_t i = 0; i < iteration; i++) mx *= step;
  return mx;
}

double __attribute__((target("fpmath=sse"))) mul_sse(double init_val,
                                                     double step,
                                                     uint64_t iteration) {
  double mx = init_val * init_val;
  for (uint64_t i = 0; i < iteration; i++) mx *= step;
  return mx;
}

double __attribute__((target("avx2"))) mul_avx(double init_val, double step,
                                               uint64_t iteration) {
  double mx = init_val * init_val;
  for (uint64_t i = 0; i < iteration; i++) mx *= step;
  return mx;
}

double __attribute__((target("avx512f"))) mul_avx512(double init_val,
                                                     double step,
                                                     uint64_t iteration) {
  double mx = init_val * init_val;
  for (uint64_t i = 0; i < iteration; i++) mx *= step;
  return mx;
}
