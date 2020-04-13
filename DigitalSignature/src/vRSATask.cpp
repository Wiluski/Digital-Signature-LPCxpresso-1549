/*
 * vRSATask.cpp
 *
 *  Created on: Feb 20, 2020
 *      Author: Ville Vainio
 */


#include "vRSATask.h"


extern QueueHandle_t rsaQueue;
extern EventGroupHandle_t xEventGroup;
Fmutex guardRSA;

void vRSATask(void *pvParameters){
	passSpecifications receive;
	mbedtls_rsa_context rsa;
	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr;
	unsigned char res[1024];
	unsigned char buf[512];
	const char *pers = "rsa_generator";
	/*Password* test1 = new Password("hello world!", "6asfh4");
	test1->hash256();
	unsigned char res[1024];
	unsigned char buf[512];
	const char *pers = "rsa_generator";


	mbedtls_rsa_context rsa;
	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr;

	mbedtls_ctr_drbg_init(&ctr);

	mbedtls_entropy_init(&entropy);

	mbedtls_ctr_drbg_seed(&ctr, mbedtls_entropy_func, &entropy, (const unsigned char*) pers, strlen(pers));
	mbedtls_rsa_init(&rsa, MBEDTLS_RSA_PKCS_V15, 0);

	mbedtls_rsa_gen_key(&rsa, mbedtls_ctr_drbg_random, &ctr, 2048, 65537);

	rsa.len = ( mbedtls_mpi_bitlen( &rsa.N ) + 7 ) >> 3;

	mbedtls_rsa_pkcs1_encrypt(&rsa, mbedtls_ctr_drbg_random, &ctr, MBEDTLS_RSA_PUBLIC,
			sizeof(test1->digestTest()), test1->digestTest(), buf);


	mbedtls_rsa_pkcs1_decrypt( &rsa, mbedtls_ctr_drbg_random,
												  &ctr, MBEDTLS_RSA_PRIVATE, &rsa.len,
												  buf, res, 1024 );
	delete test1;
    mbedtls_rsa_free(&rsa);
    mbedtls_ctr_drbg_free(&ctr);
    mbedtls_entropy_free(&entropy);*/
	while(1){
		xQueueReceive(rsaQueue, (void *) &receive, portMAX_DELAY);
		char *tmpPass = new char[sizeof(receive.pass) + 1];
		char *tmpSalt = new char[sizeof(receive.salt) + 1];

		strncpy(tmpPass, receive.pass, sizeof(receive.pass) + 1);
		strncpy(tmpSalt, receive.salt, sizeof(receive.salt) + 1);

		Password *rec = new Password(tmpPass, tmpSalt);
		delete[] tmpPass;
		delete[] tmpSalt;

		/*rec->hash256();

		mbedtls_ctr_drbg_init(&ctr);

		mbedtls_entropy_init(&entropy);

		mbedtls_ctr_drbg_seed(&ctr, mbedtls_entropy_func, &entropy, (const unsigned char*) pers, strlen(pers));
		mbedtls_rsa_init(&rsa, MBEDTLS_RSA_PKCS_V15, 0);

		mbedtls_rsa_gen_key(&rsa, mbedtls_ctr_drbg_random, &ctr, 2048, 65537);

		rsa.len = ( mbedtls_mpi_bitlen( &rsa.N ) + 7 ) >> 3;

		mbedtls_rsa_pkcs1_encrypt(&rsa, mbedtls_ctr_drbg_random, &ctr, MBEDTLS_RSA_PUBLIC,
				sizeof(rec->digestTest()), rec->digestTest(), buf);


		mbedtls_rsa_pkcs1_decrypt( &rsa, mbedtls_ctr_drbg_random,
													  &ctr, MBEDTLS_RSA_PRIVATE, &rsa.len,
													  buf, res, 1024 );*/

		delete rec;
	   /* mbedtls_rsa_free(&rsa);
	    mbedtls_ctr_drbg_free(&ctr);
	    mbedtls_entropy_free(&entropy);*/
	}
}



