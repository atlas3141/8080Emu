#ifndef CPU_8080_H
#define CPU_8080_H

#include <cstdint>
#include <iostream>
#include "Machine.h"

class CPU_8080{
public:
	unsigned int pc;
	unsigned int sp;
  unsigned int clock;

	uint8_t* memory;
 	uint8_t a,b,c,d,e,h,l;
  bool z,s,p,cy,ac;
  bool ie;

  Machine* machine;

  int level;	
  bool failed;

  CPU_8080(Machine* newM);
	void emulate();
 	void unknownOpCode();
  void setFlags(uint8_t answer);
  void interupt(int type);


};

#endif