#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_i2c.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"

#include "i2c_interface.h"

//*****************************************************************************
//
// Number of I2C data packets to send.
//
//*****************************************************************************
#define NUM_I2C_DATA 3

//*****************************************************************************
//
// Set the address for slave module. This is a 7-bit address sent in the
// following format:
//                      [A6:A5:A4:A3:A2:A1:A0:RS]
//
// A zero in the "RS" position of the first byte means that the master
// transmits (sends) data to the selected slave, and a one in this position
// means that the master receives data from the slave.
//
//*****************************************************************************
#define SLAVE_ADDRESS 0x5F

static uint8_t H0_RH;
static uint8_t H1_RH;
static int16_t H0_T0_OUT;
static int16_t H1_T0_OUT;

static uint32_t read_register(uint8_t register_address)
{
	//
	// Tell the master module what address it will place on the bus when
	// communicating with the slave.  Set the address to SLAVE_ADDRESS
	// (as set in the slave module).  The receive parameter is set to false
	// which indicates the I2C Master is initiating a writes to the slave.  If
	// true, that would indicate that the I2C Master is initiating reads from
	// the slave.
	//
	I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDRESS, false);

	I2CMasterDataPut(I2C0_BASE, register_address);
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

	while(I2CMasterBusy(I2C0_BASE))
	{
	}

	//
	// Tell the master module what address it will place on the bus when
	// communicating with the slave.  Set the address to SLAVE_ADDRESS
	// (as set in the slave module).  The receive parameter is set to false
	// which indicates the I2C Master is initiating a writes to the slave.  If
	// true, that would indicate that the I2C Master is initiating reads from
	// the slave.
	//
	I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDRESS, true);

	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

	while(I2CMasterBusy(I2C0_BASE))
	{
	}

	return I2CMasterDataGet(I2C0_BASE);
}


void get_humidity_reading()
{
	int16_t H_OUT = 0;

	uint8_t h_out_l = read_register(0x28);
	uint8_t h_out_h = read_register(0x29);
	H_OUT = (h_out_h << 8) | h_out_l;

	int16_t humidity = ((H1_RH - H0_RH) * (H_OUT - H0_T0_OUT) / (H1_T0_OUT - H0_T0_OUT)) + H0_RH;

	return;
}


void initialize_humidity()
{
	H0_RH = read_register(0x30) / 2;
	H1_RH = read_register(0x31) / 2;

	uint8_t h0_t0_l = read_register(0x36);
	uint8_t h0_t0_h = read_register(0x37);
	H0_T0_OUT = (h0_t0_h << 8) | (h0_t0_l);

	uint8_t h1_t0_l = read_register(0x3A);
	uint8_t h1_t0_h = read_register(0x3B);
	H1_T0_OUT = (h0_t0_h << 8) | (h0_t0_l);
}
