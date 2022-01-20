# computer

An 8-bit machine with 16 bits of address space. This is my attempt 
at virtual memory, access modes, and preemptive multitasking.

here it is running the `multiple-handlers.asm` program

[![asciicast](https://asciinema.org/a/W5WMRRv75lQk24p1EoZhWXtDA.png)](https://asciinema.org/a/W5WMRRv75lQk24p1EoZhWXtDA)

the assembly program

```asm
; $ cat test.asm
.data
    page_table:
        .byte   0x00
    incrementor:
        .byte   0x00

.text
    main:
        vset    page_table
        cset    0x40
        clac
        stor    incrementor
    loop:
        add     incrementor
        addi    0x01
        stor    incrementor
        clac
```


assembles to the binary file
    
    $ python assembler.py -f test.asm -o test
    $ hexdump test
    0000000 e1 15 00 e0 40 30 40 16 00 20 16 00 10 01 40 16
    0000010 00 30 50 09 00 00 00                           
    0000017

