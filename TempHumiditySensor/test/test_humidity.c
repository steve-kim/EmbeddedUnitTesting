#include "humidity.h"
#include "unity.h"
#include "mock_mcu.h"
#include "mock_i2c_interface.h"

#define SLAVE_ADDRESS 0x5F

extern uint32_t registers[];

void setUp(void)
{
    //H0_RH and H1_RH
    i2c_read_byte_ExpectAndReturn(SLAVE_ADDRESS, 0x30, 0x16);
    i2c_read_byte_ExpectAndReturn(SLAVE_ADDRESS, 0x31, 0x0A);

    //h0_t0_l and h0_t0_h
    i2c_read_byte_ExpectAndReturn(SLAVE_ADDRESS, 0x36, 0x0B);
    i2c_read_byte_ExpectAndReturn(SLAVE_ADDRESS, 0x37, 0x05);

    //h1_t0_l and h1_t0_h
    i2c_read_byte_ExpectAndReturn(SLAVE_ADDRESS, 0x3A, 0x05);
    i2c_read_byte_ExpectAndReturn(SLAVE_ADDRESS, 0x3B, 0x0B);

    //Set same global values on every test
    initialize_humidity();
}

void tearDown(void)
{
}

void test_humidityreading_whenhoutismax()
{
    //Get h_out_l and h_out_h values
    i2c_read_byte_ExpectAndReturn(SLAVE_ADDRESS, 0x28, 0xFF);
    i2c_read_byte_ExpectAndReturn(SLAVE_ADDRESS, 0x29, 0x7F);

    TEST_ASSERT_INT16_WITHIN(1, -111, get_humidity_reading());
}

void test_humidityreading_whenhoutismin()
{
    //Get h_out_l and h_out_h values
    i2c_read_byte_ExpectAndReturn(SLAVE_ADDRESS, 0x28, 0x01);
    i2c_read_byte_ExpectAndReturn(SLAVE_ADDRESS, 0x29, 0x80);

    TEST_ASSERT_INT16_WITHIN(1, 145, get_humidity_reading());
}

