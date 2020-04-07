/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>
#include "FreeRTOS.h"
#include "Password.h"
#include "task.h"
#include "vRSATask.h"
#include "vWatchDog.h"
#include "vECCTask.h"
#include "ITM_write.h"

//using namespace std;


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

#define SALT_SIZE 5
#define PASSWORD_SIZE 8


// TODO: insert other include files here

//DigitalIoPin *sw1, *sw2, *sw3;
//TimerHandle_t xAutoReloadTimerRsa = NULL, xAutoReloadTimerEcc = NULL;

static void prvSetupHardware(void)
{
    SystemCoreClockUpdate();
    Board_Init();

    /* Initial LED0 state is off */
    Board_LED_Set(0, false);
    Board_LED_Set(1, false);
    Board_LED_Set(2, false);

}


extern "C" {

void vConfigureTimerForRunTimeStats( void ) {
    Chip_SCT_Init(LPC_SCTSMALL1);
    LPC_SCTSMALL1->CONFIG = SCT_CONFIG_32BIT_COUNTER;
    LPC_SCTSMALL1->CTRL_U = SCT_CTRL_PRE_L(255) | SCT_CTRL_CLRCTR_L; // set prescaler to 256 (255 + 1), and start timer
}

}


void vTestTask(void *pvParameters){
	Password* test1 = new Password("hello world!", "6asfh4");
	test1->hash256();
	Board_UARTPutSTR((char*)test1->digestTest());
	Board_UARTPutChar('\n');
	Board_UARTPutChar('\r');
	Board_UARTPutSTR("ok!\n\r");

	int ret = 0;
	FILE *pub = NULL;
	FILE *priv = NULL;
	mbedtls_rsa_context rsa;
	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr;

	mbedtls_ctr_drbg_init(&ctr);

	mbedtls_entropy_init(&entropy);




	delete[] test1;
	while(1){

	}
}


int main(void) {

	//initialize the set up hardware
	prvSetupHardware();


	xTaskCreate(vTestTask, "TestTask",
			configMINIMAL_STACK_SIZE *4, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);

	/*xTaskCreate(vRSATask, "RSATask",
			configMINIMAL_STACK_SIZE*2, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);
	xTaskCreate(vECCTask, "ECCTask",
			configMINIMAL_STACK_SIZE*2, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);
	xTaskCreate(vWatchDog, "WatchDog",
			configMINIMAL_STACK_SIZE*2, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);
	xTaskCreate(vPasswordFile, "PasswordFile",
			configMINIMAL_STACK_SIZE *2, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);*/
	/* Start the scheduler */
	    vTaskStartScheduler();

	//never arrive here
	return 1;

}
