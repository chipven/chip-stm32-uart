#include "device_8digi.h"

void
device_8digi_show(struct device_8digi in, unsigned int number_to_show) {
    unsigned int _ven_8digi_tab[2][16] = {
        {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6, 0xee, 0x3e,
         0x1a, 0x7a, 0x9e, 0x8e},
        {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83,
         0xa7, 0xa1, 0x86, 0x8e}};

    unsigned int po[] = {
        1,
        in.number_system,
        in.number_system * in.number_system,
        in.number_system * in.number_system * in.number_system,
        in.number_system * in.number_system * in.number_system *
            in.number_system,
        in.number_system * in.number_system * in.number_system *
            in.number_system * in.number_system,
        in.number_system * in.number_system * in.number_system *
            in.number_system * in.number_system * in.number_system,
        in.number_system * in.number_system * in.number_system *
            in.number_system * in.number_system * in.number_system *
            in.number_system,
    };
    unsigned int data;
    for (unsigned int i = 0; i < 8; i++) {
        if (in.type_digital == 0) {
            data = (7 - i) << 8 |
                   _ven_8digi_tab[in.type_digital]
                                 [(number_to_show / po[i] % in.number_system)];
        }
        if (in.type_digital == 1) {
            data = (1 << i) |
                   _ven_8digi_tab[in.type_digital]
                                 [(number_to_show / po[i] % in.number_system)]
                       << 8;
        }
        chip_74hc595_sendBytes(in.chip_74hc595, 2, data);
    }
}
