#ifndef VE_TC1117_H
#define VE_TC1117_H
#include "../make/stm32f103c8t6.h"
#define A1 (*(u32 *)(0x42000000 + 0x10c0c * 0x20 + 11 * 4))
#define A2 (*(u32 *)(0x42000000 + 0x10c0c * 0x20 + 10 * 4))
#define B1 (*(u32 *)(0x42000000 + 0x10c0c * 0x20 + 1 * 4))
#define B2 (*(u32 *)(0x42000000 + 0x10c0c * 0x20 + 0 * 4))
void
ven_showMotor();
#endif /* VE_TC1117_H */
