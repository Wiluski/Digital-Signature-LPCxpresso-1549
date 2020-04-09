/*
 * Fmutex.h
 *
 *  Created on: Sep 2, 2019
 *      Author: Ville Vainio
 */

#ifndef FMUTEX_H_
#define FMUTEX_H_

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

class Fmutex{
public:
	Fmutex();
	virtual ~Fmutex();
	void lock();
	void unlock();
private:
	SemaphoreHandle_t fMutex;
};

#endif /* FMUTEX_H_ */
