.data
page_table:
    .byte   0x00
    .byte   0x00
    .byte   0x00
    .byte   0x00
incrementor:
    .byte   0x00
stupid_byte:
    .byte   0x00

.text
handler_1:
    vset    page_table
    cset    0x40
    tset    0x30                ; set preemption timer to 16 instructions
    clac
    beqz    set_handler_2

    noop ; empty space
    noop
    noop
    noop
    noop
    noop
    noop
    noop
    noop
    noop
    noop
    noop
    noop
    noop
    noop

user_loop_1:
    ;cuns    0x80                ; this is illegal in user mode
    clac
    addi    1
    addi    2
    addi    3
    addi    4
    addi    5
    stor    stupid_byte
    clac
    beqz    user_loop_1

    noop ; empty space
    noop
    noop
    noop
    noop
    noop
    noop
    noop
    noop
    noop
    noop
    noop
    noop
    noop
    noop

user_loop_2:
    ;cuns    0x80                ; this is illegal in user mode
    clac
    add     incrementor
    addi    1
    stor    incrementor
    clac
    beqz    user_loop_2


handler_2:
    vset    page_table
    tset    0x30                ; set preemption timer to 16 instructions
    clac
    beqz    set_handler_1
set_handler_1:
    eset    handler_1           ; designate code for exception handling
    cset    0x20                ; switch on timer
    cset    0x80                ; switch on user mode
    clac
    beqz user_loop_1

set_handler_2:
    eset    handler_2           ; designate code for exception handling
    cset    0x20                ; switch on timer
    cset    0x80                ; switch on user mode
    clac
    beqz user_loop_2