//
// Created by Miles on 7/3/18.
//

#ifndef CPU_SIM_UTIL_H
#define CPU_SIM_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


void load_mem(cpu_t *cpu, const char *filepath);

void print_byte(u_int8_t byte);

void print_file(cpu_t *cpu, int m, int n, int k, data_t *f, bool highlight_addr, bool lichten);

void print_memory(cpu_t *cpu);

void print_register_file(cpu_t *cpu);


#endif //CPU_SIM_UTIL_H
