/*
 * vWatchDog.cpp
 *
 *  Created on: Feb 20, 2020
 *      Author: Ville Vainio
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "Fmutex.h"
#include "DigitalIoPin.h"
#include "event_groups.h"
#include "vWatchDog.h"

extern EventGroupHandle_t xEventGroup;

//#define main_FIRST_BIT (1UL << 0UL);
//#define main_SECOND_BIT (1UL << 1UL);
//#define main_THIRD_BIT (1UL << 2UL);
//#define ALL_SYNC_BITS (main_FIRST_BIT | main_SECOND_BIT | main_THIRD_BIT);

void vWatchDog(void *pvParameters){


	while(1){
		//xBits = xEventGroupWaitBits(xEventGroup, ALL_SYNC_BITS,
		//		pdTRUE, pdTRUE, timeWait);
	}
}



