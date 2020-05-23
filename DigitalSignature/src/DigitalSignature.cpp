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

#include "vPasswordFile.h"
#include "vRSATask.h"
//#include "vWatchDog.h"
#include "vECCTask.h"
#include "ITM_write.h"

//using namespace std;

//extern EventGroupHandle_t xEventGroup;
extern QueueHandle_t rsaQueue;
extern QueueHandle_t eccQueue;
#define QUEUE_SIZE (100)

// TODO: insert other include files here

//DigitalIoPin sw1, sw2, sw3;
//TimerHandle_t xAutoReloadTimerRsa = NULL, xAutoReloadTimerEcc = NULL;

static void prvSetupHardware(void)
{
    SystemCoreClockUpdate();
    Board_Init();

    DEBUGINIT();
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
	data read;

	while(1){
		//xQueueReceive(xQueue, (void*) &read, portMAX_DELAY);
		//DEBUGOUT("%lu \r\n", read.tickCount);
		//__WFI();
		counttohun();
		DEBUGOUT("%lu \r\n", xTaskGetTickCountFromISR());
	}
}*/


int main(void) {

	//initialize the set up hardware
	prvSetupHardware();

	//creating queues to send to the RSA and ECC tasks
	rsaQueue = xQueueCreate(10, sizeof(passSpecifications));
	eccQueue = xQueueCreate(10, sizeof(passSpecifications));

	//xEventGroup = xEventGroupCreate();


	/*xTaskCreate(vTestTask, "TestTask",
			configMINIMAL_STACK_SIZE *2, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);*/

	//creating task to handle the password file as an class due to microcontroller
	//limitations
	xTaskCreate(vPasswordFile, "PasswordFile",
			configMINIMAL_STACK_SIZE * 2, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);

	//task to handle rsa encryption and decryption verification
	xTaskCreate(vRSATask, "RSATask",
			configMINIMAL_STACK_SIZE*4, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);

	//task to handle ECC encryption and verification
	xTaskCreate(vECCTask, "ECCTask",
			configMINIMAL_STACK_SIZE*4, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);

	//task to be handled to record the time of the encryptions and verifications
	/*xTaskCreate(vWatchDog, "WatchDog",
			configMINIMAL_STACK_SIZE*2, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);*/

	DEBUGOUT("TASKS RUNNING\r\n");
	/* Start the scheduler */
	vQueueAddToRegistry(rsaQueue, "rsaQueue");
	vQueueAddToRegistry(eccQueue, "eccQueue");
	//vTaskDelay(100);

	    vTaskStartScheduler();

	//never arrive here
	return 1;

}
