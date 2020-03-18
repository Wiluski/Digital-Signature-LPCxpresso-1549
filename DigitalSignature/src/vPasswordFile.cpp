/*
 * vPasswordFile.cpp
 *
 *  Created on: Feb 24, 2020
 *      Author: Ville Vainio
 */

#include "FreeRTOS.h"
#include "task.h"
//#include "cstdlib.h"
//#include "time.h
#include "queue.h"
#include "vPasswordFile.h"

QueueHandle_t passwordQueue;


/*char randomCharacter(){
	int min = 32;
	int max = 126;
	int asciiChar = rand() % 126 + 32;
	return asciiChar;
}

void password(){
	char password [8];
	for(int i = 0; i < 8; i++){
		password[i] = randomCharacter();
	}
}

void salt(){
	char salt [5];
	for(int i = 0; i < 5; i++){
		salt[i] = randomCharacter();
	}
}*/


void vPasswordFile(void *pvParameters){

	while(1){

	}
}


