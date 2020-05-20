/*
 * Fmutex.cpp
 *
 *  Created on: Apr 9, 2020
 *      Author: Ville Vainio
 */

#include "Fmutex.h"


Fmutex::Fmutex(){
	fMutex = xSemaphoreCreateMutex();
}

Fmutex::~Fmutex(){

}

void Fmutex::lock(){
	xSemaphoreTake(fMutex, portMAX_DELAY);
}

void Fmutex::unlock(){
	xSemaphoreGive(fMutex);
}

