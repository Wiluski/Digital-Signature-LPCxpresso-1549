/*
 * vPasswordFile.cpp
 *
 *  Created on: Feb 24, 2020
 *      Author: Ville Vainio
 */

#include "vPasswordFile.h"

QueueHandle_t rsaQueue;
QueueHandle_t eccQueue;

char randomCharacter(){
	int min = 32;
	int max = 126;
	int asciiChar = rand() % max + min;
	return asciiChar;
}

Password initialize(){
	Password init;
	char pass[8];
	char salt[5];
	for(int i = 0; i < 8; i++){
		pass[i] = randomCharacter();
	}
	for(int i = 0; i < 5; i++){
		salt[i] = randomCharacter();
	}
	init = Password(pass,salt);

	return init;
}


void vPasswordFile(void *pvParameters){

	int size = 6;
	int i = 0;
	Password ps[size];

	while(1){
		if(i < size){
			ps[i] = initialize();
			xQueueSendToFront(rsaQueue, (void*) &ps[i], portMAX_DELAY);
			xQueueSendToFront(eccQueue, (void*) &ps[i], portMAX_DELAY);
			i++;
		}

	}
}


