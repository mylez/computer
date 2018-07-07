#include <stdio.h>
#include <memory.h>
#include "cpu.h"

/**
 *
 * @param cpu
 */
void destroy_cpu(cpu_t *cpu)
{
    free(cpu->physical_memory);
}

/**
 *
 * @return
 */
cpu_t make_cpu()
{
    cpu_t cpu;
    cpu.physical_memory = malloc(PHYSICAL_MEMORY_BYTES);
    reset_cpu(&cpu);
    return cpu;
}

/**
 *
 * @param cpu
 */
void reset_cpu(cpu_t *cpu)
{
    cpu->running = false;
    cpu->inst_cycle_count = 0;
    cpu->_last_inst_addr = 0;
    memset(&cpu->register_file, 0, REGISTER_FILE_BYTES);
}
