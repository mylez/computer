//
// Created by Miles on 7/3/18.
//

#include <cxxabi.h>
#include "register_file.h"
#include "cpu.h"
#include "util.h"


void print_register_file(cpu_t *cpu)
{
    printf("\tregister file:\n");
    print_file(REGISTER_FILE_BYTES, 2, cpu->register_file);
}


u_int16_t read_register_wide(cpu_t *cpu, u_int8_t r_a, u_int8_t r_b)
{
    return (u_int16_t)cpu->register_file[r_a] | (u_int16_t)cpu->register_file[r_b] << 8;
}


void set_register_wide(cpu_t *cpu, u_int16_t v, u_int8_t r_a, u_int8_t r_b)
{
    cpu->register_file[r_a] = (u_int8_t)v;
    cpu->register_file[r_b] = (u_int8_t)(v/0x100);
}


u_int16_t pc_register_wide_incr(cpu_t *cpu)
{
    u_int16_t
        addr = read_register_wide(cpu, R_PX, R_PY),
        addr_incr = addr + (u_int16_t)1;

    set_register_wide(cpu, addr_incr, R_PX, R_PY);

    return addr;
}
