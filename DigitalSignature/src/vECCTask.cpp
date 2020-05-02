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
Fmutex choosingMutex;
extern SemaphoreHandle_t binaryECC;
//extern DigitalIoPin sw1, sw2, sw3;

/*bool breakCase(){

	return true;
}
//#define main_FIRST_BIT (1UL << 0UL);
int choose(){
	int count = 0;
	int cases = 1;

	choosingMutex.lock();
	while(!sw1.read()){
		switch(cases){

		case 1:
			DEBUGOUT("choose elliptic curve\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1*\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			break;
		case 2:
			DEBUGOUT("choose elliptic curve\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1*\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			break;
		case 3:
			DEBUGOUT("choose elliptic curve\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1*\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			break;
		case 4:
			DEBUGOUT("choose elliptic curve\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1*\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			break;
		case 5:
			DEBUGOUT("choose elliptic curve\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1\r\n");
			DEBUGOUT("MBEDTLS_ECP_DP_SECP224R1*\r\n");
			break;
		}
		while(!sw2.read() || !sw3.read()){
			if(sw2.read()){
				while(sw2.read());
				if(cases == 5){
					cases = 1;
				}else{
					cases++;
				}
			}
			if(sw3.read()){
				while(sw2.read());
				if(cases <= 1){
					cases = 5;
				}else{
					cases--;
				}
			}
	}
}
	choosingMutex.unlock();
	count = cases;
	return count;
}*/

void vECCTask(void *pvParameters){
	//Password test1("asdasd", "124jf");
	//test1.hash256();
	//int ret;
	passSpecifications eccReceive;
	mbedtls_ecdsa_context sign_ecc/*, verify*/;
	mbedtls_entropy_context entropy_ecc;
	mbedtls_ctr_drbg_context ctr_ecc;

	TickType_t currentTickCount;
	TickType_t currentTickCountECC;

	//unsigned char hash[] = test1.digestTest();
	unsigned char sig[512];
	size_t sig_len;
	const char *persEcc = "ecdsa";
	int count = 0;

	while(1){

		xQueueReceive(eccQueue, (void*) &eccReceive, portMAX_DELAY);

		guardECC.lock();

		//count = choose();

		currentTickCount = xTaskGetTickCountFromISR();

		char *tmpPass = new char[sizeof(eccReceive.pass) + 1];
		char *tmpSalt = new char[sizeof(eccReceive.salt) + 1];

		strncpy(tmpPass, eccReceive.pass, sizeof(eccReceive.pass) + 1);
		strncpy(tmpSalt, eccReceive.salt, sizeof(eccReceive.salt) + 1);

		Password *rec_ecc = new Password(tmpPass, tmpSalt);


		delete[] tmpPass;
		delete[] tmpSalt;

		rec_ecc->hash256();

	    mbedtls_ecdsa_init( &sign_ecc );

	    mbedtls_ctr_drbg_init( &ctr_ecc );

	    mbedtls_entropy_init( &entropy_ecc );

	    mbedtls_ctr_drbg_seed( &ctr_ecc, mbedtls_entropy_func, &entropy_ecc,
	                                   (const unsigned char *) persEcc,
	                                   strlen( persEcc ) );

	    mbedtls_ecdsa_genkey( &sign_ecc, ECPARAMS1, mbedtls_ctr_drbg_random,
	    		&ctr_ecc );

	    /*switch(count){
	    case 1:
	    	mbedtls_ecdsa_genkey( &sign_ecc, ECPARAMS1,
	    		                                  mbedtls_ctr_drbg_random, &ctr_ecc );
	    	break;
	    case 2:
	    	mbedtls_ecdsa_genkey( &sign_ecc, ECPARAMS2,
	    		                                  mbedtls_ctr_drbg_random, &ctr_ecc );
	    	break;
	    case 3:
	    	mbedtls_ecdsa_genkey( &sign_ecc, ECPARAMS3,
	    		                                  mbedtls_ctr_drbg_random, &ctr_ecc );
	    	break;
	    case 4:
	    	mbedtls_ecdsa_genkey( &sign_ecc, ECPARAMS4,
	    		                                  mbedtls_ctr_drbg_random, &ctr_ecc );
	    	break;
	    case 5:
	    	mbedtls_ecdsa_genkey( &sign_ecc, ECPARAMS5,
	    		                                  mbedtls_ctr_drbg_random, &ctr_ecc );
	    	break;
	    }*/


	    mbedtls_ecdsa_write_signature( &sign_ecc, MBEDTLS_MD_SHA256,rec_ecc->digestTest(),
	    		sizeof( rec_ecc->digestTest() ),sig,
				&sig_len, mbedtls_ctr_drbg_random, &ctr_ecc );


	    mbedtls_ecdsa_read_signature( &sign_ecc, rec_ecc->digestTest(),
	    		sizeof( rec_ecc->digestTest() ), sig, sig_len );

	    delete rec_ecc;

	    mbedtls_ecdsa_free( &sign_ecc );
	    mbedtls_ctr_drbg_free( &ctr_ecc );
	    mbedtls_entropy_free( &entropy_ecc );

		currentTickCountECC = xTaskGetTickCountFromISR() - currentTickCount;


		debugECC.lock();
		DEBUGOUT("Ticks from last ECC signature: %lu\r\n", currentTickCountECC);
		debugECC.unlock();

		guardECC.unlock();

		xSemaphoreGive(binaryECC);
	    //exit:
		//while(1);

	   // xEventGroupSetBits(xEventGroup, MAIN_THIRD_BIT);
	}

}



