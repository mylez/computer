#include <stdio.h>
#include "control.h"
#include "cpu.h"
#include "util.h"

// think little endian

int main()
{
    cpu_t cpu = make_cpu();
    load_mem(&cpu, "assembler/test");



    cpu.physical_memory[0] = 1;


    cpu.running = true;
    for (int i = 0; i < 16 && cpu.running; i++) inst_cycle(&cpu);
    destroy_cpu(&cpu);
    return 0;
}