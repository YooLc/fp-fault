#include "driver.h"
#include <stdio.h>

void fpcw_set_inf_control() {
    uint16_t fpcw;
    asm volatile ("fnstcw %0" : "=m" (fpcw));
    fpcw |= FPCW_X;
    asm volatile ("fldcw %0" : : "m" (fpcw));
}

void fpcw_clear_inf_control() {
    uint16_t fpcw;
    asm volatile ("fnstcw %0" : "=m" (fpcw));
    fpcw &= ~FPCW_X;
    asm volatile ("fldcw %0" : : "m" (fpcw));
}

uint16_t fpcw_get_inf_control() {
    uint16_t fpcw;
    asm volatile ("fnstcw %0" : "=m" (fpcw));
    return fpcw & FPCW_X;
}

void fpcw_set_round_control(uint16_t mode) {
    uint16_t fpcw;
    asm volatile ("fnstcw %0" : "=m" (fpcw));
    fpcw &= ~FPCW_RC;
    fpcw |= (mode << 10);
    asm volatile ("fldcw %0" : : "m" (fpcw));
}

uint16_t fpcw_get_round_control() {
    uint16_t fpcw;
    asm volatile ("fnstcw %0" : "=m" (fpcw));
    return (fpcw & FPCW_RC) >> 10;
}

void fpcw_set_precision_control(uint16_t mode) {
    uint16_t fpcw;
    asm volatile ("fnstcw %0" : "=m" (fpcw));
    fpcw &= ~FPCW_PC;
    fpcw |= (mode << 8);
    asm volatile ("fldcw %0" : : "m" (fpcw));
}

uint16_t fpcw_get_precision_control() {
    uint16_t fpcw;
    asm volatile ("fnstcw %0" : "=m" (fpcw));
    return (fpcw & FPCW_PC) >> 8;
}

void fpcw_set_mask(uint16_t mask) {
    uint16_t fpcw;
    asm volatile ("fnstcw %0" : "=m" (fpcw));
    fpcw &= ~FPCW_MASK;
    fpcw |= mask;
    asm volatile ("fldcw %0" : : "m" (fpcw));
}

void fpcw_flip_mask(uint16_t mask) {
    uint16_t fpcw;
    asm volatile ("fnstcw %0" : "=m" (fpcw));
    fpcw ^= mask;
    asm volatile ("fldcw %0" : : "m" (fpcw));
}

uint16_t fpcw_get_mask() {
    uint16_t fpcw;
    asm volatile ("fnstcw %0" : "=m" (fpcw));
    return fpcw & FPCW_MASK;
}

void fpcw_readable() {
    uint16_t fpcw;
    asm volatile ("fnstcw %0" : "=m" (fpcw));
    printf("======= x87 fp control word =======\n");
    printf("FPCW: 0x%04X\n", fpcw);

    uint16_t x = fpcw_get_inf_control();
    printf("Inf Control: %s\n", x ? "Masked" : "Unmasked");

    uint16_t rc = fpcw_get_round_control();
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

    uint16_t pc = fpcw_get_precision_control();
    printf("Precision: ");
    switch (pc) {
        case PC_SP:
            printf("Single Precision\n");
            break;
        case PC_DP:
            printf("Double Precision\n");
            break;
        case PC_DEP:
            printf("Double Extended Precision\n");
            break;
    }

    uint16_t mask = fpcw_get_mask();
    printf("Masked exceptions: \n");
    if (mask & MASK_P) printf("  P: Precision Underflow\n");
    if (mask & MASK_U) printf("  U: Underflow\n");
    if (mask & MASK_O) printf("  O: Overflow\n");
    if (mask & MASK_Z) printf("  Z: Zero Divide\n");
    if (mask & MASK_D) printf("  D: Denormalized Operand\n");
    if (mask & MASK_I) printf("  I: Invalid Operation\n");
    printf("===================================\n");
}