#ifndef CPU_SIM_CPU_H
#define CPU_SIM_CPU_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


#define REGISTER_FILE_BYTES 16
#define PHYSICAL_MEMORY_BYTES 0x1000

typedef u_int8_t data_t;

typedef u_int16_t address_t;

typedef struct
{
    data_t
        register_file[REGISTER_FILE_BYTES],
        *physical_memory;

    bool running;

    int inst_cycle_count;

    // used for debugging and output
    address_t
        _last_inst_addr,
        _last_mem_read_addr,
        _last_mem_write_addr;

} cpu_t;

cpu_t make_cpu();

void reset_cpu(cpu_t *cpu);

void destroy_cpu(cpu_t *cpu);


#endif //CPU_SIM_CPU_H
