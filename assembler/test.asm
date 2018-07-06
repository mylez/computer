main:                       ; beginning of program
    vset    page_table      ; set the page table pointer
    cset    0x40            ; enable virtual memory
    clac                    ; clear accumulator
    addi    0xab            ; load 0xab into accumulator
    stor    0x0000          ; store it at virtual address 0x0000
    halt                    ; stop execution
page_table:                 ;
    .wide 0x0000            ;
    .wide 0x0000            ;
    .wide 0x0000            ;
    .wide 0x0000            ;
