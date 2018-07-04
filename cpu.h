#ifndef CPU_SIM_CPU_H
#define CPU_SIM_CPU_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>



#define REGISTER_FILE_BYTES 8
#define PHYSICAL_MEMORY_BYTES 0x10000

typedef struct
{
    bool running;

    int inst_cycle_count;

    u_int8_t
        register_file[REGISTER_FILE_BYTES],
        *physical_memory;
} cpu_t;

cpu_t make_cpu();

void reset_cpu(cpu_t *cpu);

void destroy_cpu(cpu_t *cpu);


#endif //CPU_SIM_CPU_H
