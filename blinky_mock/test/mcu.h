#ifndef MCU_H
#define MCU_H
#endif

#include <stdint.h>

uint32_t registers[0xE0042000];

void set_register(uint32_t address, uint32_t value);
uint32_t get_register(uint32_t address);
