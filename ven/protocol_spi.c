#include "protocol_spi.h"
#include "system_util.h"

unsigned char
protocol_spi_write(struct protocol_spi in, unsigned char tx) {
    unsigned char rx = 0;
    for (int i = 0; i < 8; i++) {
        // down
        *in.sclk = 0;
        // send
        if (tx & 0x80)
            *in.mosi = 1;
        else
            *in.mosi = 0;
        // receive
        rx <<= 1;
        if (*in.miso) {
            rx++;
        }
        tx <<= 1;
        // up
        *in.sclk = 1;
    }
    return rx;
}
