#include "led.h"
#include "unity.h"
#include "mock_mcu.h"

//uint32_t registers[0xE0042000];
extern uint32_t registers[];

void setUp(void)
{
}

void tearDown(void)
{
}

void test_LedOn_should_SetGpio(void)
{
    led_on();

    get_register_ExpectAndReturn(0x40025020,0x00000008);
    TEST_ASSERT_EQUAL_UINT32(registers[0x40025020], get_register(0x40025020));
}

void test_LedOff_should_ClearGpio(void)
{
    led_off();

    get_register_ExpectAndReturn(0x40025020,0x00000000);
    TEST_ASSERT_EQUAL_UINT32(registers[0x40025020], get_register(0x40025020));
}
