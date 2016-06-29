/*
 * humidity.h
 *
 *  Created on: Jun 23, 2016
 *      Author: steve-kim
 */

#ifndef INC_HUMIDITY_H_
#define INC_HUMIDITY_H_

#include <stdint.h>

#ifdef TEST
uint32_t read_register(uint8_t register_address);
#endif
void initialize_humidity();
int16_t get_temperature_reading();
int16_t get_humidity_reading();

#endif /* INC_HUMIDITY_H_ */
