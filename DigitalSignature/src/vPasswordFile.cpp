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
	passSpecifications s;


	while(1){

		if(init == false){
			for(int j = 0; j < 6; j++){
				//passSpecifications s;
				for(int i = 0; i < 5; i++){
					s.salt[i] = randomCharacter();
					}
				for(int i = 0; i < 8; i++){
					s.pass[i] = randomCharacter();
				}
				xQueueSendToFront(rsaQueue, (void*) &s, portMAX_DELAY);
			}
			init = true;
		}

	}
}

char randomCharacter(){
	int min = 32;
	int max = 126;
	int asciiChar = rand() % max + min;
	return asciiChar;
}

/*void salt(){
	passSpecifications s;
	char saltT[5];
	for(int i = 0; i < 5; i++){
		s.salt[i] = randomCharacter();
		}
}

void pass(){
	char passT[8];
	for(int i = 0; i < 8; i++){
		passT[i] = randomCharacter();
	}

}*/

/*Password initialize(){
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

	//delete[] pass;
	//delete[] salt;
	return init;
}*/

