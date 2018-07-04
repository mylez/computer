# computer

An 8-bit machine with 16 bits of address space. This is my attempt 
at virtual memory, access modes, and preemptive multitasking.

the assembly program

    $ cat test.asm
    clac
    addi 5
    stor 254
    subi 1
    stor 127
    halt


assembles to the binary file
    
    $ python assembler.py -f test.asm -o test
    $ hexdump test
    0000000 30 10 05 40 fe 00 11 01 40 7f 00 ff            
    000000c
