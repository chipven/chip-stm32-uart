#include "device_24c256.h"

void
device_24c256_writeByte(struct device_24c256 in, unsigned char address,
                        unsigned char data) {
    /* 1 start */
    protocol_i2c_start(in.protocol_i2c);
    /* 2 device addressess | write (write 0 / read 1) */
    protocol_i2c_sendByte(in.protocol_i2c, 0xa0);
    /* 3 data addressess 16 bit  */
    protocol_i2c_sendByte(in.protocol_i2c, (unsigned char)(address >> 8));
    protocol_i2c_sendByte(in.protocol_i2c, (unsigned char)(address & 0x00ff));
    /* 4 write 1 Byte */
    protocol_i2c_sendByte(in.protocol_i2c, data);
    /* 5 stop */
    protocol_i2c_stop(in.protocol_i2c);
}

unsigned char
device_24c256_readByte(struct device_24c256 in, unsigned char address) {
    /* 1 start */
    protocol_i2c_start(in.protocol_i2c);
    /* 2 device addressess | write (write 0 / read 1) */
    protocol_i2c_sendByte(in.protocol_i2c, 0xa0);
    /* 3 data addressess 16 bit */
    protocol_i2c_sendByte(in.protocol_i2c, (unsigned char)(address >> 8));
    protocol_i2c_sendByte(in.protocol_i2c, (unsigned char)(address & 0x00ff));
    /* 4 restart */
    protocol_i2c_start(in.protocol_i2c);
    /* 5 device addressess | read (write 0 / read 1) */
    protocol_i2c_sendByte(in.protocol_i2c, 0xa1);
    /* 6 read one byte */
    unsigned char data;
    data = protocol_i2c_receiveByte(in.protocol_i2c);
    /* 7 stop */
    protocol_i2c_stop(in.protocol_i2c);
    /* return */
    return data;
}
