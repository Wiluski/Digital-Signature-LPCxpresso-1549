/*
 * vECCTask.cpp
 *
 *  Created on: Feb 20, 2020
 *      Author: Ville Vainio
 */


#include "vECCTask.h"

extern QueueHandle_t eccQueue;
extern EventGroupHandle_t xEventGroup;
extern Fmutex guard;

//#define main_FIRST_BIT (1UL << 0UL);

void vECCTask(void *pvParameters){
	//Password test1("asdasd", "124jf");
	//test1.hash256();
	//int ret;
	passSpecifications eccReceive;
	mbedtls_ecdsa_context sign_ecc/*, verify*/;
	mbedtls_entropy_context entropy_ecc;
	mbedtls_ctr_drbg_context ctr_ecc;

	//unsigned char hash[] = test1.digestTest();
	unsigned char sig[512];
	size_t sig_len;
	const char *pers = "ecdsa";

	while(1){
		xQueueReceive(eccQueue, (void*) &eccReceive, portMAX_DELAY);

		guard.lock();

		char *tmpPass = new char[sizeof(eccReceive.pass) + 1];
		char *tmpSalt = new char[sizeof(eccReceive.salt) + 1];

		strncpy(tmpPass, eccReceive.pass, sizeof(eccReceive.pass) + 1);
		strncpy(tmpSalt, eccReceive.salt, sizeof(eccReceive.salt) + 1);

		Password *rec_ecc = new Password(tmpPass, tmpSalt);

		if(rec_ecc == NULL)
			goto exit;

		delete[] tmpPass;
		delete[] tmpSalt;

		rec_ecc->hash256();

		//guardECC.lock();
	    mbedtls_ecdsa_init( &sign_ecc );
	    //mbedtls_ecdsa_init( &verify );
	    mbedtls_ctr_drbg_init( &ctr_ecc );
	    mbedtls_entropy_init( &entropy_ecc );


	    mbedtls_ctr_drbg_seed( &ctr_ecc, mbedtls_entropy_func, &entropy_ecc,
	                                   (const unsigned char *) pers,
	                                   strlen( pers ) );

	    mbedtls_ecdsa_genkey( &sign_ecc, ECPARAMS,
	                                  mbedtls_ctr_drbg_random, &ctr_ecc );

	    mbedtls_ecdsa_write_signature( &sign_ecc, MBEDTLS_MD_SHA256,rec_ecc->digestTest(),
	    		sizeof( rec_ecc->digestTest() ),sig,
				&sig_len, mbedtls_ctr_drbg_random, &ctr_ecc );

	    /*mbedtls_ecp_group_copy( &verify.grp, &sign.grp );
	    mbedtls_ecp_copy( &verify.Q, &sign.Q );*/

	    mbedtls_ecdsa_read_signature( &sign_ecc, rec_ecc->digestTest(),
	    		sizeof( rec_ecc->digestTest() ), sig, sig_len );
	   // mbedtls_ecdsa_free( &verify );

	    delete rec_ecc;

	    mbedtls_ecdsa_free( &sign_ecc );
	    mbedtls_ctr_drbg_free( &ctr_ecc );
	    mbedtls_entropy_free( &entropy_ecc );

	    exit:
		while(1);

	    guard.unlock();

	   // xEventGroupSetBits(xEventGroup, MAIN_SECOND_BIT);
	}

}



