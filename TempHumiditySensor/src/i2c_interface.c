/*
 * i2c_interface.c
 *
 *  Created on: Jun 24, 2016
 *      Author: steve-kim
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_i2c.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"


void initialize_i2c()
{
	//
	// The I2C0 peripheral must be enabled before use.
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

	//
	// For this example I2C0 is used with PortB[3:2].  The actual port and
	// pins used may be different on your part, consult the data sheet for
	// more information.  GPIO port B needs to be enabled so these pins can
	// be used.
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

	//
	// Configure the pin muxing for I2C0 functions on port B2 and B3.
	// This step is not necessary if your part does not support pin muxing.
	//
	GPIOPinConfigure(GPIO_PB2_I2C0SCL);
	GPIOPinConfigure(GPIO_PB3_I2C0SDA);

	//
	// Select the I2C function for these pins.  This function will also
	// configure the GPIO pins pins for I2C operation, setting them to
	// open-drain operation with weak pull-ups.  Consult the data sheet
	// to see which functions are allocated per pin.
	//
	GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
	GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

	I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);
}

uint32_t i2c_read_byte(uint8_t slave_address, uint8_t register_address)
{
	//
	// Tell the master module what address it will place on the bus when
	// communicating with the slave.  Set the address to SLAVE_ADDRESS
	// (as set in the slave module).  The receive parameter is set to false
	// which indicates the I2C Master is initiating a writes to the slave.  If
	// true, that would indicate that the I2C Master is initiating reads from
	// the slave.
	//
	I2CMasterSlaveAddrSet(I2C0_BASE, slave_address, false);

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
	I2CMasterSlaveAddrSet(I2C0_BASE, slave_address, true);

	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

	while(I2CMasterBusy(I2C0_BASE))
	{
	}

	return I2CMasterDataGet(I2C0_BASE);
}
