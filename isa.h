#ifndef CPU_SIM_ISA_H
#define CPU_SIM_ISA_H

#include "cpu.h"

static const data_t
    I_NOOP = 0x00,
    I_ADDI = 0x10,
    I_SUBI = 0x11,
    I_ADD  = 0x20,
    I_SUB  = 0X21,
    I_CLAC = 0x30,
    I_STOR = 0x40,
    I_BEQZ = 0x50,

    I_SSET = 0xe0,
    I_HALT = 0xff;


#endif //CPU_SIM_ISA_H
