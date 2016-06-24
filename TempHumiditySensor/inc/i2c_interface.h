/*
 * i2c_interface.h
 *
 *  Created on: Jun 24, 2016
 *      Author: steve-kim
 */

#ifndef INC_I2C_INTERFACE_H_
#define INC_I2C_INTERFACE_H_

void initialize_i2c();
uint8_t i2c_read_byte(uint8_t slave_address, uint8_t register_address);

#endif /* INC_I2C_INTERFACE_H_ */
