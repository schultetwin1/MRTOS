#ifndef __MRTOS_PORT_SPI__
#define __MRTOS_PORT_SPI__
typedef volatile struct __attribute__((packed)) {
  uint16_t CR1;
  uint16_t _reserved1;
  uint16_t CR2;
  uint16_t _reserved2;

  uint16_t SR;
  uint16_t _reserved3;

  uint16_t DR;
  uint16_t _reserved4;

  uint16_t CRCPR;
  uint16_t _reserved5;
  uint16_t RXCRCR;
  uint16_t _reserved6;
  uint16_t TXCRCR;
  uint16_t _reserved7;

  uint16_t I2SCFGR;
  uint16_t _reserved8;
  uint16_t I2SPR;
  uint16_t _reserved9;
} SPI_t;

static SPI_t volatile * const  SPI1 = (SPI_t volatile * const)(0X40013000);
static SPI_t volatile * const  SPI2 = (SPI_t volatile * const)(0X40003800);

#define SPI_BIDIMODE (1 << 15)
#define SPI_BIDIOE   (1 << 14)
#define SPI_CRCEN    (1 << 13)
#define SPI_CRCNEXT  (1 << 12)
#define SPI_DFF      (1 << 11)
#define SPI_RXONLY   (1 << 10)
#define SPI_SSM      (1 << 9)
#define SPI_SSI      (1 << 8)
#define SPI_LSBFIRST (1 << 7)
#define SPI_SPE      (1 << 6)
#define SPI_MSTR     (1 << 2)
#define SPI_CPOL     (1 << 1)
#define SPI_CPHA     (1 << 0)

#define SPI_TXEIE    (1 << 7)
#define SPI_RXNEIE   (1 << 6)
#define SPI_ERRIE    (1 << 5)
#define SPI_FRF      (1 << 4)
#define SPI_SSOE     (1 << 2)
#define SPI_TXDMAEN  (1 << 1)
#define SPI_RXDMAEN  (1 << 0)

#define SPI_FRE      (1 << 8)
#define SPI_BSY      (1 << 7)
#define SPI_OVR      (1 << 6)
#define SPI_MODF     (1 << 5)
#define SPI_CRCERR   (1 << 4)
#define SPI_UDR      (1 << 3)
#define SPI_CHSIDE   (1 << 2)
#define SPI_TXE      (1 << 1)
#define SPI_RXNE     (1 << 0)

typedef enum {
  SPI_CLK_DIV_2   = 0,
  SPI_CLK_DIV_4   = 1,
  SPI_CLK_DIV_8   = 2,
  SPI_CLK_DIV_16  = 3,
  SPI_CLK_DIV_32  = 4,
  SPI_CLK_DIV_64  = 5,
  SPI_CLK_DIV_128 = 6,
  SPI_CLK_DIV_256 = 7
} spi_baudrate_t;

typedef enum {
  SPI_TX_ONLY,
  SPI_RX_ONLY,
  SPI_HALFDUPLEX,
  SPI_DUPLEX
} spi_mode_t;

typedef enum {
  SPI_LSB_FIRST,
  SPI_MSB_FIRST
} spi_endianess_t;

#endif
