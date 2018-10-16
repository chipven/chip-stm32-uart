#include "device_sd.h"

u8
device_sd_clock(Device_sd sd, u8 cs, u8 clock) {
    *sd.cs = cs;
    for (u8 i = 0; i < clock; i++) {
        *sd.sclk = 0;
        *sd.sclk = 1;
    }
    return 0xac;
}

u8
device_sd_write(Device_sd sd, u8 Tx) {
    u8 Rx = 0;
    *sd.cs = 0;
    *sd.sclk = 1;
    for (u8 i = 0; i < 8; i++) {
        if (Tx & 0x80) {
            *sd.mosi = 1;
        } else {
            *sd.mosi = 0;
        }
        Tx <<= 1;
        *sd.sclk = 0;
        Rx <<= 1;
        if (*sd.miso == 1) {
            Rx |= 0x01;
        }
        *sd.sclk = 1;
    }
    return Rx;
}

/*
 * CMD  : 0x40 + command number
 * ACMD : 0xc0 + command number
 */
u8
device_sd_cmd(Device_sd sd, u8 cmd, u32 arg) {
    u8 res = 0xaa;

    if (cmd & 0x80) {
        cmd &= 0x7F;
        res = device_sd_cmd(sd, 0x40 + 55, 0);
        if (res > 1) return res;
    }

    device_sd_write(sd, 0xff);
    device_sd_write(sd, 0xff);

    device_sd_write(sd, cmd);
    device_sd_write(sd, arg >> 24);
    device_sd_write(sd, arg >> 16);
    device_sd_write(sd, arg >> 8);
    device_sd_write(sd, arg);

    u8 crc = 0x01;
    if (cmd == 0x40 + 0) crc = 0x95;
    if (cmd == 0x40 + 8) crc = 0x87;
    device_sd_write(sd, crc);

    u8 i = 10;
    do {
        res = device_sd_write(sd, 0xff);
    } while ((res & 0x80) && --i);

    return res;
}

u8
device_sd_learn(Device_sd sd) {
    u8 res;
    for (u8 i = 0; i < 0xf; i++) {
        res = device_sd_cmd(sd, 0x40 + 0, 0x00000000);
        if (res == 1) break;
    }
    return res;
}
