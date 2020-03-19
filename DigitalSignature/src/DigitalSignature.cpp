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
#include <DigitalIoPin.h>
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "vRSATask.h"
#include "vWatchDog.h"
#include "vECCTask.h"
#include "ITM_write.h"
#include "fstream"

//using namespace std;


#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif
/*
#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdlib.h>
#include <stdio.h>
#define mbedtls_printf       printf
#define mbedtls_exit         exit
#define MBEDTLS_EXIT_SUCCESS EXIT_SUCCESS
#define MBEDTLS_EXIT_FAILURE EXIT_FAILURE
#endif

#if defined(MBEDTLS_MD5_C)
#include "mbedtls/md5.h"
#endif*/
#if DEBUG_LEVEL > 0
#include "mbedtls/debug.h"
#endif

#include "mbedtls/platform.h"
#include "mbedtls/sha256.h"
#include "mbedtls/md.h"
#include <cstdio>


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
static const char hello_str[] = "Hello, world!";
static const unsigned char *hello_buffer = (const unsigned char *) hello_str;
static const size_t hello_len = sizeof hello_str - 1;


void vTestTask(void *pvParameters){

	unsigned char digest[32];
	//int c;

	mbedtls_sha256_ret(hello_buffer, hello_len, digest, 0);

	//Board_UARTPutChar('\n');
	//Board_UARTPutChar('\r');
	for(size_t i = 0; i < sizeof digest; i++){
		//ITM_write("02%x", digest[i]);
		DEBUGOUT("02%x", digest[i]);
		//c = digest[i];
		//Board_UARTPutChar(c);
	}
	DEBUGOUT("\n\r");

	//Board_UARTPutChar('\n');
	//Board_UARTPutChar('\r');
	//Board_UARTPutSTR(hello_str);

	DEBUGOUT("OK \n\r");
	//ITM_write(digest);

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
