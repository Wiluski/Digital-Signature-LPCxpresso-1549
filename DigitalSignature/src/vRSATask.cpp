/*
 * vRSATask.cpp
 *
 *  Created on: Feb 20, 2020
 *      Author: Ville Vainio
 */


#include "vRSATask.h"


extern QueueHandle_t rsaQueue;
//extern EventGroupHandle_t xEventGroup;
extern SemaphoreHandle_t binaryRSA;
extern Fmutex guardRSA;
//extern DigitalIoPin sw1, sw2, sw3;
Fmutex debugRSA;

void vRSATask(void *pvParameters){

	//due to limitations of the microcontroller the rsa functions don't work properly
	//need to be implemented in a later date, configurations don't allow file handling
	passSpecifications receiveRSA;
	//mbedtls_rsa_context rsa;
	//mbedtls_entropy_context entropy;
	//mbedtls_ctr_drbg_context ctr;

	TickType_t currentTickCount;
	TickType_t currentTickCountRSA;

	/*unsigned char bufSign[512];
	unsigned char bufVerify[512];
	const char *persRsa = "rsa";
	//bool done = false;
	int count = 0;*/

	while(1){
		xQueueReceive(rsaQueue, (void*) &receiveRSA, portMAX_DELAY);


		guardRSA.lock();

		currentTickCount = xTaskGetTickCount();


		char *tmpPass = new char[sizeof(receiveRSA.pass) + 1];
		char *tmpSalt = new char[sizeof(receiveRSA.salt) + 1];

		strncpy(tmpPass, receiveRSA.pass, sizeof(receiveRSA.pass) + 1);
		strncpy(tmpSalt, receiveRSA.salt, sizeof(receiveRSA.salt) + 1);

		Password *rec = new Password(tmpPass, tmpSalt);


		delete[] tmpPass;
		delete[] tmpSalt;

		rec->hash256();

	/*	mbedtls_ctr_drbg_init(&ctr);

		mbedtls_entropy_init(&entropy);

		mbedtls_rsa_init(&rsa, MBEDTLS_RSA_PKCS_V15, 0);

		mbedtls_ctr_drbg_seed(&ctr, mbedtls_entropy_func, &entropy,
						(const unsigned char*) persRsa, strlen(persRsa));


		mbedtls_rsa_gen_key(&rsa, mbedtls_ctr_drbg_random,
						&ctr, receiveRSA.nbit, receiveRSA.exp);


		mbedtls_rsa_pkcs1_sign( &rsa, NULL, NULL, MBEDTLS_RSA_PRIVATE, MBEDTLS_MD_SHA256,
					                                20, rec->digestTest(), bufSign );


		mbedtls_rsa_pkcs1_verify( &rsa, NULL, NULL, MBEDTLS_RSA_PUBLIC, MBEDTLS_MD_SHA256,
													20, bufSign, bufVerify );*/


		delete rec;
		//delete test;

	  /*  mbedtls_rsa_free(&rsa);

	    mbedtls_ctr_drbg_free(&ctr);

	    mbedtls_entropy_free(&entropy);*/


	   // ret = 0;
	    currentTickCountRSA = xTaskGetTickCount() - currentTickCount;


	    debugRSA.lock();
		DEBUGOUT("Ticks from last RSA signature: %lu \r\n", currentTickCountRSA);
		debugRSA.unlock();


	    guardRSA.unlock();

	    xSemaphoreGive(binaryRSA);
		//exit:
		//while(1);

		//guard.unlock();
		//xEventGroupSetBits(xEventGroup, MAIN_SECOND_BIT);

	}
}



