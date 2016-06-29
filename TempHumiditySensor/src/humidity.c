#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_i2c.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"

#include "i2c_interface.h"
#include "humidity.h"

#define SLAVE_ADDRESS 0x5F

static uint8_t H0_RH = 0;
static uint8_t H1_RH = 0;
static int16_t H0_T0_OUT = 0;
static int16_t H1_T0_OUT = 0;

int16_t get_temperature_reading()
{
	return 50;
}

int16_t get_humidity_reading()
{
	int16_t H_OUT = 0;

	uint8_t h_out_l = i2c_read_byte(SLAVE_ADDRESS, 0x28);
	uint8_t h_out_h = i2c_read_byte(SLAVE_ADDRESS, 0x29);
	H_OUT = (h_out_h << 8) | h_out_l;

	int16_t humidity = ((H1_RH - H0_RH) * (H_OUT - H0_T0_OUT) / (H1_T0_OUT - H0_T0_OUT)) + H0_RH;

	return humidity;
}


void initialize_humidity()
{
	H0_RH = i2c_read_byte(SLAVE_ADDRESS, 0x30) / 2;
	H1_RH = i2c_read_byte(SLAVE_ADDRESS, 0x31) / 2;

	uint8_t h0_t0_l = i2c_read_byte(SLAVE_ADDRESS, 0x36);
	uint8_t h0_t0_h = i2c_read_byte(SLAVE_ADDRESS, 0x37);
	H0_T0_OUT = (h0_t0_h << 8) | (h0_t0_l);

	uint8_t h1_t0_l = i2c_read_byte(SLAVE_ADDRESS, 0x3A);
	uint8_t h1_t0_h = i2c_read_byte(SLAVE_ADDRESS, 0x3B);
	H1_T0_OUT = (h1_t0_h << 8) | (h1_t0_l);
}
