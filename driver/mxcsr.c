#include "driver.h"
#include <stdio.h>
#include <stdalign.h>

uint16_t mxcsr_get_ftz() {
    alignas(16) uint16_t mxcsr;
    asm volatile("stmxcsr %0" : "=m"(mxcsr));
    return (mxcsr & MXCSR_FTZ) >> 15;
}

void mxcsr_set_ftz() {
    alignas(16) uint16_t mxcsr;
    asm volatile("stmxcsr %0" : "=m"(mxcsr));
    mxcsr |= MXCSR_FTZ;
    asm volatile("ldmxcsr %0" : : "m"(mxcsr));
}

uint16_t mxcsr_get_daz() {
    alignas(16) uint16_t mxcsr;
    asm volatile("stmxcsr %0" : "=m"(mxcsr));
    return (mxcsr & MXCSR_DAZ) >> 6;
}

void mxcsr_set_daz() {
    alignas(16) uint16_t mxcsr;
    asm volatile("stmxcsr %0" : "=m"(mxcsr));
    mxcsr |= MXCSR_DAZ;
    asm volatile("ldmxcsr %0" : : "m"(mxcsr));
}

uint16_t mxcsr_get_round_control() {
    alignas(16) uint16_t mxcsr;
    asm volatile("stmxcsr %0" : "=m"(mxcsr));
    return (mxcsr & MXCSR_RC) >> 13;
}

void mxcsr_set_round_control(uint16_t mode) {
    alignas(16) uint16_t mxcsr;
    asm volatile("stmxcsr %0" : "=m"(mxcsr));
    mxcsr &= ~MXCSR_RC;
    mxcsr |= mode << 13;
    asm volatile("ldmxcsr %0" : : "m"(mxcsr));
}

uint16_t mxcsr_get_mask() {
    alignas(16) uint16_t mxcsr;
    asm volatile("stmxcsr %0" : "=m"(mxcsr));
    return (mxcsr & MXCSR_MASK) >> 7;
}

void mxcsr_set_mask(uint16_t mask) {
    alignas(16) uint16_t mxcsr;
    asm volatile("stmxcsr %0" : "=m"(mxcsr));
    mxcsr &= ~MXCSR_MASK;
    mxcsr |= mask << 7;
    asm volatile("ldmxcsr %0" : : "m"(mxcsr));
}

void mxcsr_flip_mask(uint16_t mask) {
    alignas(16) uint16_t mxcsr;
    asm volatile("stmxcsr %0" : "=m"(mxcsr));
    mxcsr ^= mask << 7;
    asm volatile("ldmxcsr %0" : : "m"(mxcsr));
}

uint16_t mxcsr_get_exception_status() {
    alignas(16) uint16_t mxcsr;
    asm volatile("stmxcsr %0" : "=m"(mxcsr));
    return mxcsr & MXCSR_EXCEPT;
}

void mxcsr_readable() {
    alignas(16) uint16_t mxcsr;
    asm volatile("stmxcsr %0" : "=m"(mxcsr));
    printf("======= avx mxcsr register ========\n");
    printf("MXCSR: 0x%04X\n", mxcsr);

    uint16_t ftz = mxcsr_get_ftz();
    printf("FTZ: %s\n", ftz ? "ON" : "OFF");

    uint16_t daz = mxcsr_get_daz();
    printf("DAZ: %s\n", daz ? "ON" : "OFF");

    uint16_t rc = mxcsr_get_round_control();
    printf("Round: ");
    switch (rc) {
        case RC_RNE:
            printf("Round to Nearest or Even\n");
            break;
        case RC_NINF:
            printf("Round Toward Negative INF\n");
            break;
        case RC_PINF:
            printf("Round Toward Positive INF\n");
            break;
        case RC_RTZ:
            printf("Round Toward Zero\n");
            break;
    }

    uint16_t mask = mxcsr_get_mask();
    printf("Masked exceptions: \n");
    if (mask & MASK_P) printf("  P: Precision Underflow\n");
    if (mask & MASK_U) printf("  U: Underflow\n");
    if (mask & MASK_O) printf("  O: Overflow\n");
    if (mask & MASK_Z) printf("  Z: Zero Divide\n");
    if (mask & MASK_D) printf("  D: Denormalized Operand\n");
    if (mask & MASK_I) printf("  I: Invalid Operation\n");
    printf("===================================\n");
}