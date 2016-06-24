/*
 * timer.c
 *
 *  Created on: Feb 19, 2016
 *      Author: steve-kim
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#include "timer.h"
#include "humidity.h"
#include "led.h"

void Timer0IntHandler(void)
{
	TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);

	if (get_humidity_reading() > 60) {
		led_on();
	} else {
		led_off();
	}
}

void timer_init()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

	// Configure the timer for 16-bit periodic interrupt
	TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC);

	// Interrupt every 500ms
	TimerLoadSet(TIMER0_BASE, TIMER_B, SysCtlClockGet());

	// Enable timer interrupts
	TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
	IntEnable(INT_TIMER0B);
}

void timer_enable()
{
	TimerEnable(TIMER0_BASE, TIMER_B);
}
