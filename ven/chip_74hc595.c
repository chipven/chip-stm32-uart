#include "chip_74hc595.h"

void
chip_74hc595_sendBytes(struct chip_74hc595 in, unsigned int how_many_bytes,
                       unsigned int data) {
    for (unsigned int i = 0; i < how_many_bytes * 8; i++) {
        *in.serialInput = data >> (how_many_bytes * 8 - 1);
        data <<= 1;
        *in.shiftClock = 0;
        *in.shiftClock = 1;
    }
    *in.resetClock = 1;
    *in.resetClock = 0;
}
