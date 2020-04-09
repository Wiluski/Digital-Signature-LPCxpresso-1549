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
#include "semphr.h"
#include <cstdlib>
#include "queue.h"
#include "Password.h"


void vPasswordFile(void *pvParameters);
char randomCharacter();
Password initialize();

#endif /* VPASSWORDFILE_H_ */
