/*
 * vWatchDog.cpp
 *
 *  Created on: Feb 20, 2020
 *      Author: Ville Vainio
 */

#include "vWatchDog.h"

EventGroupHandle_t xEventGroup;
extern Fmutex guard;


void vWatchDog(void *pvParameters){

	TickType_t currentTickCount1 = 0;
	TickType_t currentTickCount2 = 0;
	EventBits_t xBits;
	while(1){
		xBits = xEventGroupWaitBits(xEventGroup, (MAIN_FIRST_BIT || MAIN_SECOND_BIT),
				pdFALSE, pdFALSE, portMAX_DELAY);
		//xEventGroupWaitBits(xEventGroup, mainFIRST_BIT,pdFALSE, pdFALSE, portMAX_DELAY);
		currentTickCount1 = xTaskGetTickCount();
		currentTickCount2 = currentTickCount1 - currentTickCount2;
		if((xBits & MAIN_FIRST_BIT) == MAIN_FIRST_BIT){
			guard.lock();
			Board_UARTPutSTR("Ticks from last RSA signature:");
			Board_UARTPutChar(currentTickCount2);
			Board_UARTPutChar('\n');
			Board_UARTPutChar('\r');
			//DEBUGOUT("Ticks from last RSA signature: %lu\r\n", currentTickCount2);
			xEventGroupClearBits(xEventGroup, MAIN_FIRST_BIT);
			guard.unlock();
		}else if((xBits & MAIN_SECOND_BIT) == MAIN_SECOND_BIT){
			guard.lock();
			Board_UARTPutSTR("Ticks from last ECC signature:");
			Board_UARTPutChar(currentTickCount2);
			Board_UARTPutChar('\n');
			Board_UARTPutChar('\r');
			//DEBUGOUT("Ticks from last ECC signature: %lu\r\n", currentTickCount2);
			xEventGroupClearBits(xEventGroup, MAIN_SECOND_BIT);
			guard.unlock();
		}
	}
}



