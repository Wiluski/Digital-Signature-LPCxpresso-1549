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
Fmutex debug;
SemaphoreHandle_t binaryECC;
SemaphoreHandle_t binaryRSA;


void menuRSAexp(int in){
	switch(in){
	case 1:
		debug.lock();
		DEBUGOUT("Choose exponent: \r\n");
		DEBUGOUT("3 <-- \r\n");
		DEBUGOUT("5 \r\n");
		DEBUGOUT("17 \r\n");
		DEBUGOUT("257 \r\n");
		DEBUGOUT("65537 \r\n");
		debug.unlock();
		break;
	case 2:
		debug.lock();
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("3 \r\n");
		DEBUGOUT("5 <-- \r\n");
		DEBUGOUT("17 \r\n");
		DEBUGOUT("257 \r\n");
		DEBUGOUT("65537 \r\n");
		debug.unlock();
		break;
	case 3:
		debug.lock();
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("3 \r\n");
		DEBUGOUT("5 \r\n");
		DEBUGOUT("17 <-- \r\n");
		DEBUGOUT("257 \r\n");
		DEBUGOUT("65537 \r\n");
		debug.unlock();
		break;
	case 4:
		debug.lock();
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("3 \r\n");
		DEBUGOUT("5 \r\n");
		DEBUGOUT("7 \r\n");
		DEBUGOUT("257 <-- \r\n");
		DEBUGOUT("65537 \r\n");
		debug.unlock();
		break;
	case 5:
		debug.lock();
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("3 \r\n");
		DEBUGOUT("5 \r\n");
		DEBUGOUT("17 \r\n");
		DEBUGOUT("257 \r\n");
		DEBUGOUT("65537 <-- \r\n");
		debug.unlock();
		break;
	}
}

void menuRSAbin(int in){
	switch(in){
	case 1:
		debug.lock();
		DEBUGOUT("Choose bits to use: \r\n");
		DEBUGOUT("128 <-- \r\n");
		DEBUGOUT("1024 \r\n");
		DEBUGOUT("2048 \r\n");
		DEBUGOUT("3072 \r\n");
		debug.unlock();
		break;
	case 2:
		debug.lock();
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("128 \r\n");
		DEBUGOUT("1024 <-- \r\n");
		DEBUGOUT("2048 \r\n");
		DEBUGOUT("3072 \r\n");
		debug.unlock();
		break;
	case 3:
		debug.lock();
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("128 \r\n");
		DEBUGOUT("1024 \r\n");
		DEBUGOUT("2048 <-- \r\n");
		DEBUGOUT("3072 \r\n");
		debug.unlock();
		break;
	case 4:
		debug.lock();
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("128 \r\n");
		DEBUGOUT("1024 \r\n");
		DEBUGOUT("2048 \r\n");
		DEBUGOUT("3072 <-- \r\n");
		debug.unlock();
		break;
	}
}

void menuECC(int in){
	switch(in){
	case 1:
		debug.lock();
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP192R1 <-- \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1 \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP256R1 \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP384R1 \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP521R1 \r\n");
		debug.unlock();
		break;
	case 2:
		debug.lock();
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP192R1 \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1 <-- \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP256R1 \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP384R1 \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP521R1 \r\n");
		debug.unlock();
		break;
	case 3:
		debug.lock();
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP192R1 \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1 \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP256R1 <-- \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP384R1 \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP521R1 \r\n");
		debug.unlock();
		break;
	case 4:
		debug.lock();
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP192R1 \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1 \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP256R1 \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP384R1 <-- \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP521R1 \r\n");
		debug.unlock();
		break;
	case 5:
		debug.lock();
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP192R1 \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1 \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP256R1 \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP384R1 \r\n");
		DEBUGOUT("MBEDTLS_ECP_DP_SECP521R1 <-- \r\n");
		debug.unlock();
		break;
	}
}

void menuWhich(int in){
	switch(in){
	case 1:
		debug.lock();
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("RSA <--\r\n");
		DEBUGOUT("ECC \r\n");
		debug.unlock();
		break;
	case 2:
		debug.lock();
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("RSA \r\n");
		DEBUGOUT("ECC <--\r\n");
		debug.unlock();
		break;
	}
}


