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
//
// everything above is user accessible
// everything below is restricted
//
// page table virtual address
    R_VX = 5,   // page table x
    R_VY = 6,   // page table y
// control byte
    R_C0 = 7,   // control bits
// exception handling registers
    R_EX = 8,   // exception type
    R_HX = 9,   // handler x
    R_HY = 10,  // handler y
// interrupt timer
    R_TI = 11,
// context buffer registers
    R_X0 = 12,
    R_X1 = 13,
    R_X2 = 14,
    R_X3 = 15,
    R_X4 = 16;

static const data_t
    S_MODE = 0x80,
    S_VMEM = 0x40,
    S_TIME = 0x20;

address_t read_register_wide(cpu_t *cpu, u_int8_t r_a, u_int8_t r_b);

void write_register_wide(cpu_t *cpu, address_t w, u_int8_t r_a, u_int8_t r_b);

void write_register(cpu_t *cpu, data_t v, u_int8_t r);

u_int16_t pc_register_wide_incr(cpu_t *cpu);

bool read_c0_bit(cpu_t *cpu, data_t cbit);

void write_c0_bit(cpu_t *cpu, data_t cbit, data_t val);

#endif //CPU_SIM_REGISTER_FILE_H
