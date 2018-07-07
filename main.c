#include <stdio.h>
#include "control.h"
#include "cpu.h"
#include "util.h"

// think little endian

int main()
{
    cpu_t cpu = make_cpu();
    load_mem(&cpu, "assembler/test");
    cpu.running = true;
    start(&cpu);
    destroy_cpu(&cpu);
    return 0;
}