void vPasswordFile(void *pvParameters){

	passSpecifications s;
	binaryECC = xSemaphoreCreateBinary();
	binaryRSA = xSemaphoreCreateBinary();

	DigitalIoPin sw1(0,17,DigitalIoPin::pullup, true);
	DigitalIoPin sw2(1,11,DigitalIoPin::pullup, true);
	DigitalIoPin sw3(1, 9,DigitalIoPin::pullup, true);


	int input;
	int choose;
	while(1){

		vTaskDelay(100);
		input = 1;

		for(int i = 0; i < 5; i++){
			s.salt[i] = randomCharacter();
			}
		for(int i = 0; i < 8; i++){
			s.pass[i] = randomCharacter();
			}

		while(1){

			debug.lock();
			DEBUGOUT("Choose encryption type: \r\n");
			DEBUGOUT("RSA <--\r\n");
			DEBUGOUT("ECC \r\n");
			debug.unlock();

			if(sw2.read()){
				while(sw2.read());
				//DEBUGOUT("OK 2");
				if(input == 2)
					input = 1;
				else{
					input++;
				}
				menuWhich(input);
			}
				if(sw3.read()){
					while(sw3.read());
					//DEBUGOUT("OK 3");
					if(input == 1)
						input = 2;
					else{
						input--;
					}
				menuWhich(input);
			}
			if(sw1.read()){
				while(sw1.read());
				choose = input;
				input = 1;
				break;
			}
		}

		if(choose == 1){
			debug.lock();
			DEBUGOUT("Choose exponent: \r\n");
			DEBUGOUT("3 <-- \r\n");
			DEBUGOUT("5 \r\n");
			DEBUGOUT("17 \r\n");
			DEBUGOUT("257 \r\n");
			DEBUGOUT("65537 \r\n");
			debug.unlock();

			while(1){
				if(sw2.read()){
					while(sw2.read());
						//DEBUGOUT("OK 2");
					if(input == 5)
						input = 1;
					else{
						input++;
						}
					menuRSAexp(input);
					}
					if(sw3.read()){
						while(sw3.read());
						//DEBUGOUT("OK 3");
						if(input == 1)
							input = 5;
						else{
							input--;
							}
						menuRSAexp(input);
						}
					if(sw1.read()){
						while(sw1.read());
						switch(input){
						case 1:
							s.exp = 3;
							break;
						case 2:
							s.exp = 5;
							break;
						case 3:
							s.exp = 17;
							break;
						case 4:
							s.exp = 257;
							break;
						case 5:
							s.exp = 65537;
							break;
						}
						s.exp = input;
						input = 1;
						break;
					}
			}
			while(1){

				debug.lock();
				DEBUGOUT("Choose bits to use: \r\n");
				DEBUGOUT("128 <-- \r\n");
				DEBUGOUT("1024 \r\n");
				DEBUGOUT("2048 \r\n");
				DEBUGOUT("3072 \r\n");
				debug.unlock();

				if(sw2.read()){
					while(sw2.read());
					//DEBUGOUT("OK 2");
					if(input == 4)
						input = 1;
					else{
						input++;
					}
					menuRSAbin(input);
				}
				if(sw3.read()){
					while(sw3.read());
					//DEBUGOUT("OK 3");
					if(input == 1)
						input = 4;
					else{
						input--;
					}
				menuRSAbin(input);
				}
				if(sw1.read()){
					while(sw1.read());
					switch(input){
					case 1:
						s.nbit = 128;
						break;
					case 2:
						s.nbit = 1024;
						break;
					case 3:
						s.nbit = 2048;
						break;
					case 4:
						s.nbit = 3072;
						break;
					}
					break;
				}
			}
			xQueueSendToFront(rsaQueue, (void*) &s, portMAX_DELAY);

			xSemaphoreTake(binaryRSA, portMAX_DELAY);
		}

		if(choose == 2){

			debug.lock();
			DEBUGOUT("Choose encryption type: \r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP192R1 <-- \r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1 \r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP256R1 \r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP384R1 \r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP521R1 \r\n");
			debug.unlock();

			while(1){
			if(sw2.read()){
				while(sw2.read());
				//DEBUGOUT("OK 2");
				if(input == 5)
					input = 1;
				else{
					input++;
					}
				menuECC(input);
				}
				if(sw3.read()){
					while(sw3.read());
					//DEBUGOUT("OK 3");
					if(input == 1)
						input = 5;
					else{
						input--;
					}
					menuECC(input);
					}
				if(sw1.read()){
					while(sw1.read());
					break;
				}

			}
			s.valueECC = input;

			/* send values of pass and salt to the ecc queue to be handled in ECC
			 * Task*/
			xQueueSendToFront(eccQueue, (void*) &s, portMAX_DELAY);

			//wait for the ecc task to run the encryption and verification
			xSemaphoreTake(binaryECC, portMAX_DELAY);
		}
	}
}

char randomCharacter(){
	int min = 32;
	int max = 126;
	int asciiChar = rand() % max + min;
	return asciiChar;
}



