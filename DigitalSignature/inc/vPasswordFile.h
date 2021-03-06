/*
 * vPasswordFile.h
 *
 *  Created on: Feb 24, 2020
 *      Author: Ville Vainio
 */

#ifndef VPASSWORDFILE_H_
#define VPASSWORDFILE_H_


#include "FreeRTOS.h"
#include "task.h"
#include <cstdlib>
#include "queue.h"
#include "Password.h"
#include "Fmutex.h"
#include "DigitalIoPin.h"



void vPasswordFile(void *pvParameters);
char randomCharacter();
void menu(int in);

#endif /* VPASSWORDFILE_H_ */
