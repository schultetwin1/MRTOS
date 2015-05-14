#include <inttypes.h>

#include "drivers/rtc.h"
#include "drivers/port_pwr.h"
#include "drivers/port_rcc.h"

#define RTC_ISR_INIT  (1 << 7)
#define RTC_ISR_INITF (1 << 6)
#define RTC_ISR_RSF   (1 << 5)
#define RTC_ISR_WUTWF (1 << 2)
#define RTC_ISR_WUTF  (1 << 10)

#define RTC_CR_WUTE   (1 << 10)

typedef volatile struct {
  uint32_t TR;
  uint32_t DR;
  uint32_t CR;

  uint32_t ISR;

  uint32_t PRER;

  uint16_t WUTR;
  uint16_t _reserved2;

  uint32_t _morereserved;

  uint32_t ALRMAR;
  uint32_t ALRMBR;

  uint8_t WPR;
  uint8_t _reserved3;
  uint8_t _reserved4;
  uint8_t _reserved5;

  uint16_t SSR;
  uint16_t _reserved6;

  uint16_t SHIFTR;
  uint16_t _reserved7;

  uint32_t TSTR;

  uint16_t TSDR;
  uint16_t _reserved8;

  uint16_t TSSSR;
  uint16_t _reserved9;

  uint16_t CALR;
  uint16_t _reserved10;

  uint32_t TAMPCR;

  uint32_t ALRMASSR;
  uint32_t ALRMBSSR;

  uint8_t OR;
  uint8_t _reserved11;
  uint8_t _reserved12;
  uint8_t _reserved13;

  uint32_t BKPR[4];
} rtc_t;

static rtc_t volatile * const RTC  = (rtc_t  volatile * const)(0X40002800);

void rtc_set_clk_src() {
  // Reset RCC RTC
  RCC->RCC_CSR |= (1 << 19);
  RCC->RCC_CSR &= ~(1 << 19);

  // Enable LSI
  if (!(RCC->RCC_CSR & 0x1)) {
    // Set LSION
    RCC->RCC_CSR |= 0x1;

    // wait for LSI RDY
    while (!((RCC->RCC_CSR >> 1) & 0x1))
      ;
  }
  // Set the clock src for RTC to LSI and enable
  RCC->RCC_CSR |= (0x6 << 16);
}

void rtc_init() {
  // Enable PWR Clk
  RCC->RCC_APB1ENR |= (1 << 28);

  // Enable write access to rtc from reset
  PWR->CR |= PWR_DBP;
  
  rtc_set_clk_src();

}

void rtc_set_time() {
  // Disable write protection for all RTC regs
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  // Set INIT bit in RTC_ISR
  RTC->ISR |= RTC_ISR_INIT;
  while (!(RTC->ISR & RTC_ISR_INITF));

  // Set the prescalar (LSI ~ 37 kHz)
  RTC->PRER = (124 << 16) | 295;

  // Set to 24 hrs (CR)
  RTC->CR &= ~(1 << 6);

  // Turn on BYPSHAD
  RTC->CR |= (1 << 5);

  // Set hours
  RTC->TR &= ~(0x3F << 16);
  RTC->TR |= (1 << 20);
  RTC->TR |= (2 << 16); 

  // Set minutes
  RTC->TR &= ~(0x7F << 8);
  RTC->TR |= (5 << 12);
  RTC->TR |= (0 << 8); 

  // Set seconds
  RTC->TR &= ~(0x7F << 0);
  RTC->TR |= (0 << 4);
  RTC->TR |= (0 << 0); 

  // Set year
  RTC->DR &= ~(0xFF << 16);
  RTC->DR |= (1 << 20);
  RTC->DR |= (5 << 16); 

  // Set week day
  RTC->DR &= ~(0x7 << 13);
  RTC->DR |= (4 << 13); 

  // Set month
  RTC->DR &= ~(0x1F << 8);
  RTC->DR |= (0 << 12);
  RTC->DR |= (5 << 8); 

  // Set day
  RTC->DR &= ~(0x3F << 0);
  RTC->DR |= (1 << 4);
  RTC->DR |= (4 << 0); 

  RTC->ISR &= ~(RTC_ISR_INIT);

  // Enable write protection for all RTC regs
  RTC->WPR = 0xFF;
}

void rtc_read_time(char* buf) {
  buf[5] = '\0';
  buf[0] = '0' + ((RTC->TR >> 20) & 0x3);
  buf[1] = '0' + ((RTC->TR >> 16) & 0xF);
  buf[2] = ':';
  buf[3] = '0' + ((RTC->TR >> 12) & 0x7);
  buf[4] = '0' + ((RTC->TR >> 8) & 0xF);
}

void rtc_set_periodic_wakeup() {
  // Disable write protection for all RTC regs
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  // Disable wakeup timer
  RTC->CR &= ~(RTC_CR_WUTE);

  // Ensure bits are unlocked
  while (!(RTC->ISR & RTC_ISR_WUTWF))
    ;

  // Set value of wakeup timer
  RTC->WUTR = 60;
  // Set the desired clk src
  RTC->CR |= 0x4;

  // Enable wakeup timer
  RTC->CR |= RTC_CR_WUTE;

  // Enable write protection for all RTC regs
  RTC->WPR = 0xFF;
}

uint8_t rtc_timer() {
  // Disable write protection for all RTC regs
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  if (RTC->ISR & RTC_ISR_WUTF) {
    RTC->ISR &= ~(RTC_ISR_WUTF);
    return 1;
  }
  // Enable write protection for all RTC regs
  RTC->WPR = 0xFF;
  return 0;
}
