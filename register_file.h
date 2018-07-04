//
// Created by Miles on 7/3/18.
//

#ifndef CPU_SIM_REGISTER_FILE_H
#define CPU_SIM_REGISTER_FILE_H


#include "cpu.h"


static const u_int8_t
// memory address
    R_MX = 0,
    R_MY = 1,
// program counter
    R_PX = 2,
    R_PY = 3,
// accumulator
    R_AC = 4,
// frame pointer
    R_FX = 5,
    R_FY = 6,
// machine status byte
    R_MS = 7;

static const data_t
    S_MODE = 0x80,
    S_VMEM = 0x40;

address_t read_register_wide(cpu_t *cpu, u_int8_t r_a, u_int8_t r_b);

void set_register_wide(cpu_t *cpu, address_t w, u_int8_t r_a, u_int8_t r_b);

void set_register(cpu_t *cpu, data_t v, u_int8_t r);

u_int16_t set_pc_register_wide_incr(cpu_t *cpu);

#endif //CPU_SIM_REGISTER_FILE_H
