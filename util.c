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
void print_file(int n, int k, u_int8_t *f)
{
    for (int i = 0; i < n; i++)
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
    printf("memory:\n");
    print_file(0x100, 0x10, cpu->physical_memory);
}
