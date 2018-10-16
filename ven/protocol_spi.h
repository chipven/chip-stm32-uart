#ifndef __protocol_spi_h_
#define __protocol_spi_h_

/* example:
 *struct protocol_spi out;
 *out.cs = (unsigned int *)(0x42000000 + 0x10c0c * 0x20 + 6 * 4);
 *out.sclk = (unsigned int *)(0x42000000 + 0x10c0c * 0x20 + 4 * 4);
 *out.mosi = (unsigned int *)(0x42000000 + 0x10c0c * 0x20 + 5 * 4);
 *out.miso = (unsigned int *)(0x42000000 + 0x10c08 * 0x20 + 3 * 4);
 */

struct protocol_spi {
    unsigned int* cs;
    unsigned int* sclk;
    unsigned int* mosi;
    unsigned int* miso;
};

unsigned char
protocol_spi_write(struct protocol_spi in,unsigned char data);

#endif /* __protocol_spi_h_ */
