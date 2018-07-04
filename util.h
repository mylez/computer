//
// Created by Miles on 7/3/18.
//

#ifndef CPU_SIM_UTIL_H
#define CPU_SIM_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"


void load_mem(cpu_t *cpu, const char *filepath);

void print_file(int m, int n, int k, data_t *f);

void print_memory(cpu_t *cpu);

void print_register_file(cpu_t *cpu);


#endif //CPU_SIM_UTIL_H
