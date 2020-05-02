/*
 * vPasswordFile.cpp
 *
 *  Created on: Feb 24, 2020
 *      Author: Ville Vainio
 */

#include "vPasswordFile.h"

QueueHandle_t rsaQueue;
QueueHandle_t eccQueue;
Fmutex guardRSA;
Fmutex guardECC;
SemaphoreHandle_t binaryECC;
SemaphoreHandle_t binaryRSA;


void vPasswordFile(void *pvParameters){
	bool init = false;
	passSpecifications s;
	binaryECC = xSemaphoreCreateBinary();
	binaryRSA = xSemaphoreCreateBinary();


	while(1){

		if(init == false){

			for(int j = 0; j < 10; j++){
					//passSpecifications s;
				for(int i = 0; i < 5; i++){
					s.salt[i] = randomCharacter();
					}
				for(int i = 0; i < 8; i++){
					s.pass[i] = randomCharacter();
					}

//					xQueueSendToFront(rsaQueue, (void*) &s, portMAX_DELAY);

//					xSemaphoreTake(binaryRSA, portMAX_DELAY);

//					vTaskDelay(portMAX_DELAY);
					//xSemaphoreTake(binaryRSA, portMAX_DELAY);
					//vTaskDelay(1000);
					xQueueSendToFront(eccQueue, (void*) &s, portMAX_DELAY);

					xSemaphoreTake(binaryECC, portMAX_DELAY);

			}
			init = true;

			}
			//init = true;

	}
}

char randomCharacter(){
	int min = 32;
	int max = 126;
	int asciiChar = rand() % max + min;
	return asciiChar;
}



