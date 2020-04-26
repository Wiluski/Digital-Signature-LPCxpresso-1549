/*
 * vPasswordFile.cpp
 *
 *  Created on: Feb 24, 2020
 *      Author: Ville Vainio
 */

#include "vPasswordFile.h"

QueueHandle_t rsaQueue;
QueueHandle_t eccQueue;
Fmutex guard;

void vPasswordFile(void *pvParameters){
	bool init = false;
	//passSpecifications s[6];



	while(1){

		if(init == false){
				sendOne();
				sendTen();
				sendHundred();

			}
			init = true;

	}
}

char randomCharacter(){
	int min = 32;
	int max = 126;
	int asciiChar = rand() % max + min;
	return asciiChar;
}

void sendOne(){
	passSpecifications s;

	TickType_t currentTickCountStart = 0;
	TickType_t currentTickCountECC = 0;
	TickType_t currentTickCountRSA = 0;

	for(int i = 0; i < 5; i++){
		s.salt[i] = randomCharacter();
		}
	for(int i = 0; i < 8; i++){
		s.pass[i] = randomCharacter();
	}

	xQueueSendToFront(rsaQueue, (void*) &s, portMAX_DELAY);

	currentTickCountRSA = currentTickCountStart - xTaskGetTickCount();

	currentTickCountStart = xTaskGetTickCount();

	guard.lock();
	Board_UARTPutSTR("Ticks for one RSA signature:");
	Board_UARTPutChar(currentTickCountRSA);
	Board_UARTPutChar('\n');
	Board_UARTPutChar('\r');
	guard.unlock();

	xQueueSendToFront(eccQueue, (void*) &s, portMAX_DELAY);
	currentTickCountECC = currentTickCountStart - xTaskGetTickCount();

	guard.lock();
	Board_UARTPutSTR("Ticks for one ECC signature:");
	Board_UARTPutChar(currentTickCountECC);
	Board_UARTPutChar('\n');
	Board_UARTPutChar('\r');
	guard.unlock();

}

void sendTen(){
	passSpecifications s;

	TickType_t currentTickCountStart = 0;
	TickType_t currentTickCountECC = 0;
	TickType_t currentTickCountRSA = 0;

	for(int j = 0; j < 10; j++){
		//passSpecifications s;
		for(int i = 0; i < 5; i++){
			s.salt[i] = randomCharacter();
			}
		for(int i = 0; i < 8; i++){
			s.pass[i] = randomCharacter();
		}
		//currentTickCount1 = xTaskGetTickCount();
		//currentTickCount2 = currentTickCount1 - currentTickCount2;
		currentTickCountStart = xTaskGetTickCount();

		xQueueSendToFront(rsaQueue, (void*) &s, portMAX_DELAY);

		currentTickCountRSA += xTaskGetTickCount() - currentTickCountStart;

		currentTickCountStart = xTaskGetTickCount();

		xQueueSendToFront(eccQueue, (void*) &s, portMAX_DELAY);
		currentTickCountECC += xTaskGetTickCount() - currentTickCountStart;

	}
	guard.lock();
	Board_UARTPutSTR("Ticks for 10 RSA signature:");
	Board_UARTPutChar(currentTickCountRSA);
	Board_UARTPutChar('\n');
	Board_UARTPutChar('\r');
	guard.unlock();

	guard.lock();
	Board_UARTPutSTR("Ticks for 10 ECC signature:");
	Board_UARTPutChar(currentTickCountECC);
	Board_UARTPutChar('\n');
	Board_UARTPutChar('\r');
	guard.unlock();
}

void sendHundred(){
	passSpecifications s;

	TickType_t currentTickCountStart = 0;
	TickType_t currentTickCountECC = 0;
	TickType_t currentTickCountRSA = 0;

	for(int j = 0; j < 100; j++){
		//passSpecifications s;
		for(int i = 0; i < 5; i++){
			s.salt[i] = randomCharacter();
			}
		for(int i = 0; i < 8; i++){
			s.pass[i] = randomCharacter();
		}
		//currentTickCount1 = xTaskGetTickCount();
		//currentTickCount2 = currentTickCount1 - currentTickCount2;
		currentTickCountStart = xTaskGetTickCount();

		xQueueSendToFront(rsaQueue, (void*) &s, portMAX_DELAY);

		currentTickCountRSA += xTaskGetTickCount() - currentTickCountStart;

		currentTickCountStart = xTaskGetTickCount();

		xQueueSendToFront(eccQueue, (void*) &s, portMAX_DELAY);
		currentTickCountECC += xTaskGetTickCount() - currentTickCountStart;

	}
	guard.lock();
	Board_UARTPutSTR("Ticks for 100 RSA signature:");
	Board_UARTPutChar(currentTickCountRSA);
	Board_UARTPutChar('\n');
	Board_UARTPutChar('\r');
	guard.unlock();

	guard.lock();
	Board_UARTPutSTR("Ticks for 100 ECC signature:");
	Board_UARTPutChar(currentTickCountECC);
	Board_UARTPutChar('\n');
	Board_UARTPutChar('\r');
	guard.unlock();
}



