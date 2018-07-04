#ifndef CPU_SIM_ISA_H
#define CPU_SIM_ISA_H

#include <stdint.h>


#define     I_NOOP     0x00
#define     I_ADDI     0x10
#define     I_SUBI     0x11
#define     I_ADD      0x20
#define     I_SUB      0X21
#define     I_CLAC     0x30
#define     I_STOR     0x40
#define     I_BEQZ     0x50
#define     I_HALT     0xff


#endif //CPU_SIM_ISA_H
