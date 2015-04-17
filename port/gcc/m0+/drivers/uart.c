#include <stddef.h>

#include "drivers/port_rcc.h"
#include "drivers/gpio.h"
#include "drivers/port_uart.h"

typedef volatile struct __attribute__((__packed__)) {
  uint8_t UE     : 1;
  uint8_t UESM   : 1;
  uint8_t RE     : 1;
  uint8_t TE     : 1;
  uint8_t IDLEIE : 1;
  uint8_t RXNEIE : 1;
  uint8_t TCIE   : 1;
  uint8_t TXEIE  : 1;
  uint8_t PEIE   : 1;
  uint8_t PS     : 1;
  uint8_t PCE    : 1;
  uint8_t WAKE   : 1;
  uint8_t M0     : 1;
  uint8_t MME    : 1;
  uint8_t CMIE   : 1;
  uint8_t OVER8  : 1;
  uint8_t DEDT   : 5;
  uint8_t DEAT   : 5;
  uint8_t RTOIE  : 1;
  uint8_t EOBIE  : 1;
  uint8_t M1     : 1;
  uint8_t _reserved : 3;
} CR1_t;

_Static_assert(sizeof(CR1_t) == 4, "Incorrectly sized UART CR1 struct");

typedef volatile struct __attribute__((__packed__)) {
  uint8_t _reserved1 : 4;
  uint8_t ADDM7    : 1;
  uint8_t LBDL     : 1;
  uint8_t LBDIE    : 1;
  uint8_t _reserved2 : 1;
  uint8_t LBCL     : 1;
  uint8_t CPHA     : 1;
  uint8_t CPOL     : 1;
  uint8_t CLKEN    : 1;
  uint8_t STOP     : 2;
  uint8_t LINEN    : 1;
  uint8_t SWAP     : 1;
  uint8_t RXINV    : 1;
  uint8_t TXINV    : 1;
  uint8_t DATAINV  : 1;
  uint8_t MSBFIRST : 1;
  uint8_t ABREN    : 1;
  uint8_t ABRMOD   : 2;
  uint8_t RTOEN    : 1;
  uint8_t ADD      : 8;
} CR2_t;

_Static_assert(sizeof(CR2_t) == 4, "Incorrectly sized UART CR2 struct");

typedef volatile struct __attribute__((__packed__)) {
  uint8_t EIE      : 1;
  uint8_t IREN     : 1;
  uint8_t IRLP     : 1;
  uint8_t HDSEL    : 1;
  uint8_t NACK     : 1;
  uint8_t SCEN     : 1;
  uint8_t DMAR     : 1;
  uint8_t DMAT     : 1;
  uint8_t RTSE     : 1;
  uint8_t CTSE     : 1;
  uint8_t CTSIE    : 1;
  uint8_t ONEBIT   : 1;
  uint8_t OVRDIS   : 1;
  uint8_t DDRE     : 1;
  uint8_t DEM      : 1;
  uint8_t DEP      : 1;
  uint8_t _reserved1 : 1;
  uint8_t SCARCNT  : 3;
  uint8_t WUS      : 2;
  uint8_t WUFIE    : 1;
  uint16_t _reserved2 : 9;
} CR3_t;

_Static_assert(sizeof(CR3_t) == 4, "Incorrectly sized UART CR3 struct");

typedef volatile struct __attribute__((__packed__)) {
  uint8_t PSC : 8;
  uint8_t GT  : 8;
  uint16_t _reserved : 16;
} GTPR_t;

_Static_assert(sizeof(GTPR_t) == 4, "Incorrectly sized UART GTPR struct");

typedef volatile struct __attribute__((__packed__)) {
  uint32_t RTO  : 24;
  uint8_t  BLEN : 8;
} RTOR_t;

_Static_assert(sizeof(RTOR_t) == 4, "Incorrectly sized UART RTOR struct");

typedef volatile struct __attribute__((__packed__)) {
  uint8_t ABRRQ : 1;
  uint8_t SBKRQ : 1;
  uint8_t MMRQ  : 1;
  uint8_t RXFRQ : 1;
  uint8_t TXFRQ : 1;
  uint32_t _reserved : 27;
} RQR_t;

_Static_assert(sizeof(RQR_t) == 4, "Incorrectly sized UART RQR struct");

typedef volatile struct __attribute__((__packed__)) {
  uint8_t PE     : 1;
  uint8_t FE     : 1;
  uint8_t NF     : 1;
  uint8_t ORE    : 1;
  uint8_t IDLE   : 1;
  uint8_t RXNE   : 1;
  uint8_t TC     : 1;
  uint8_t TXE    : 1;
  uint8_t LBDF   : 1;
  uint8_t CTSIF  : 1;
  uint8_t CTS    : 1;
  uint8_t RTOF   : 1;
  uint8_t EOBF   : 1;
  uint8_t _reserved1 : 1;
  uint8_t ABRE   : 1;
  uint8_t ABRF   : 1;
  uint8_t BUSY   : 1;
  uint8_t CMF    : 1;
  uint8_t SBKF   : 1;
  uint8_t RWU    : 1;
  uint8_t WUF    : 1;
  uint8_t TEACK  : 1;
  uint8_t REACK  : 1;
  uint16_t _reserved2 : 9;
} ISR_t;

