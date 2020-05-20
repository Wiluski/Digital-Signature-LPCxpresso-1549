/*
 * DigitalIoPin.h
 *
 *  Created on: Aug 26, 2019
 *      Author: Ville Vainio
 */

#ifndef DIGITALIOPIN_H_
#define DIGITALIOPIN_H_

class DigitalIoPin {
public:
enum pinMode {
	output,
	input,
	pullup,
	pulldown
};
DigitalIoPin(int port, int pin, pinMode mode, bool invert = false);
virtual ~DigitalIoPin();
virtual bool read();
void write(bool value);

private:
int port;
int pin;
};




#endif /* DIGITALIOPIN_H_ */
