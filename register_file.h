//
// Created by Miles on 7/3/18.
//

#ifndef CPU_SIM_REGISTER_FILE_H
#define CPU_SIM_REGISTER_FILE_H


#include "cpu.h"


#define     R_00    0
#define     R_AC    1
#define     R_MX    2
#define     R_MY    3
#define     R_PX    4
#define     R_PY    5
#define     R_MS    6
#define     R_PT    7

#define     S_MODE  (u_int8_t)0x80
#define     S_VMEM  (u_int8_t)0x40

void print_register_file(cpu_t *cpu);

u_int16_t read_register_wide(cpu_t *cpu, u_int8_t r_a, u_int8_t r_b);

void set_register_wide(cpu_t *cpu, u_int16_t v, u_int8_t r_a, u_int8_t r_b);

u_int16_t pc_register_wide_incr(cpu_t *cpu);

#endif //CPU_SIM_REGISTER_FILE_H