_Static_assert(sizeof(ISR_t) == 4, "Incorrectly sized UART ISR struct");

typedef volatile struct __attribute__((__packed__)) {
  uint8_t PECF    : 1;
  uint8_t FECF    : 1;
  uint8_t NCF     : 1;
  uint8_t ORECF   : 1;
  uint8_t IDLECF  : 1;

  uint8_t _reserved1 : 1;

  uint8_t TCCF    : 1;

  uint8_t _reserved2 : 1;

  uint8_t LBDCF   : 1;
  uint8_t CTSCF   : 1;

  uint8_t _reserved3 : 1;

  uint8_t RTOCF   : 1;
  uint8_t EOBCF   : 1;

  uint8_t _reserved4 : 4;

  uint8_t CMCF    : 1;

  uint8_t _reserved5 : 2;

  uint8_t WUCF    : 1;

  uint16_t _reserved6 : 11;
} ICR_t;

_Static_assert(sizeof(ICR_t) == 4, "Incorrectly sized UART ICR struct");



typedef volatile struct __attribute__((__packed__)) {
  CR1_t CR1;
  CR2_t CR2;
  CR3_t CR3;

  uint16_t     BRR;
  uint16_t     _reserved1;

  GTPR_t GTPR;

  RTOR_t RTOR;

  RQR_t RQR;
  ISR_t ISR;
  ICR_t ICR;

  uint8_t RDR;
  uint8_t _reserved2;
  uint8_t _reserved3;
  uint8_t _reserved4;

  uint8_t TDR;
  uint8_t _reserved5;
  uint8_t _reserved6;
  uint8_t _reserved7;
} USARTx_t;

_Static_assert(sizeof(USARTx_t) == 0x2C, "Incorrectly sized UART struct");

// @TODO: Use more than just UART1
static USARTx_t volatile * const USART1 = (USARTx_t volatile * const)(0x40013800);
// Pin B6  = USART1_TX (AF0)
// Pin B7  = USART1_RX (AF0)
// Pin A8  = USART1_CK (AF4)
// Pin A9  = USART1_TX (AF4)
// Pin A10 = USART1_RX (AF4)

static USARTx_t volatile * const USART2 = (USARTx_t volatile * const)(0x40004400);

void uart_init() {
  // Enable USART1 clock
  RCC->RCC_APB2ENR |= (1 << 14);

  // Set USART1 clock to system clock
  RCC->RCC_CCIPR &= ~(0x3);
  RCC->RCC_CCIPR |= 0x1;

  // Set TX and RX as pullup and AF4
  // TX
  gpio_set_mode(GPIOA, 9, GPIO_ALT_FUNC_MODE);
  gpio_set_type(GPIOA, 9, GPIO_TYPE_PUSH_PULL);
  gpio_set_pull(GPIOA, 9, GPIO_PULLUP);
  gpio_set_alt_func(GPIOA, 9, GPIO_AF4);

  // RX
  gpio_set_mode(GPIOA, 10, GPIO_ALT_FUNC_MODE);
  gpio_set_type(GPIOA, 10, GPIO_TYPE_PUSH_PULL);
  gpio_set_alt_func(GPIOA, 10, GPIO_AF4);

  // Set word length (CR1)
  USART1->CR1.M1 = 0;
  USART1->CR1.M0 = 0;

  // Disable parity
  USART1->CR1.PCE = 0;

  // Set baud rate (BRR)
  // Setting to 9600
  USART1->BRR = 0xD05;

  // Set number of stop bits (CR2)
  USART1->CR2.STOP = 0x00;

  // Enable USART (write UE bit in CR1 to 1)
  USART1->CR1.UE = 1;

  // Set TE bit to enable TX
  USART1->CR1.TE = 1;
  // Set RE bit to enable RX
  USART1->CR1.RE = 1;

}

void uart_send(uint8_t* data, size_t len) {
  size_t cnt = 0;

  // Wait for TXE
  while (!USART1->ISR.TXE)
    ;

  while (cnt < len) {
    // Write data to send in TDR
    USART1->TDR = *data;

    while (!USART1->ISR.TXE)
      ;
    data++;
    cnt++;
  }

  // Wait for TC = 1
  while (!USART1->ISR.TC)
    ;
}

void uart_recv(uint8_t* data, size_t len) {
  size_t cnt = 0;


  while (cnt < len) {
    // Wait for RXNE
    while (!USART1->ISR.RXNE)
      ;
    
    // Read in data
    *data = USART1->RDR;

    data++;
    cnt++;
  }
}
