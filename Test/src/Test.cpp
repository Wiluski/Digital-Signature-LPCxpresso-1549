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

#include "DigitalIoPin.h"
#include "Fmutex.h"

void menu(int in);

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



void vTestTask(void *pvParameters){

	int input = 1;
	DigitalIoPin sw1(0,17,DigitalIoPin::pullup, true);
	DigitalIoPin sw2(1,11,DigitalIoPin::pullup, true);
	DigitalIoPin sw3(1, 9,DigitalIoPin::pullup, true);

	DEBUGOUT("Choose encryption type: \r\n");
	DEBUGOUT("1 <-\r\n");
	DEBUGOUT("2 \r\n");
	DEBUGOUT("3 \r\n");
	DEBUGOUT("4 \r\n");
	DEBUGOUT("5 \r\n");

	while(1){

		do{
			if(sw2.read()){
				while(sw2.read());
				DEBUGOUT("OK 2");
				if(input == 5)
					input = 1;
				else{
					input++;
				}
				menu(input);
			}
			if(sw3.read()){
				while(sw3.read());
				DEBUGOUT("OK 3");
				if(input == 1)
					input = 5;
				else{
					input--;
				}
				menu(input);
			}

		}while(!sw1.read());



	}
}

void menu(int in){
	switch(in){
	case 1:
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("1 <-\r\n");
		DEBUGOUT("2 \r\n");
		DEBUGOUT("3 \r\n");
		DEBUGOUT("4 \r\n");
		DEBUGOUT("5 \r\n");
		break;
	case 2:
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("1 \r\n");
		DEBUGOUT("2 <-\r\n");
		DEBUGOUT("3 \r\n");
		DEBUGOUT("4 \r\n");
		DEBUGOUT("5 \r\n");
		break;
	case 3:
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("1 \r\n");
		DEBUGOUT("2 \r\n");
		DEBUGOUT("3 <-\r\n");
		DEBUGOUT("4 \r\n");
		DEBUGOUT("5 \r\n");
		break;
	case 4:
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("1 \r\n");
		DEBUGOUT("2 \r\n");
		DEBUGOUT("3 \r\n");
		DEBUGOUT("4 <-\r\n");
		DEBUGOUT("5 \r\n");
		break;
	case 5:
		DEBUGOUT("Choose encryption type: \r\n");
		DEBUGOUT("1 \r\n");
		DEBUGOUT("2 \r\n");
		DEBUGOUT("3 \r\n");
		DEBUGOUT("4 \r\n");
		DEBUGOUT("5 <-\r\n");
		break;
	}
}
int main(void) {

	//initialize the set up hardware
	prvSetupHardware();


	xTaskCreate(vTestTask, "TestTask",
			configMINIMAL_STACK_SIZE *2, NULL, (tskIDLE_PRIORITY +1UL),
			(TaskHandle_t *) NULL);


	DEBUGOUT("TASKS RUNNING\r\n");

	    vTaskStartScheduler();

	//never arrive here
	return 1;

}
