.data
page_table:
    .byte   0x00
    .byte   0x00
    .byte   0x00
    .byte   0x00
incrementor:
    .byte   0x00

.text
main:
    vset    page_table
    eset    handle_exception    ; designate code for exception handling
    cset    0x80                ; switch to user mode
    cuns    0x80                ; illegally attempt to raise privileges
    clac
    clac
    clac
    clac
    clac
    clac
    clac
    beqz main
handle_exception:
    halt