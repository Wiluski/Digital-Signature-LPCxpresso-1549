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

	//task to handle the time recording, will be implemented fully on a future date

	TickType_t currentTickCount;
	TickType_t currentTickCountRSA;
	TickType_t currentTickCountECC;
	EventBits_t xBit, xBitRSA, xBitECC;
	while(1){
		xBit = xEventGroupWaitBits(xEventGroup, (MAIN_FIRST_BIT),
				pdFALSE, pdFALSE, portMAX_DELAY);

		if((xBit & MAIN_FIRST_BIT ) == MAIN_FIRST_BIT){
			currentTickCount = xTaskGetTickCountFromISR();
		}

		xBitRSA = xEventGroupWaitBits(xEventGroup, (MAIN_SECOND_BIT),
				pdFALSE, pdFALSE, portMAX_DELAY);
		if((xBitRSA & MAIN_SECOND_BIT) == MAIN_SECOND_BIT){
			currentTickCountRSA = xTaskGetTickCountFromISR() - currentTickCount;
			guard.lock();

			DEBUGOUT("Ticks from last RSA signature: %lu\r\n", currentTickCountRSA);

			guard.unlock();
		}
		xBitECC = xEventGroupWaitBits(xEventGroup, (MAIN_THIRD_BIT),
						pdFALSE, pdFALSE, portMAX_DELAY);

		xEventGroupWaitBits(xEventGroup, MAIN_FIRST_BIT,pdFALSE, pdFALSE, portMAX_DELAY);
		if((xBitECC & MAIN_THIRD_BIT) == MAIN_THIRD_BIT){
			currentTickCountECC = xTaskGetTickCountFromISR() - currentTickCountRSA;
					guard.lock();

					DEBUGOUT("Ticks from last ECC signature: %lu\r\n", currentTickCountECC);

					guard.unlock();

		}
		xEventGroupClearBits(xEventGroup, ALL_BITS);


	}
}



