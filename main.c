#include <stdio.h>
#include "control.h"
#include "cpu.h"
#include "util.h"


int main()
{
    cpu_t cpu = make_cpu();
    load_mem("assembler/test", &cpu);

    start(&cpu);

    destroy_cpu(&cpu);
    return 0;
}