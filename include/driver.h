#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <stdint.h>

#define RC_RNE 0b00
#define RC_NINF 0b01
#define RC_PINF 0b10
#define RC_RTZ 0b11

#define PC_SP 0b00
#define PC_DP 0b10
#define PC_DEP 0b11

#define MASK_P (1 << 5)
#define MASK_U (1 << 4)
#define MASK_O (1 << 3)
#define MASK_Z (1 << 2)
#define MASK_D (1 << 1)
#define MASK_I 1

#define FPCW_RC (0b11 << 10)
#define FPCW_PC (0b11 << 8)
#define FPCW_MASK (0b111111)

#define MXCSR_FTZ (1 << 15)
#define MXCSR_DAZ (1 << 6)
#define MXCSR_RC (0b11 << 13)
#define MXCSR_MASK (0b111111 << 7)
#define MXCSR_EXCEPT 0b111111

// x87 FPU Control and Status Register
void fpcw_set_round_control(uint16_t mode);
uint16_t fpcw_get_round_control();
void fpcw_set_precision_control(uint16_t mode);
uint16_t fpcw_get_precision_control();
void fpcw_set_mask(uint16_t mask);
void fpcw_flip_mask(uint16_t mask);
uint16_t fpcw_get_mask();

void fpcw_readable();

uint16_t fpsw_get_exception_status();
uint16_t fpsw_get_condition_code();

void fpsw_readable();

// avx FPU MXCSR Register
uint16_t mxcsr_get_ftz();
void mxcsr_set_ftz();
uint16_t mxcsr_get_daz();
void mxcsr_set_daz();
uint16_t mxcsr_get_round_control();
void mxcsr_set_round_control(uint16_t mode);
uint16_t mxcsr_get_mask();
void mxcsr_set_mask(uint16_t mask);
void mxcsr_flip_mask(uint16_t mask);
uint16_t mxcsr_get_exception_status();

void mxcsr_readable();

#endif