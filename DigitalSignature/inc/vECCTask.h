/*
 * vECCTask.h
 *
 *  Created on: Feb 20, 2020
 *      Author: Ville Vainio
 */

#ifndef VECCTASK_H_
#define VECCTASK_H_

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#define mbedtls_printf     printf
#endif

#if defined(MBEDTLS_ECDSA_C) && \
    defined(MBEDTLS_ENTROPY_C) && defined(MBEDTLS_CTR_DRBG_C)
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/ecdsa.h"

#endif

/*
 * Uncomment to show key and signature details
 */
#define VERBOSE

/*
 * Uncomment to force use of a specific curve
 */
//different curves for ecc
#define ECPARAMS1   MBEDTLS_ECP_DP_SECP192R1
#define ECPARAMS2	MBEDTLS_ECP_DP_SECP224R1
#define ECPARAMS3	MBEDTLS_ECP_DP_SECP256R1
#define ECPARAMS4	MBEDTLS_ECP_DP_SECP384R1
#define ECPARAMS5	MBEDTLS_ECP_DP_SECP521R1

//#include "FreeRTOS.h"
//#include "task.h"
//#include "semphr.h"
#include "Fmutex.h"
#include "Password.h"
#include "board_api.h"
//#include "vWatchDog.h"

void vECCTask(void *pvParameters);



#endif /* VECCTASK_H_ */
