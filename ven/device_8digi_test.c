#include "device_8digi.h"
void device_8digi_show_test()
{
    RCC->APB2ENR |= 0x00000008;
    GPIOB->CRH &= 0xe000eeee;
    GPIOB->CRH |= 0x03330000;
    struct device_8digi d8;
    d8.chip_74hc595.serialInput =
        (unsigned int *)(0x42000000 + 0x10c0c * 0x20 + 12 * 4);
    d8.chip_74hc595.resetClock =
        (unsigned int *)(0x42000000 + 0x10c0c * 0x20 + 13 * 4);
    d8.chip_74hc595.shiftClock =
        (unsigned int *)(0x42000000 + 0x10c0c * 0x20 + 14 * 4);
    d8.number_system = 16;
    d8.type_digital = 1;
    unsigned int number = 0x20;
    while (1)
    {
        device_8digi_show(d8, number);
    }
}
