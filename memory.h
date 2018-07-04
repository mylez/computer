//
// Created by Miles on 7/3/18.
//

#ifndef CPU_SIM_MEMORY_H
#define CPU_SIM_MEMORY_H


#include "isa.h"
#include "cpu.h"



/**
 *
 * @param cpu
 * @param addr
 * @return
 */
u_int8_t mem_read(cpu_t *cpu, address_t addr);


void mem_write(cpu_t *cpu, data_t v, address_t addr);


#endif //CPU_SIM_MEMORY_H
