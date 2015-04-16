#include "drivers/nvic.h"
#include "drivers/port_systick.h"

typedef volatile struct {
  uint32_t SYST_CSR;
  uint32_t SYST_RVR;
  uint32_t SYST_CVR;
  const uint32_t SYST_CALIB;
} systick_t;

static systick_t * const SYSTICK = (systick_t * const)0xE000E010;

void systick_enable() {
  SYSTICK->SYST_CSR |= 1;
}

void systick_disable() {
  SYSTICK->SYST_CSR &= ~1;
}

void systick_countflag() {
  SYSTICK->SYST_CSR;
}

void systick_enable_int() {
  SYSTICK->SYST_CSR |= 2;
}

void systick_disable_int() {
  SYSTICK->SYST_CSR &= ~2;
}

void systick_internal_src() {
  SYSTICK->SYST_CSR |= 4;
}

void systick_external_src() {
  SYSTICK->SYST_CSR &= ~4;
}

void systick_set_reload_value(uint32_t value) {
  value &= 0x00FFFF;
  SYSTICK->SYST_RVR = value;
}

uint32_t systick_get_reload_value() {
  return SYSTICK->SYST_RVR;
}

uint32_t systick_get_count() {
  return SYSTICK->SYST_CVR;
}

void systick_init() {
  // Program reload
  // Cause tick every second
  // @TODO: Not working
  systick_set_reload_value(0x00F42400);
  //systick_set_reload_value(0x00FFFFFF);

  // Clear current register
  systick_get_count();

  // Set to internally sourced clock
  systick_internal_src();

  // Enable interrupts
  systick_enable_int();

  // Enable Tick
  systick_enable();
}
