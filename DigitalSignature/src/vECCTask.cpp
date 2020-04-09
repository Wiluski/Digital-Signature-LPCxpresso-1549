/*
 * vECCTask.cpp
 *
 *  Created on: Feb 20, 2020
 *      Author: Ville Vainio
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "Fmutex.h"
#include "DigitalIoPin.h"
#include "event_groups.h"
#include "vECCTask.h"

extern QueueHandle_t eccQueue;
Fmutex guardECC;
//#define main_FIRST_BIT (1UL << 0UL);

void vECCTask(void *pvParameters){
	//Password test1("asdasd", "124jf");
	//test1.hash256();
	//int ret;
	Password eccReceive;
	mbedtls_ecdsa_context sign/*, verify*/;
	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr;

	//unsigned char hash[] = test1.digestTest();
	unsigned char sig[512];
	size_t sig_len;
	const char *pers = "ecdsa";

	while(1){
		xQueueReceive(eccQueue, (void*) &eccReceive, portMAX_DELAY);

		guardECC.lock();
	    mbedtls_ecdsa_init( &sign );
	    //mbedtls_ecdsa_init( &verify );
	    mbedtls_ctr_drbg_init( &ctr );
	    mbedtls_entropy_init( &entropy );


	    mbedtls_ctr_drbg_seed( &ctr, mbedtls_entropy_func, &entropy,
	                                   (const unsigned char *) pers,
	                                   strlen( pers ) );

	    mbedtls_ecdsa_genkey( &sign, ECPARAMS,
	                                  mbedtls_ctr_drbg_random, &ctr );

	    mbedtls_ecdsa_write_signature( &sign, MBEDTLS_MD_SHA256,eccReceive.digestTest(),
	    		sizeof( eccReceive.digestTest() ),sig,
				&sig_len, mbedtls_ctr_drbg_random, &ctr );

	    /*mbedtls_ecp_group_copy( &verify.grp, &sign.grp );
	    mbedtls_ecp_copy( &verify.Q, &sign.Q );*/

	    mbedtls_ecdsa_read_signature( &sign, eccReceive.digestTest(),
	    		sizeof( eccReceive.digestTest() ), sig, sig_len );
	   // mbedtls_ecdsa_free( &verify );
	    mbedtls_ecdsa_free( &sign );
	    mbedtls_ctr_drbg_free( &ctr );
	    mbedtls_entropy_free( &entropy );
	    guardECC.unlock();
	}

}



