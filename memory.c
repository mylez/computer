//
// Created by Miles on 7/3/18.
//

#include <stdio.h>
#include "cpu.h"
#include "memory.h"
#include "register_file.h"

address_t virtual_lookup(cpu_t *cpu, address_t virtual_address)
{
    if (VERBOSE_MEMORY) printf("performing virtual lookup\n");

    u_int8_t virtual_page_num = (u_int8_t) virtual_address >> 9;

    if (VERBOSE_MEMORY) printf("\tvirtual_page_num:    %02x\n", virtual_page_num);

    address_t
        offset          = virtual_address & (address_t) 0x01ff,
        page_entry_addr = virtual_page_num + read_register_wide(cpu, R_VX, R_VY),
        phys_page_addr  = cpu->physical_memory[page_entry_addr],
        phys_addr       = phys_page_addr + offset;

     if (VERBOSE_MEMORY) printf("\toffset:              %02x\n", offset);
     if (VERBOSE_MEMORY) printf("\tpage_entry_addr:   %04x\n", page_entry_addr);
     if (VERBOSE_MEMORY) printf("\tphys_page_addr:    %04x\n", phys_page_addr);
     if (VERBOSE_MEMORY) printf("\tphys_addr:         %04x\n\n", phys_addr);

    return phys_addr;
}

/**
 * if restricted mode or vmem is on, dereference virtual
 * address through the page table. otherwise return the
 * value of the physical address
 *
 * @param cpu
 * @param addr
 * @return
 */
u_int8_t mem_read(cpu_t *cpu, address_t addr)
{
    if (VERBOSE_MEMORY) printf("mem_read\n");
    address_t phys_addr;
    if (!read_c0_bit(cpu, S_MODE) && !read_c0_bit(cpu, S_VMEM))
    {
        phys_addr = addr;
    }
    else
    {
        phys_addr = virtual_lookup(cpu, addr);
    }

    cpu->_last_mem_read_addr = phys_addr;
    return cpu->physical_memory[phys_addr];
}


/**
 * currently only physical addressing is set up
 *
 * @param cpu
 * @param v
 * @param addr
 */
void mem_write(cpu_t *cpu, data_t v, address_t addr)
{
    if (VERBOSE_MEMORY) printf("mem_write\n");
    address_t phys_addr = 0;
    if (!read_c0_bit(cpu, S_MODE) && !read_c0_bit(cpu, S_VMEM))
    {
        phys_addr = addr;
    }
    else
    {
        phys_addr = virtual_lookup(cpu, addr);
        cpu->physical_memory[phys_addr] = v;
    }
    cpu->_last_mem_write_addr = phys_addr;
    cpu->physical_memory[phys_addr] = v;
}
