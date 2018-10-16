#ifndef __device_mhsd_spi_h_
#define __device_mhsd_spi_h_

#include "../make/stm32f103c8t6.h"

typedef struct device_sd {
    u32* cs;
    u32* sclk;
    u32* mosi;
    u32* miso;
} Device_sd;

u8
device_sd_learn(Device_sd sd);
#endif /* __device_mhsd_spi_h_ */
