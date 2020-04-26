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
#include "task.h"
#include "semphr.h"
#include "Password.h"
#include "vPasswordFile.h"
#include "vRSATask.h"
#include "vWatchDog.h"
#include "vECCTask.h"
#include "ITM_write.h"

//using namespace std;

extern EventGroupHandle_t xEventGroup;
extern QueueHandle_t rsaQueue;
extern QueueHandle_t eccQueue;
#define QUEUE_SIZE (5)


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


/*void vTestTask(void *pvParameters){

	while(1){

	}
}*/


int main(void) {

	//initialize the set up hardware
	prvSetupHardware();

	rsaQueue = xQueueCreate(QUEUE_SIZE, sizeof(passSpecifications));
	eccQueue = xQueueCreate(QUEUE_SIZE, sizeof(passSpecifications));
	xEventGroup = xEventGroupCreate();
	//Board_UARTPutSTR(str)

	/*xTaskCreate(vTestTask, "TestTask",
			configMINIMAL_STACK_SIZE *2, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);*/
	xTaskCreate(vPasswordFile, "PasswordFile",
			configMINIMAL_STACK_SIZE * 4, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);
	xTaskCreate(vRSATask, "RSATask",
			configMINIMAL_STACK_SIZE*4, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);
	xTaskCreate(vECCTask, "ECCTask",
			configMINIMAL_STACK_SIZE*2, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);
	xTaskCreate(vWatchDog, "WatchDog",
			configMINIMAL_STACK_SIZE*2, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);
	/* Start the scheduler */
	vQueueAddToRegistry(rsaQueue, "rsaQueue");
	vQueueAddToRegistry(eccQueue, "eccQueue");
	    vTaskStartScheduler();

	//never arrive here
	return 1;

}
