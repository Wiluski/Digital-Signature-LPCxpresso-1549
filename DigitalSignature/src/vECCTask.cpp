/*
 * vECCTask.cpp
 *
 *  Created on: Feb 20, 2020
 *      Author: Ville Vainio
 */


#include "vECCTask.h"

extern QueueHandle_t eccQueue;
//extern EventGroupHandle_t xEventGroup;
extern Fmutex guardECC;
Fmutex debugECC;

extern SemaphoreHandle_t binaryECC;
//extern DigitalIoPin sw1, sw2, sw3;

//#define main_FIRST_BIT (1UL << 0UL);



void vECCTask(void *pvParameters){


	//static context / structs to handle ecdsa and password
	passSpecifications eccReceive;
	//mbedtls_ecdsa_context sign_ecc/*, verify*/;
	//mbedtls_entropy_context entropy_ecc;
	//mbedtls_ctr_drbg_context ctr_ecc;

	//use ticks to record the values and time it takes for the ECC encryption
	TickType_t currentTickCount;
	TickType_t currentTickCountECC;


	unsigned char sig[512];
	size_t sig_len;
	const char *persEcc = "ecdsa";

	while(1){

		vTaskDelay(100);
		//receive password struct
		xQueueReceive(eccQueue, (void*) &eccReceive, portMAX_DELAY);


		//guard the ecc task with a mutex
		//guardECC.lock();

		//get the beginning tick count
		currentTickCount = xTaskGetTickCountFromISR();

		//create a password from password class with a struct
		char *tmpPass = new char[sizeof(eccReceive.pass) + 1];
		char *tmpSalt = new char[sizeof(eccReceive.salt) + 1];

		strncpy(tmpPass, eccReceive.pass, sizeof(eccReceive.pass) + 1);
		strncpy(tmpSalt, eccReceive.salt, sizeof(eccReceive.salt) + 1);

		Password *rec_ecc = new Password(tmpPass, tmpSalt);


		//delete the temperature values of pass and salt
		delete[] tmpPass;
		delete[] tmpSalt;

		//use the hashing function to save the hash to digest
		rec_ecc->hash256();

		/*initialize all the required structures for ecc
		 * and run the functions for ecc signature*/
	   /* mbedtls_ecdsa_init( &sign_ecc );

	    mbedtls_ctr_drbg_init( &ctr_ecc );

	    mbedtls_entropy_init( &entropy_ecc );

	    mbedtls_ctr_drbg_seed( &ctr_ecc, mbedtls_entropy_func, &entropy_ecc,
	                                   (const unsigned char *) persEcc,
	                                   strlen( persEcc ) );


	   switch(eccReceive.value){
	    case 1:
		    mbedtls_ecdsa_genkey( &sign_ecc, ECPARAMS1, mbedtls_ctr_drbg_random,
		    		&ctr_ecc );
		    break;
	    case 2:
		    mbedtls_ecdsa_genkey( &sign_ecc, ECPARAMS2, mbedtls_ctr_drbg_random,
		    		&ctr_ecc );
	    	break;
	    case 3:
		    mbedtls_ecdsa_genkey( &sign_ecc, ECPARAMS3, mbedtls_ctr_drbg_random,
		    		&ctr_ecc );
		    break;
	    case 4:
		    mbedtls_ecdsa_genkey( &sign_ecc, ECPARAMS4, mbedtls_ctr_drbg_random,
		    		&ctr_ecc );
		    break;
	    case 5:
		    mbedtls_ecdsa_genkey( &sign_ecc, ECPARAMS5, mbedtls_ctr_drbg_random,
		    		&ctr_ecc );
		    break;
	    }



	    mbedtls_ecdsa_write_signature( &sign_ecc, MBEDTLS_MD_SHA256,rec_ecc->digestTest(),
	    		sizeof( rec_ecc->digestTest() ),sig,
				&sig_len, mbedtls_ctr_drbg_random, &ctr_ecc );


	    mbedtls_ecdsa_read_signature( &sign_ecc, rec_ecc->digestTest(),
	    		sizeof( rec_ecc->digestTest() ), sig, sig_len );*/

	    delete rec_ecc;

	 /*   mbedtls_ecdsa_free( &sign_ecc );
	    mbedtls_ctr_drbg_free( &ctr_ecc );
	    mbedtls_entropy_free( &entropy_ecc );*/

	    //take the time of the ecc signature
		currentTickCountECC = xTaskGetTickCountFromISR() - currentTickCount;


		//guard the debugging of the time it took for ecc signature
		debugECC.lock();
		DEBUGOUT("Ticks from last ECC signature: %lu\r\n", currentTickCountECC);
		debugECC.unlock();

		//guardECC.unlock();

		//release the task
		xSemaphoreGive(binaryECC);


	   // xEventGroupSetBits(xEventGroup, MAIN_THIRD_BIT);
	}

}



