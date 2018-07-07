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
    beqz    loop