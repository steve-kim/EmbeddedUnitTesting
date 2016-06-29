#include "unity.h"
#include "mock_mcu.h"
#include "mock_humidity.h"

#include "led.h"
#include "timer.h"

extern uint32_t registers[];

void setUp(void)
{
}

void tearDown(void)
{
}

void test_wheninterrupted_thenreadhumidity()
{
    get_humidity_reading_ExpectAndReturn(40);

    Timer0IntHandler();
}

void test_whenhumiditygreaterthan60_thenledturnson()
{
    get_humidity_reading_ExpectAndReturn(70);
    get_register_ExpectAndReturn(0x40025020, 0x00000008);

    Timer0IntHandler();

    TEST_ASSERT_EQUAL_UINT32(registers[0x40025020], get_register(0x40025020));
}

void test_whenhumiditylessthan60_thenledturnsoff()
{
    get_humidity_reading_ExpectAndReturn(40);

    Timer0IntHandler();

    TEST_ASSERT_EQUAL_UINT32(registers[0x40025020], 0x00000000);
}
