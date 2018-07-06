//
// Created by Miles on 7/3/18.
//

#include <stdio.h>
#include "cpu.h"
#include "memory.h"
#include "register_file.h"

address_t virtual_lookup(cpu_t *cpu, address_t virtual_address)
{
    printf("performing virtual lookup\n");

    u_int8_t virtual_page_num = (u_int8_t) virtual_address >> 9;
    printf("\tvirtual_page_num:    %02x\n", virtual_page_num);

    address_t
        offset          = virtual_address & (address_t) 0x01ff,
        page_entry_addr = virtual_page_num + read_register_wide(cpu, R_VX, R_VY),
        phys_page_addr  = cpu->physical_memory[page_entry_addr],
        phys_addr       = phys_page_addr + offset;

    printf("\toffset:              %02x\n", offset);
    printf("\tpage_entry_addr:   %04x\n", page_entry_addr);
    printf("\tphys_page_addr:    %04x\n", phys_page_addr);
    printf("\tphys_addr:         %04x\n\n", phys_addr);

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
    printf("mem_read\n");
    if (!c0_bit(cpu, S_MODE) && !c0_bit(cpu, S_VMEM))
    {
        return cpu->physical_memory[addr];
    }

    address_t phys_addr = virtual_lookup(cpu, addr);

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
    printf("mem_write\n");
    if (!c0_bit(cpu, S_MODE) && !c0_bit(cpu, S_VMEM))
    {
        cpu->physical_memory[addr] = v;
    }
    else
    {
        address_t phys_addr = virtual_lookup(cpu, addr);
        cpu->physical_memory[phys_addr] = v;
    }
}
