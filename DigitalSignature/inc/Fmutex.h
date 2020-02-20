/*
 * Fmutex.h
 *
 *  Created on: Sep 2, 2019
 *      Author: Ville Vainio
 */
#include "semphr.h"

#ifndef FMUTEX_H_
#define FMUTEX_H_

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
