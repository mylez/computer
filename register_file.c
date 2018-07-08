//
// Created by Miles on 7/3/18.
//

#include "register_file.h"


/**
 *
 * @param cpu
 * @param r_a
 * @param r_b
 * @return
 */
u_int16_t read_register_wide(cpu_t *cpu, u_int8_t r_a, u_int8_t r_b)
{
    return (u_int16_t) cpu->register_file[r_a] | (u_int16_t) cpu->register_file[r_b] << 8;
}


/**
 *
 * @param cpu
 * @param w
 * @param r_a
 * @param r_b
 */
void write_register_wide(cpu_t *cpu, address_t w, u_int8_t r_a, u_int8_t r_b)
{
    cpu->register_file[r_a] = (data_t) w;
    cpu->register_file[r_b] = (data_t) (w >> 8);
}


/**
 *
 * @param cpu
 * @return
 */
u_int16_t pc_register_wide_incr(cpu_t *cpu)
{
    u_int16_t
        addr      = read_register_wide(cpu, R_PX, R_PY),
        addr_incr = addr + (address_t) 1;
    write_register_wide(cpu, addr_incr, R_PX, R_PY);
    return addr;
}


/**
 *
 * @param cpu
 * @param v
 * @param r
 */
void write_register(cpu_t *cpu, data_t v, u_int8_t r)
{
    cpu->register_file[r] = v;
}


/**
 *
 * @param cpu
 * @param cbit
 * @return
 */
bool read_c0_bit(cpu_t *cpu, data_t cbit)
{
    return (cpu->register_file[R_C0] & cbit);
}


/**
 *
 * @param cpu
 * @param cbit
 * @param val
 */
void write_c0_bit(cpu_t *cpu, data_t cbit, data_t val)
{
    if (val)
    {
        cpu->register_file[R_C0] |= cbit;
    }
    else
    {
        cpu->register_file[R_C0] &= (0xFF ^ cbit);
    }
}

