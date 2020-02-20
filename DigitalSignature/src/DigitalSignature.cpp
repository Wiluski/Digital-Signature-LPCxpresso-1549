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
#include "timers.h"
#include "Fmutex.h"
#include "vRSATask.h"
#include "vWatchDog.h"
#include "vECCTask.h"

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



int main(void) {

	//initialize the set up hardware
	prvSetupHardware();
	//initialize digital input pins
	//sw1 = new DigitalIoPin(0,17, DigitalIoPin::pullup, true);
	//sw2 = new DigitalIoPin(1,11, DigitalIoPin::pullup, true);
	//sw3 = new DigitalIoPin(1, 9, DigitalIoPin::pullup, true);

	xTaskCreate(vRSATask, "RSATask",
			configMINIMAL_STACK_SIZE*2, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);
	xTaskCreate(vECCTask, "ECCTask",
			configMINIMAL_STACK_SIZE*2, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);
	xTaskCreate(vWatchDog, "WatchDog",
			configMINIMAL_STACK_SIZE*2, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);

	/* Start the scheduler */
	    vTaskStartScheduler();

	//never arrive here
	return 1;

}
