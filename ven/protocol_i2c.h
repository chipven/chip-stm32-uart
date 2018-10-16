#ifndef VE_I2C_H
#define VE_I2C_H
#include "../make/stm32f103c8t6.h"
#include "system_util.h"
/*
 * Example:
 *
 * ven_i2c.scl = (unsigned int *)(0x42000000 + 0x10c0c * 0x20 + 9 * 4);
 * ven_i2c.sda = (unsigned int *)(0x42000000 + 0x10c0c * 0x20 + 8 * 4);
 * ven_i2c.scl_read = (unsigned int *)(0x42000000 + 0x10c08 * 0x20 + 9 * 4);
 * ven_i2c.sda_read = (unsigned int *)(0x42000000 + 0x10c08 * 0x20 + 8 * 4);
 *
 */
struct protocol_i2c {
    unsigned int *scl;      /* GPIO pointer clock */
    unsigned int *sda;      /* GPIO pointer data */
    unsigned int *scl_read; /* GPIO pointer read clock */
    unsigned int *sda_read; /* GPIO pointer data clock */
};
void
protocol_i2c_start(struct protocol_i2c in);
void
protocol_i2c_stop(struct protocol_i2c in);
void
protocol_i2c_sendByte(struct protocol_i2c in, unsigned int dataTx);
unsigned int
protocol_i2c_receiveByte(struct protocol_i2c in);
#endif /* VE_I2C_H */
