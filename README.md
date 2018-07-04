# cpu-sim

An 8-bit machine with 16 bits of address space. This is my attempt 
at an implementation of virtual memory, access modes, and preemptive 
multitasking.

the assembly program

    $ cat test.asm
    clac
    addi 5
    subi 3
    halt
    
assembles to the binary file
    
    $ python assembler.py -f test.asm -o test
    $ hexdump test
    0000000 30 10 05 11 03 40 0a ff          
    0000008              
