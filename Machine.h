#ifndef MACHINE_H
#define MACHINE_H

#include <cstdint>
#include <iostream>

class Machine{
public:
	
	uint8_t shiftValue;
	uint8_t shiftm = 0, shiftb = 0;
	uint8_t input1 = 0x08;

	uint8_t in(uint8_t pin,bool* failed);
	void out(uint8_t pin, uint8_t a, bool* failed);

};

#endif