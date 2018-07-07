#ifndef CPU_SIM_CONTROL_H
#define CPU_SIM_CONTROL_H

#include "cpu.h"

void start(cpu_t *cpu);

void inst_cycle(cpu_t *cpu);

void save_context(cpu_t *cpu, data_t exception);

#endif //CPU_SIM_CONTROL_H
