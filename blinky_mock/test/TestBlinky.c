#include "led.h"
#include "mock_mcu.h"
#include "unity.h"

//uint32_t registers[0xE0042000];

void setUp(void)
{
}

void tearDown(void)
{
}

void test_LedOn_should_SetGpio(void)
{
    led_on();
    TEST_ASSERT_EQUAL_UINT32(registers[0x40025020], 0x00000008);
}

void test_LedOff_should_ClearGpio(void)
{
    led_off();
    TEST_ASSERT_EQUAL_UINT32(registers[0x40025020], 0x00000000);
}
