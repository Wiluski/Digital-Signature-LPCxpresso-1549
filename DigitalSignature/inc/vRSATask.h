/*
 * vRSATask.h
 *
 *  Created on: Feb 20, 2020
 *      Author: Ville Vainio
 */

#ifndef VRSATASK_H_
#define VRSATASK_H_



#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif



#if defined(MBEDTLS_BIGNUM_C) && defined(MBEDTLS_ENTROPY_C) && \
    defined(MBEDTLS_RSA_C) && defined(MBEDTLS_GENPRIME) && \
    defined(MBEDTLS_FS_IO) && defined(MBEDTLS_CTR_DRBG_C)
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/bignum.h"
#include "mbedtls/x509.h"
#include "mbedtls/rsa.h"

#endif

/*#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif*/

#include "Fmutex.h"
#include "DigitalIoPin.h"
#include "Password.h"
#include "board_api.h"




void vRSATask(void *pvParameters);


#endif /* VRSATASK_H_ */
