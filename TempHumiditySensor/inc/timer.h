/*
 * timer.h
 *
 *  Created on: Feb 19, 2016
 *      Author: steve-kim
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#ifdef TEST
void Timer0IntHandler(void);
#endif

void timer_init();
void timer_enable();

#endif /* INC_TIMER_H_ */
