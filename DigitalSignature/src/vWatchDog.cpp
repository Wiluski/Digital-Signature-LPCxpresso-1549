/*
 * vWatchDog.cpp
 *
 *  Created on: Feb 20, 2020
 *      Author: Ville Vainio
 */

#include "vWatchDog.h"

EventGroupHandle_t xEventGroup;



void vWatchDog(void *pvParameters){

	TickType_t currentTickCount1 = 0;
	TickType_t currentTickCount2 = 0;
	EventBits_t xBits;
	while(1){
		xBits = xEventGroupWaitBits(xEventGroup, MAIN_FIRST_BIT,
				pdTRUE, pdTRUE, portMAX_DELAY);
		currentTickCount1 = xTaskGetTickCount();
		currentTickCount2 = currentTickCount1 - currentTickCount2;
		if((xBits & MAIN_FIRST_BIT) == MAIN_FIRST_BIT){
			DEBUGOUT("Ticks from last OK: %lu\r\n", currentTickCount2);
			xEventGroupClearBits(xEventGroup, MAIN_FIRST_BIT);
		}

		}
}



