#!/usr/bin/env bash

echo "Without machine clear"
gcc machine_clear.c
time ./a.out

echo "With machine clear"
gcc machine_clear.c -DMACHINE_CLEAR
time ./a.out