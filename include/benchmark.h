#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define MAX_LEN          16

#define RED              "\033[31m"
#define GREEN            "\033[1;38;2;119;221;119m"
#define YELLOW           "\033[1;38;2;255;221;136m"
#define BLUE             "\033[1;38;2;119;187;221m"
#define PINK             "\033[1;38;2;255;136;153m"
#define DEEPGREEN        "\033[36m"
#define CLEAR            "\033[0m"

#define Log(format, ...) printf(BLUE format CLEAR "\n", ##__VA_ARGS__)

typedef struct TestSettings {
  char name[MAX_LEN];
  double init_val;
  double step;
  double target;
  uint64_t iteration;
} TestSettings;

typedef double (*test_func)(double, double, uint64_t);

void mul_benchmark();
double do_test(test_func test, TestSettings setting);

#endif