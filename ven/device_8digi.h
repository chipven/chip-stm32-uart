#ifndef VEN_8DIGI_H
#define VEN_8DIGI_H
#include "../make/stm32f103c8t6.h"
#include "chip_74hc595.h"
typedef struct device_8digi {
    struct chip_74hc595 chip_74hc595;
    unsigned int type_digital;   // choose 1/2/* common cathode or anode
    unsigned int number_system;  // numeric for binary decimal hexadecimal
}Device_8digi;
void
device_8digi_show(struct device_8digi in, unsigned int number_to_show);
#endif /* VEN_8DIGI_H */
