#include <stdio.h>
#include <unistd.h>
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
        //printf("\e[1;1H\e[2J"); // clear terminal
        if (read_c0_bit(cpu, S_MODE))
        {
            printf(KGRN);
            printf("USER");
            printf(KNRM);
        }
        else
        {
            printf(KRED);
            printf("KERN");
            printf(KNRM);
        }
        printf(" ---------------------------------------------------------\n");

        inst_cycle(cpu);

        if (cpu->inst_cycle_count == 100)
            break;

      //  usleep(1000000);
    }
}


/**
 *
 * @param cpu
 */
void store_context(cpu_t *cpu)
{
    printf(KMAG);
    printf("STORING CONTEXT\n");

    print_register_file(cpu);
    cpu->register_file[R_X0] = cpu->register_file[R_MX];
    cpu->register_file[R_X1] = cpu->register_file[R_MY];
    cpu->register_file[R_X2] = cpu->register_file[R_PX];
    cpu->register_file[R_X3] = cpu->register_file[R_PY];
    cpu->register_file[R_X4] = cpu->register_file[R_AC];
    print_register_file(cpu);

    printf(KNRM);
}


/**
 *
 * @param cpu
 * @param e
 */
void raise_exception(cpu_t *cpu, data_t e)
{
    printf(KRED);
    printf("EXCEPTION 0x%02x: ", e);
    switch (e)
    {
        case E_ILLG:
            printf("ILLEGAL INSTRUCTION");
            break;
        case E_PFLT:
            printf("PAGE FAULT");
            break;
        case E_PRMT:
            printf("TIMER PREEMPTION");
            break;
        default:
            printf("UNKNOWN");
            break;
    }
    printf(KNRM);
    printf("\n");

    store_context(cpu);
    write_register(cpu, e, R_EX);
    write_c0_bit(cpu, S_MODE, 0); // set privileged mode
    write_c0_bit(cpu, S_VMEM, 0); // turn off virtual memory
    write_register_wide(cpu, read_register_wide(cpu, R_HX, R_HY), R_PX, R_PY); // begin executing at exception handler
}


/**
 *
 * @param cpu
 */
void inst_cycle(cpu_t *cpu)
{
    address_t
        inst_addr = read_register_wide(cpu, R_PX, R_PY),
        imm_16    = 0;

    data_t
        inst  = mem_read(cpu, pc_register_wide_incr(cpu)),
        imm_0 = 0,
        imm_1 = 0;

    cpu->_last_inst_addr = inst_addr;

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
            imm_0  = mem_read(cpu, pc_register_wide_incr(cpu));
            imm_1  = mem_read(cpu, pc_register_wide_incr(cpu));
            imm_16 = imm_0 + imm_1 * (u_int16_t) 0x100;
            cpu->register_file[R_AC] += mem_read(cpu, imm_16);
            break;
        case I_SUB:
            imm_0  = mem_read(cpu, pc_register_wide_incr(cpu));
            imm_1  = mem_read(cpu, pc_register_wide_incr(cpu));
            imm_16 = imm_0 + imm_1 * (u_int16_t) 0x100;
            cpu->register_file[R_AC] -= mem_read(cpu, imm_16);
            break;
        case I_STOR:
            imm_0  = mem_read(cpu, pc_register_wide_incr(cpu));
            imm_1  = mem_read(cpu, pc_register_wide_incr(cpu));
            imm_16 = imm_0 + imm_1 * (u_int16_t) 0x100;
            mem_write(cpu, cpu->register_file[R_AC], imm_16);
            break;
        case I_BEQZ:
            imm_0  = mem_read(cpu, pc_register_wide_incr(cpu));
            imm_1  = mem_read(cpu, pc_register_wide_incr(cpu));
            imm_16 = imm_0 + imm_1 * (u_int16_t) 0x100;
            if (cpu->register_file[R_AC] == 0)
            {
                write_register_wide(cpu, imm_16, R_PX, R_PY);
            }
            break;


        case I_TSET:
            imm_0 = mem_read(cpu, pc_register_wide_incr(cpu));
            if (read_c0_bit(cpu, S_MODE) == 0) // privileged mode
            {
                cpu->register_file[R_TI] = imm_0;
            }
            else
            {
                raise_exception(cpu, E_ILLG);
            }
            break;

        case I_CSET:
            imm_0 = mem_read(cpu, pc_register_wide_incr(cpu));
            if (read_c0_bit(cpu, S_MODE) == 0) // privileged mode
            {
                cpu->register_file[R_C0] |= imm_0;
            }
            else
            {
                raise_exception(cpu, E_ILLG);
            }
            break;

        case I_CUNS:
            imm_0 = mem_read(cpu, pc_register_wide_incr(cpu));
            if (read_c0_bit(cpu, S_MODE) == 0) // privileged mode
            {
                cpu->register_file[R_C0] &= (0xff ^ imm_0);
            }
            else
            {
                raise_exception(cpu, E_ILLG);
            }
            break;

        case I_ESET:

            imm_0  = mem_read(cpu, pc_register_wide_incr(cpu));
            imm_1  = mem_read(cpu, pc_register_wide_incr(cpu));
            imm_16 = imm_0 + imm_1 * (u_int16_t) 0x100;
            if (read_c0_bit(cpu, S_MODE) == 0) // privileged mode
            {
                write_register_wide(cpu, imm_16, R_HX, R_HY);
            }
            else
            {
                raise_exception(cpu, E_ILLG);
            }
            break;
        case I_VSET:
            imm_0  = mem_read(cpu, pc_register_wide_incr(cpu));
            imm_1  = mem_read(cpu, pc_register_wide_incr(cpu));
            imm_16 = imm_0 + imm_1 * (u_int16_t) 0x100;
            if (read_c0_bit(cpu, S_MODE) == 0) // privileged mode
            {
                write_register_wide(cpu, imm_16, R_VX, R_VY);
                cpu->register_file[R_C0] |= imm_0;
            }
            else
            {
                raise_exception(cpu, E_ILLG);
            }
            break;
        case I_HALT:
            cpu->running = false;
            break;
        case I_NOOP:
        default:
            break;
    }

    printf("- cycle %d\n", cpu->inst_cycle_count);
    printf("\tinst:           %02x\n", inst);
    printf("\timm_16:       %02x%02x\n", imm_1, imm_0);
    printf("\tinst_addr:    %04x\n", inst_addr);
    printf("\ttimer:          %02x\n", cpu->register_file[R_TI]);
    print_register_file(cpu);
    print_memory(cpu);
    printf("\n");

    if (read_c0_bit(cpu, S_MODE) && (cpu->register_file[R_TI]-- == 0))
    {
        raise_exception(cpu, E_PRMT);
    }

    cpu->inst_cycle_count++;
}
