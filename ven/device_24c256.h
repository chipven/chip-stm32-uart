#include "../make/stm32f103c8t6.h"
#include "protocol_i2c.h"

struct device_24c256 {
    struct protocol_i2c protocol_i2c;
};

void
device_24c256_writeByte(struct device_24c256 in, unsigned char addr,
                        unsigned char data);
unsigned char
device_24c256_readByte(struct device_24c256 in, unsigned char addr);
