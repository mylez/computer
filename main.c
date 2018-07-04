#include <stdio.h>
#include "control.h"
#include "cpu.h"
#include "util.h"

// think little endian

int main()
{
    cpu_t cpu = make_cpu();
    load_mem("assembler/test", &cpu);

    for (int i = 0; i < 64; i++) inst_cycle(&cpu);
    destroy_cpu(&cpu);
    return 0;
}