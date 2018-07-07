#ifndef CPU_SIM_CONTROL_H
#define CPU_SIM_CONTROL_H

#include "cpu.h"

static const data_t
    E_PRMT = 0x01,
    E_ILLG = 0x02,
    E_PFLT = 0x03;

void start(cpu_t *cpu);

void inst_cycle(cpu_t *cpu);

void store_context(cpu_t *cpu);

#endif //CPU_SIM_CONTROL_H
