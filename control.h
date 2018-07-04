#ifndef CPU_SIM_CONTROL_H
#define CPU_SIM_CONTROL_H

#include "cpu.h"

void start(cpu_t *cpu);


void inst_cycle(cpu_t *cpu);


bool status_bit(cpu_t *cpu, u_int8_t sbit);


#endif //CPU_SIM_CONTROL_H
