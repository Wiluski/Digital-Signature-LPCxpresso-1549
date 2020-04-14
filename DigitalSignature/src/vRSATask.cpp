/*
 * vRSATask.cpp
 *
 *  Created on: Feb 20, 2020
 *      Author: Ville Vainio
 */


#include "vRSATask.h"


extern QueueHandle_t rsaQueue;
extern EventGroupHandle_t xEventGroup;
extern Fmutex guard;

void vRSATask(void *pvParameters){
	passSpecifications receiveRSA;
	mbedtls_rsa_context rsa;
	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr;

	unsigned char bufSign[512];
	unsigned char bufVerify[512];
	const char *pers = "rsa_generator";

	int ret = 0;

	while(1){
		xQueueReceive(rsaQueue, (void *) &receiveRSA, portMAX_DELAY);
		guard.lock();
		char *tmpPass = new char[sizeof(receiveRSA.pass) + 1];
		char *tmpSalt = new char[sizeof(receiveRSA.salt) + 1];

		strncpy(tmpPass, receiveRSA.pass, sizeof(receiveRSA.pass) + 1);
		strncpy(tmpSalt, receiveRSA.salt, sizeof(receiveRSA.salt) + 1);

		Password *rec = new Password(tmpPass, tmpSalt);
		if(rec == NULL)
			goto exit;

		delete[] tmpPass;
		delete[] tmpSalt;

		rec->hash256();

		mbedtls_ctr_drbg_init(&ctr);

		mbedtls_entropy_init(&entropy);

		if( (ret = mbedtls_ctr_drbg_seed(&ctr, mbedtls_entropy_func, &entropy,
				(const unsigned char*) pers, strlen(pers)) ) != 0)
			goto exit;



		mbedtls_rsa_init(&rsa, MBEDTLS_RSA_PKCS_V15, 0);

		if( ( ret = mbedtls_rsa_gen_key(&rsa, mbedtls_ctr_drbg_random,
				&ctr, 2048, 65537) ) != 0)
			goto exit;

//		rsa.len = ( mbedtls_mpi_bitlen( &rsa.N ) + 7 ) >> 3;

		if( ( ret = mbedtls_rsa_pkcs1_sign( &rsa, NULL, NULL, MBEDTLS_RSA_PRIVATE, MBEDTLS_MD_SHA256,
			                                20, rec->digestTest(), bufSign ) ) != 0)
			goto exit;

		if( ( ret = mbedtls_rsa_pkcs1_verify( &rsa, NULL, NULL, MBEDTLS_RSA_PUBLIC, MBEDTLS_MD_SHA256,
											20, bufSign, bufVerify ) ) != 0)
			goto exit;

		delete rec;
	    mbedtls_rsa_free(&rsa);
	    mbedtls_ctr_drbg_free(&ctr);
	    mbedtls_entropy_free(&entropy);

	    ret = 0;


		exit:
		while(1);

		guard.unlock();

		xEventGroupSetBits(xEventGroup, MAIN_FIRST_BIT);

	}
}



