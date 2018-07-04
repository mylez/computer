//
// Created by Miles on 7/3/18.
//

#include <memory.h>
#include "util.h"
#include "cpu.h"


/**
 *
 * @param filepath
 * @param cpu
 */
void load_mem(const char *filepath, cpu_t *cpu)
{
    int byte;

    FILE *file;

    file = fopen(filepath, "r");

    printf("loading memory from file: %s\n\n", filepath);

    if (file)
    {
        int i = 0;

        memset(cpu->physical_memory, 0, PHYSICAL_MEMORY_BYTES);

        while ((byte = getc(file)) != EOF)
        {
            cpu->physical_memory[i++] = (u_int8_t) byte;
        }
        fclose(file);
    }
    else
    {
        printf("error: unable to read mem file");
    }
}

/**
 *
 * @param n
 * @param k
 * @param f
 */
void print_file(int m, int n, int k, data_t *f)
{
    for (int i = m; i < n; i++)
    {
        if (!((i) % k))
        {
            printf("\t%04x   ", i);
        }
        printf("%02x ", f[i]);
        if (!((i + 1) % k) || i == n - 1)
        {
            printf("\n");
        }
    }
}


/**
 *
 * @param cpu
 */
void print_memory(cpu_t *cpu)
{
    int dsp = 0x50;
    printf("\n\tphysical memory\n");
    print_file(0, dsp, 0x10, cpu->physical_memory);
    printf("\t...\n");
    print_file(PHYSICAL_MEMORY_BYTES - dsp, PHYSICAL_MEMORY_BYTES , 0x10, cpu->physical_memory);
}


void print_register_file(cpu_t *cpu)
{
    printf("\n\tregister file\n");
    print_file(0, REGISTER_FILE_BYTES, 4, cpu->register_file);
}
