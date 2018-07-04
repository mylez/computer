//
// Created by Miles on 7/3/18.
//

#ifndef CPU_SIM_UTIL_H
#define CPU_SIM_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"


u_int16_t make_wide(u_int8_t a, u_int8_t b);

void load_mem(const char *filepath, cpu_t *cpu);

void print_file(int n, int k, u_int8_t *f);

void print_memory(cpu_t *cpu);



#endif //CPU_SIM_UTIL_H
