#ifndef __STM32l0_NVIC__
#define __STM32l0_NVIC__
#include <inttypes.h>
typedef int8_t IRQn_t;

#define PEND_SV_IRQn -2
#define SYSTICK_IRQn -1

void NVIC_EnableIRQ(IRQn_t IRQn);
void NVIC_DisableIRQ(IRQn_t IRQn);
void NVIC_SetPendingIRQ(IRQn_t IRQn);
void NVIC_ClearPendingIRQ(IRQn_t IRQn);
uint32_t NVIC_GetPendingIRQ(IRQn_t IRQn);
void NVIC_SetPriority(IRQn_t IRQn, uint8_t priority);
uint32_t NVIC_GetPriority(IRQn_t IRQn);
#endif
