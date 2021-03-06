/*
 * vWatchDog.h
 *
 *  Created on: Feb 20, 2020
 *      Author: Ville Vainio
 */

#ifndef VWATCHDOG_H_
#define VWATCHDOG_H_

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include "board_api.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Fmutex.h"
#include "event_groups.h"


#define MAIN_FIRST_BIT (1UL << 0UL)
#define MAIN_SECOND_BIT (1UL << 1UL)
#define MAIN_THIRD_BIT (1UL << 2UL)
#define ALL_BITS (MAIN_FIRST_BIT | MAIN_SECOND_BIT | MAIN_THIRD_BIT)

void vWatchDog(void *pvParameters);




#endif /* VWATCHDOG_H_ */
