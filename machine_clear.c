#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void trigger_machine_clear() {
    uint32_t eax, ebx, ecx, edx;

    asm volatile(
        "cpuid"
        : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
        : "a"(0)
    );
}

int main() {
    // Example function that performs floating point operations
    double a = 1.0, b = 1.00000001;
    for (int i = 0; i < 1e8; ++i) {
        a = a * b;
#ifdef MACHINE_CLEAR
        trigger_machine_clear();
#endif
    }
    return 0;
}