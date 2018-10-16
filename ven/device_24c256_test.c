#include "device_24c256.h"
#include "../make/stm32f103c8t6.h"
#include "device_8digi.h"
#include "system_util.h"
void
device_24c256_test() {
    on_72m();
    /* enable GPIOB in RCC->APB2ENR register */
    RCC->APB2ENR = 0x00000008;
    /* enable GPIOB pin 8 & 9 to floating mode */
    GPIOB->CRH &= 0xffffff00;
    GPIOB->CRH |= 0x00000077;
    /* enable GPIOB pin 12 13 14 to out mode */
    GPIOB->CRH &= 0xf000ffff;
    GPIOB->CRH |= 0x03330000;

    struct device_24c256 d24;
    d24.protocol_i2c.scl =
        (unsigned int *)(0x42000000 + 0x10c0c * 0x20 + 9 * 4);
    d24.protocol_i2c.sda =
        (unsigned int *)(0x42000000 + 0x10c0c * 0x20 + 8 * 4);
    d24.protocol_i2c.scl_read =
        (unsigned int *)(0x42000000 + 0x10c08 * 0x20 + 9 * 4);
    d24.protocol_i2c.sda_read =
        (unsigned int *)(0x42000000 + 0x10c08 * 0x20 + 8 * 4);
    device_24c256_writeByte(d24, 0x0005, 0x05);
    unsigned char data = device_24c256_readByte(d24, 0x0001);

    struct device_8digi d8;
    d8.chip_74hc595.serialInput =
        (unsigned int *)(0x42000000 + 0x10c0c * 0x20 + 12 * 4);
    d8.chip_74hc595.resetClock =
        (unsigned int *)(0x42000000 + 0x10c0c * 0x20 + 13 * 4);
    d8.chip_74hc595.shiftClock =
        (unsigned int *)(0x42000000 + 0x10c0c * 0x20 + 14 * 4);
    d8.number_system = 16;
    d8.type_digital = 1;

    while (1) {
        device_8digi_show(d8, data);
    }
}
