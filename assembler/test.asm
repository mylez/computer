main:
    vset    page_table
    cset    0x40 # cset vmem
    clac
    addi    0xab
    stor    0x0000
    halt
page_table:
    .wide 0xbbbb
    .wide 0xbbbb
    .wide 0xbbbb
    .wide 0xbbbb