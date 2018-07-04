#include <stdio.h>
#include <zconf.h>
#include "control.h"
#include "isa.h"
#include "register_file.h"
#include "util.h"
#include "memory.h"
#include "cpu.h"


/**
 *
 * @param cpu
 */
void start(cpu_t *cpu)
{
    cpu->running = true;

    while (cpu->running)
    {
        inst_cycle(cpu);
    }
}


/**
 *
 * @param cpu
 */
void inst_cycle(cpu_t *cpu)
{

    u_int16_t
        inst_addr = read_register_wide(cpu, R_PX, R_PY),
        imm_16 = 0;

    u_int8_t
        inst  = mem_read(cpu, pc_register_wide_incr(cpu)),
        imm_0 = 0,
        imm_1 = 0;

    switch (inst)
    {
        case I_CLAC:
            cpu->register_file[R_AC] = 0;
            break;
        case I_ADDI:
            imm_0 = mem_read(cpu, pc_register_wide_incr(cpu));
            cpu->register_file[R_AC] += imm_0;
            break;
        case I_SUBI:
            imm_0 = mem_read(cpu, pc_register_wide_incr(cpu));
            cpu->register_file[R_AC] -= imm_0;
            break;
        case I_ADD:
            imm_0 = mem_read(cpu, pc_register_wide_incr(cpu));
            imm_1 = mem_read(cpu, pc_register_wide_incr(cpu));
            imm_16 = imm_0 + imm_1 * (u_int16_t)0x100;
            cpu->register_file[R_AC] += mem_read(cpu, imm_16);
            break;
        case I_SUB:
            imm_0 = mem_read(cpu, pc_register_wide_incr(cpu));
            imm_1 = mem_read(cpu, pc_register_wide_incr(cpu));
            imm_16 = imm_0 + imm_1 * (u_int16_t)0x100;
            cpu->register_file[R_AC] -= mem_read(cpu, imm_16);
            break;
        case I_STOR:
            break;
        case I_BEQZ:
            break;
        case I_HALT:
            cpu->running = false;
            break;
        case I_NOOP:
        default:
            break;
    }

    printf("cycle %d\n", cpu->inst_cycle_count);
    printf("\tinst:        0x%02x\n", inst);
    printf("\timm_0:       0x%02x\n", imm_0);
    printf("\timm_1:       0x%02x\n", imm_1);
    printf("\timm_16:      0x%04x\n", imm_16);
    printf("\tinst_addr:   0x%04x\n", inst_addr);
    print_register_file(cpu);
    //print_memory(cpu);
    printf("\n");

    cpu->inst_cycle_count++;
}

/**
 * returns true if cpu is currently in supervisor mode
 *
 * @param cpu
 * @return
 */
bool status_bit(cpu_t *cpu, u_int8_t sbit)
{
    return (cpu->register_file[R_MS] & sbit);
}
