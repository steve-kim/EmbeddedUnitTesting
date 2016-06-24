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

/*void test_wheninterrupted_thenreadhumidity()
{
    get_humidity_reading_ExpectAndReturn(40);

    TEST_ASSERT_EQUALS_INT16(40, Timer0IntHandler());
}*/

void test_whenhumiditygreaterthan60_thenledturnson()
{
    get_humidity_reading_ExpectAndReturn(70);

    Timer0IntHandler();

    TEST_ASSERT_EQUAL_UINT32(registers[0x40025020], 0x00000008);
}

void test_whenhumiditylessthan60_thenledturnsoff()
{
    get_humidity_reading_ExpectAndReturn(40);

    Timer0IntHandler();

    TEST_ASSERT_EQUAL_UINT32(registers[0x40025020], 0x00000000);
}
