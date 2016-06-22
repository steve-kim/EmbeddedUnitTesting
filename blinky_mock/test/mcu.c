#include "mcu.h"

uint32_t registers[0xE0042000];

void set_register(uint32_t address, uint32_t value)
{
    registers[address] = value;
}

uint32_t get_register(uint32_t address)
{
    return registers[address];
}
