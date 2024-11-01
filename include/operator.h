#ifndef _OPERATOR_H_
#define _OPERATOR_H_

#include "common.h"

double mul_x87(double init_val, double step, uint64_t iteration);
double mul_sse(double init_val, double step, uint64_t iteration);
double mul_avx(double init_val, double step, uint64_t iteration);
double mul_avx2(double init_val, double step, uint64_t iteration);
double mul_avx512(double init_val, double step, uint64_t iteration);
// double subnormal_mul(double init_val, double step, uint64_t iteration);
// double add(double init_val, double step, uint64_t iteration);
// double div(double init_val, double step, uint64_t iteration);
// double sqrt(double init_val, double step, uint64_t iteration);

#endif