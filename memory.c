//
// Created by Miles on 7/3/18.
//

#include "cpu.h"
#include "memory.h"
#include "control.h"
#include "register_file.h"

/**
 * if restricted mode or vmem is on, dereference virtual
 * address through the page table. otherwise return the
 * value of the physical address
 *
 * @param cpu
 * @param addr
 * @return
 */
u_int8_t mem_read(cpu_t *cpu, u_int16_t addr)
{
    if (!status_bit(cpu, S_MODE) && !status_bit(cpu, S_VMEM))
    {
        return cpu->physical_memory[addr];
    }

    return 0;
}


/**
 * currently only physical addressing is set up
 *
 * @param cpu
 * @param v
 * @param addr
 */
void mem_write(cpu_t *cpu, u_int8_t v, u_int16_t addr)
{
    if (!status_bit(cpu, S_MODE) && !status_bit(cpu, S_VMEM))
    {
        cpu->physical_memory[addr] = v;
    }
}
