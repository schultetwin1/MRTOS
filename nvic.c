#include "nvic.h"

typedef struct {
  uint32_t _reserved3  : 12;
  uint32_t VECTPENDING :  6;
  uint32_t _reserved2  :  7;
  uint32_t PENDSTCLR   :  1;
  uint32_t PENDSTSET   :  1;
  uint32_t PENDSVCLR   :  1;
  uint32_t PENDSVSET   :  1;
  uint32_t _reserved1  :  2;
  uint32_t NMIPENDSET  :  1;
} ICSR_t;

typedef struct {
  uint16_t _reserved1;
  uint8_t  PRI_14;
  uint8_t  PRI_15;
} SHPR3_t;

static ICSR_t  volatile * const ICSR  = (ICSR_t  volatile * const)(0xE000ED04);
static SHPR3_t volatile * const SHPR3 = (SHPR3_t volatile * const)(0xE000ED20);

void NVIC_EnableIRQ(IRQn_t IRQn) {
  uint32_t * const NVIC_ISER = (uint32_t * const)0xE000E100;
  *NVIC_ISER = 0x1 << IRQn;
}

void NVIC_DisableIRQ(IRQn_t IRQn) {
  uint32_t * const NVIC_ICER = (uint32_t * const)0xE000E180;
  *NVIC_ICER = 0x1 << IRQn;
}

void NVIC_SetPendingIRQ(IRQn_t IRQn) {
  if (IRQn >= 0) {
    uint32_t * const NVIC_ISPR = (uint32_t * const)0xE000E200;
    *NVIC_ISPR = 0x1 << IRQn;
    return;
  } 

  switch (IRQn) {
    case PEND_SV_IRQn:
      ICSR->PENDSVSET = 1;
      break;
    // @TODO: add rest of negative IRQs
  }
}

void NVIC_ClearPendingIRQ(IRQn_t IRQn) {
  if (IRQn >= 0) {
    uint32_t * const NVIC_CSPR = (uint32_t * const)0xE000E280;
    *NVIC_CSPR = 0x1 << IRQn;
    return;
  }

  switch (IRQn) {
    case PEND_SV_IRQn:
      ICSR->PENDSVCLR = 1;
      break;
    // @TODO: add rest of negative IRQs
  }

}

uint32_t NVIC_GetPendingIRQ(IRQn_t IRQn) {
  if (IRQn >= 0) {
    uint32_t * const NVIC_ISPR = (uint32_t * const)0xE000E200;
    return (*NVIC_ISPR & (0x1 << IRQn));
  }

  switch (IRQn) {
    case PEND_SV_IRQn:
      return ICSR->PENDSVSET;
    // @TODO: add rest of negative IRQs
  }
  // @TODO: THIS IS AN ERROR
  return 0xFF;
}

void NVIC_SetPriority(IRQn_t IRQn, uint8_t priority) {
  if (IRQn >= 0) {
    uint32_t * const NVIC_IPR = (uint32_t * const)0xE000E400;
    int index = IRQn / 4;
    int offset = IRQn % 4;

    uint32_t priorities = NVIC_IPR[index];

    // 0 out  priority
    priorities &= ~(0xF << (offset * 4));

    // set new priority
    priorities |= (priority << (offset * 4));

    NVIC_IPR[index] = priorities;
    return;
  }

  switch (IRQn) {
    case PEND_SV_IRQn:
      SHPR3->PRI_14 = priority;
      break;
    // @TODO: add rest of negative IRQs
  }
}

uint32_t NVIC_GetPriority(IRQn_t IRQn) {
  if (IRQn >= 0) {
    uint32_t * const NVIC_IPR = (uint32_t * const)0xE000E400;
    int index = IRQn / 4;
    int offset = IRQn % 4;

    uint32_t priorities = NVIC_IPR[index];

    // shift over priorities
    priorities >>= (offset * 4);

    // 0 out higher bits
    priorities &= 0x0000000F;
    return priorities;
  }

  switch (IRQn) {
    case PEND_SV_IRQn:
      return SHPR3->PRI_14;
    // @TODO: add rest of negative IRQs
  }
  // @TODO: THIS IS AN ERROR
  return 0xFF;
}
