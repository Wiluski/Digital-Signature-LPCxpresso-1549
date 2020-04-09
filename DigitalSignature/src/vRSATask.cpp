/*
 * vRSATask.cpp
 *
 *  Created on: Feb 20, 2020
 *      Author: Ville Vainio
 */


#include "vRSATask.h"


extern QueueHandle_t passwordQueue;
Fmutex guard;

void vRSATask(void *pvParameters){
	Password receive;
	const char *pers = "rsa_generator";
    unsigned char buf[512];
    unsigned char res[1024];
	mbedtls_rsa_context rsa;
	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr;

	while(1){
		xQueueReceive(passwordQueue, (void*) &receive, portMAX_DELAY);
		guard.lock();

		receive.hash256();

		mbedtls_ctr_drbg_init(&ctr);

		mbedtls_entropy_init(&entropy);

		mbedtls_ctr_drbg_seed(&ctr, mbedtls_entropy_func, &entropy, (const unsigned char*) pers, strlen(pers));

		mbedtls_rsa_init(&rsa, MBEDTLS_RSA_PKCS_V15, 0);

		mbedtls_rsa_gen_key(&rsa, mbedtls_ctr_drbg_random, &ctr, 2048, 65537);

		rsa.len = ( mbedtls_mpi_bitlen( &rsa.N ) + 7 ) >> 3;

		mbedtls_rsa_pkcs1_encrypt(&rsa, mbedtls_ctr_drbg_random, &ctr, MBEDTLS_RSA_PUBLIC,
				sizeof(receive.digestTest()), receive.digestTest(), buf);


		mbedtls_rsa_pkcs1_decrypt( &rsa, mbedtls_ctr_drbg_random,
			                                          &ctr, MBEDTLS_RSA_PRIVATE, &rsa.len,
			                                          buf, res, 1024 );
		guard.unlock();

	    mbedtls_rsa_free(&rsa);
	    mbedtls_ctr_drbg_free(&ctr);
	    mbedtls_entropy_free(&entropy);

	}
}


