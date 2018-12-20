#include "CPU_8080.h"
#include <iostream>

using namespace std;

CPU_8080::CPU_8080(Machine* newM){
	machine = newM;
	failed = false;
	ie = false;
}

void CPU_8080::interupt(int type){
	if(ie){
	   
	  level++;
      memory[sp-1] = (pc >> 8) & 0xff;
      memory[sp-2] = pc & 0xff;
      sp -= 2;
      pc = type;
  	}
}

void CPU_8080::emulate(){
  uint8_t* opCode = &(memory[pc]);

  pc++;

  switch(*opCode){
    
  case 0x00:                  //NOP
  	clock = 4;
    break;  
    
  case 0x01: //LXI B
    
    b = opCode[2];
    c = opCode[1];
    pc += 2;
    clock = 10;

    break;
  case 0x02: 
    break;
  case 0x03: //INX B
  	c++;
  	if (c == 0x00)
      b++;
 	clock = 5;	
    break;
  case 0x04: //INR B
  	b ++;
  	setFlags(b);
  	clock = 5;
    break;
  case 0x05:                   //DCR B
    b--;
    setFlags(b);
    clock = 5;
    break;
  case 0x06:                   //MVI B,D8
    b = opCode[1];
    pc++;
    clock = 7;
    break;
  case 0x07: //RLC
    {
      bool bit8 = (0x80 == (a & 0x80));
      a = a<<1;
      a = (a & 0xfe) | bit8;
      cy = bit8;
      clock = 4;
    }
    break;
  case 0x08: unknownOpCode();
    break;
  case 0x09: //DAD B
    {
      unsigned int initial = (h << 8) | l;
      unsigned int toAdd = (b << 8) | c;
      unsigned int answer = initial + toAdd;
      cy = (answer & 0xffff0000 > 0);
      h = (answer >> 8) & 0xff;
      l = answer & 0xff;
      clock = 10;
    }
    break;
  case 0x0a: //LDAX B
  	a = memory[(b<<8) | c];
  	clock = 7;
    break;
  case 0x0b: unknownOpCode();
    break;
  case 0x0c: //INR C
  	c++;
  	setFlags(c);
  	clock = 5;
    break;
  case 0x0d: //DCR C;
    c --;
    setFlags(c);
	clock = 5;    
    break;
  case 0x0e:                  //MVI C
    c = opCode[1];
    pc++;
    clock = 7;
    break;
  case 0x0f: //RRC
    {
      bool bit0 = a%2;
      a = a>>1;
      a = a | (bit0 << 7);
      cy = bit0;
      clock = 4;
    }
    break;
  case 0x10: unknownOpCode();
    break;
  case 0x11:                   //LXI D
    d = opCode[2];
    e = opCode[1];
    pc += 2;
   	clock = 10;
    break;
    
  case 0x12:  //STAX D
    memory[(d << 8) | e] = a;
    clock = 7;
    break;
  case 0x13:                   //INX D
    e++;
    if (e == 0x00)
      d++;
  	clock = 5;
    break;
  case 0x14: //INR D
  	d++;
  	setFlags(d);
  	clock = 5;
    break;
  case 0x15: //DCR D
    d --;
    setFlags(d);
    clock = 5;
    break;
  case 0x16: //MVI D D8
  	d = opCode[1];
  	pc++;
  	clock = 7;
    break;
  case 0x17: unknownOpCode();
    break;
  case 0x18: unknownOpCode();
    break;
  case 0x19: //DAD D
    {
      unsigned int initial = (h << 8) | l;
      unsigned int toAdd = (d << 8) | e;
      unsigned int answer = initial + toAdd;
      cy = (answer & 0xff00) > 0;
      h = (answer >> 8) & 0xff;
      l = answer & 0xff;
      clock = 10;
    }
    break;
  case 0x1a:                   //LDAX D
    a = memory[(d << 8) | e];
    clock = 7;
    break;
  case 0x1b: //DCX D
  	e--;
  	if (e == 0xff) d--;
    clock = 5;
    break;
  case 0x1c: unknownOpCode();
    break;
  case 0x1d: unknownOpCode();
    break;
  case 0x1e: unknownOpCode();
    break;
  case 0x1f: //RAR
  	{
  		uint8_t old = a;
  		a = a >> 1;
  		a = (a & 0x7f) | (cy << 7);
  		cy = (0x01 == (old & 0x01));
  		clock = 4;
  	}
    break;
  case 0x20: unknownOpCode();
    break;
  case 0x21:                   //LXI H
    h = opCode[2];
    l = opCode[1];
    pc += 2;
   	clock = 10;
    break;

  case 0x22: //SHLD
  	{
  	  	uint16_t adr = (opCode[2] << 8) | opCode[1];
  	  	memory[adr] = l;
  	  	memory[adr+1] = h;
  	  	pc += 2;
  	  	clock = 16;
  	}
    break;
  case 0x23:                   //INX H
    l++;
    if (l == 0x00)
      h++;
    clock =5;
    break;
    
  case 0x24: //INR
  	h++;
  	setFlags(a);
  	clock = 5;
    break;
  case 0x25: unknownOpCode();
    break;
  case 0x26: //MVI H D8
    h = opCode[1];
    clock = 7;
    pc++;
    break;
  case 0x27:  //DAA
  	clock =4;
  	if((a & 0x0f) > 0x09 || ac){
  		a+=6;
  		ac = 1;
  	}
  	if((a & 0xf0) > 0x90){
  		uint16_t ans = a + 0x60;
  		a = ans & 0xff;
  		setFlags(a);
  		cy = 1;
  	}
    break;
  case 0x28: unknownOpCode();
    break;
  case 0x29: //DAD H
    {
      unsigned int answer = (h << 8) | l;
      answer += answer;
      cy = (answer > 0xff00);
      h = (answer >> 8) & 0xff;
      l = answer & 0xff;
      clock = 10;
    }
    break;
  case 0x2a: //LHLD
  	{
  		uint16_t offset = (opCode[2] << 8) | opCode[1];
  		l = memory[offset];
  		h = memory[offset+1];
  		pc += 2;
  		clock = 16;
  	}	
    break;
  case 0x2b: //DCX H
  	l--;
  	if (l == 0xff) h--;
   	clock = 5;
    break;
  case 0x2c: //INR L
  	l++;
  	setFlags(l);
  	clock = 5;
    break;
  case 0x2d: unknownOpCode();
    break;
  case 0x2e: //MVI L D8
  	l = opCode[1]; 
  	pc++;
  	clock =7;
  	break;
  case 0x2f: //CMA
  	a = ~a;
  	clock =4;
    break;
  case 0x30: unknownOpCode();
    break;
  case 0x31:                  //LXI SP
    sp = (opCode[2] << 8) | opCode[1];
    pc += 2; 
    clock =10; 
    break;
  case 0x32: //STA adr
  	memory[(opCode[2]<<8) | opCode[1]] = a;
  	pc += 2;
  	clock = 13;
    break;
  case 0x33: unknownOpCode();
    break;
  case 0x34: //INR M;
    memory[(h << 8) | l]++;
    setFlags(memory[(h << 8) | l]);
    clock = 10;
    break;
  case 0x35: //DCR M
  	memory[(h << 8) | l]--;
  	setFlags(memory[(h << 8) | l]);
  	clock = 10;
    break;
  case 0x36:       //MOV M,D8
    memory[(h << 8) | l] = opCode[1];
    clock = 10;
    pc++;
    break;
  case 0x37: //STC
    cy = 1;
    clock =4;
    break;
  case 0x38: unknownOpCode();
    break;
  case 0x39: unknownOpCode();
    break;
  case 0x3a: //LDA adr;
    a = memory[(opCode[2] << 8) | opCode[1]];
    pc += 2;
    clock = 13;
    break;
  case 0x3b: unknownOpCode();
    break;
  case 0x3c: //INR A
  	a++;
  	setFlags(a);
  	clock =5;
    break;
  case 0x3d: //DCR A
  	a--;
  	setFlags(a);
  	clock =5;
    break;
  case 0x3e: //MVI A D8
  	a = opCode[1];
  	pc++;
  	clock = 7;
    break;
  case 0x3f: unknownOpCode();
    break;
  case 0x40: unknownOpCode();
    break;
  case 0x41: //MOV B C
  	b = c;
  	clock = 5;
    break;
  case 0x42: unknownOpCode();
    break;
  case 0x43: unknownOpCode();
    break;
  case 0x44: unknownOpCode();
    break;
  case 0x45: unknownOpCode();
    break;
  case 0x46: //MOV B M
  	b = memory[(h<<8) | l];
  	clock =7;
    break;
  case 0x47: //MOV B A
  	b = a;
  	clock = 5;
    break;
  case 0x48: //MOV C B
  	c = b;
  	clock = 5;
    break;
  case 0x49: unknownOpCode();
    break;
  case 0x4a: unknownOpCode();
    break;
  case 0x4b: unknownOpCode();
    break;
  case 0x4c: unknownOpCode();
    break;
  case 0x4d: unknownOpCode();
    break;
  case 0x4e: //MOV C M
  	c = memory[(h<<8) | l];
  	clock = 7;
    break;
  case 0x4f: //MOV C A
  	c = a;
  	clock = 5;
    break;
  case 0x50: unknownOpCode();
    break;
  case 0x51: unknownOpCode();
    break;
  case 0x52: unknownOpCode();
    break;
  case 0x53: unknownOpCode();
    break;
  case 0x54: unknownOpCode();
    break;
  case 0x55: unknownOpCode();
    break;
  case 0x56: // MOV D M
  	d = memory[(h << 8) | l];
  	clock = 7;
    break;
  case 0x57: //MOV D A
  	d = a;
  	clock = 5;
    break;
  case 0x58: unknownOpCode();
    break;
  case 0x59: unknownOpCode();
    break;
  case 0x5a: unknownOpCode();
    break;
  case 0x5b: unknownOpCode();
    break;
  case 0x5c: unknownOpCode();
    break;
  case 0x5d: unknownOpCode();
    break;
  case 0x5e: //MOV E M
  	e = memory[(h << 8) | l];
  	clock = 7;
    break;
  case 0x5f: //MOV E A
  	e = a;
  	clock = 5;
    break;
  case 0x60: unknownOpCode();
    break;
  case 0x61: //MOVE H C
  	h = c;
  	clock = 5;
    break;
  case 0x62: unknownOpCode();
    break;
  case 0x63: unknownOpCode();
    break;
  case 0x64: unknownOpCode();
    break;
  case 0x65: //MOVE H l
  	h = l;
  	clock = 5;
    break;
  case 0x66: // MOV H M
  	h = memory[(h << 8) | l];
  	clock = 7;
    break;
  case 0x67: //MOVE H A
  	h = a;
  	clock = 5;
    break;
  case 0x68: //MOV L B
    l = b;
    clock = 5;
    break;
  case 0x69: //MOV L C
    l = c;
    clock = 5;
    break;
  case 0x6a: unknownOpCode();
    break;
  case 0x6b: unknownOpCode();
    break;
  case 0x6c: unknownOpCode();
    break;
  case 0x6d: unknownOpCode();
    break;
  case 0x6e: unknownOpCode();
    break;
  case 0x6f: //MOV L A
    l = a;
    clock = 5;
    break;
  case 0x70: //MOV M B
  	 if (((h<<8) | l ) < 0x4001 && ((h<<8) | l ) >= 2000){
  	memory[(h << 8) | l] = b;
  }
  	clock = 7;
    break;
  case 0x71: //MOV M C
   	if (((h<<8) | l )< 0x4001 && ((h<<8) | l ) >= 2000){
  	memory[(h << 8) | l] = c;
    }
	clock = 7;    
    break;
  case 0x72: unknownOpCode();
    break;
  case 0x73: unknownOpCode();
    break;
  case 0x74: unknownOpCode();
    break;
  case 0x75: unknownOpCode();
    break;
  case 0x76: unknownOpCode();
    break;
  case 0x77:                   //MOV M,A
    if (((h<<8) | l ) < 0x4001 && ((h<<8) | l ) >= 2000){
    memory[(h << 8) | l] = a;
	}
	clock = 7;
    break;
  case 0x78: //MOV A B
   	a = b;
   	clock = 5;
    break;
  case 0x79: //MOV A C
    a = c;
    clock = 5;
    break;
  case 0x7a: //MOV A D
  	a = d;
  	clock = 5;
    break;
  case 0x7b: //MOV A E
  	a = e;
  	clock = 5;
    break;
  case 0x7c:             //MOV A,H
    a = h;
    clock = 5;
    break;
  case 0x7d: //MOV A L
    a = l;
    clock = 5;
    break;
  case 0x7e: //MOV A M
    a = memory[(h << 8) | l];
  	clock = 7;
    break;
  case 0x7f: unknownOpCode();
    break;
  case 0x80: //ADD B
  	{
  	uint16_t ans = a+b;
  	cy = (ans > 0xff);
  	a = ans & 0xff;
  	setFlags(b);
  	clock = 4;
    }
    break;
  case 0x81: //ADD C
  	{
  	uint16_t ans = a+c;
  	cy = (ans > 0xff);
  	a = ans & 0xff;
  	setFlags(a);
  	clock = 4;
    }
    break;
  case 0x82: unknownOpCode();
    break;
  case 0x83: //ADD E
    {
  	uint16_t ans = a+e;
  	cy = (ans > 0xff);
  	a = ans & 0xff;
  	setFlags(a);
  	clock = 4;
    }
    break;
  case 0x84: unknownOpCode();
    break;
  case 0x85: //ADD L
  	{
  	uint16_t ans = a+l;
  	cy = (ans > 0xff);
  	a = ans & 0xff;
  	setFlags(a);
  	clock = 4;
    }
    break;
  case 0x86: //ADD M
  	{
  	uint16_t ans = a+memory[(h << 8) | l];
  	cy = (ans > 0xff);
  	a = ans & 0xff;
  	setFlags(a);
  	clock = 7;
    }
    break;
  case 0x87: unknownOpCode();
    break;
  case 0x88: unknownOpCode();
    break;
  case 0x89: unknownOpCode();
    break;
  case 0x8a: //ADC D
  	{
  	uint16_t ans = d+a+cy;
  	cy = (ans > 0xff);
  	a = ans & 0xff;
  	setFlags(a);
  	clock = 4;
    }
    break;
  case 0x8b: unknownOpCode();
    break;
  case 0x8c: unknownOpCode();
    break;
  case 0x8d: unknownOpCode();
    break;
  case 0x8e: unknownOpCode();
    break;
  case 0x8f: unknownOpCode();
    break;
  case 0x90: unknownOpCode();
    break;
  case 0x91: unknownOpCode();
    break;
  case 0x92: unknownOpCode();
    break;
  case 0x93: unknownOpCode();
    break;
  case 0x94: unknownOpCode();
    break;
  case 0x95: unknownOpCode();
    break;
  case 0x96: unknownOpCode();
    break;
  case 0x97: //SUB A
     {
      unsigned int ans = a - a;
	  setFlags(ans & 0xff);
	  cy = (a < a);     
      a = ans;
      clock = 4;
    }
    break;
  case 0x98: unknownOpCode();
    break;
  case 0x99: unknownOpCode();
    break;
  case 0x9a: unknownOpCode();
    break;
  case 0x9b: unknownOpCode();
    break;
  case 0x9c: unknownOpCode();
    break;
  case 0x9d: unknownOpCode();
    break;
  case 0x9e: unknownOpCode();
    break;
  case 0x9f: unknownOpCode();
    break;
  case 0xa0://ANA B
  	a = a&b;
  	setFlags(a);
  	cy = 0;
    clock = 4;
    break;
  case 0xa1: unknownOpCode();
    break;
  case 0xa2: unknownOpCode();
    break;
  case 0xa3: unknownOpCode();
    break;
  case 0xa4: unknownOpCode();
    break;
  case 0xa5: unknownOpCode();
    break;
  case 0xa6: //ANA M
  	{
  	uint8_t temp = memory[(h << 8) | l];
  	a= a & memory[(h << 8) | l];
  	setFlags(a);
  	cy = 0;
    clock = 4;
    }
    break;
  case 0xa7: //ANA A
  	setFlags(a);
  	cy = 0;
    clock = 4;
    break;
  case 0xa8: //XRA B
	a = a^b;
  	setFlags(a);
  	cy = 0;
    clock = 4;
    break;
  case 0xa9: unknownOpCode();
    break;
  case 0xaa: unknownOpCode();
    break;
  case 0xab: unknownOpCode();
    break;
  case 0xac: unknownOpCode();
    break;
  case 0xad: unknownOpCode();
    break;
  case 0xae: unknownOpCode();
    break;
  case 0xaf: //XRA A
  	a = 0;
  	setFlags(a);
  	cy = 0;
    clock =4;
    break;
  case 0xb0: //ORA B
  	a = a | b;
  	setFlags(a);
  	cy = 0;
  	clock = 4;
    break;
  case 0xb1: unknownOpCode();
    break;
  case 0xb2: unknownOpCode();
  	break;
  case 0xb3: unknownOpCode();
    break;
  case 0xb4: //ORA H
	a = a | h;
  	setFlags(a);
  	cy = 0;
  	clock = 4;
    break;
  case 0xb5: unknownOpCode();
    break;
  case 0xb6: //ORA M
  	a = a | memory[(h<<8) | l];
  	setFlags(a);
  	cy = 0;
  	clock = 7;
    break;
  case 0xb7: unknownOpCode();
    break;
  case 0xb8: //CMP B;
    {
      uint16_t answer =a-b; 
      setFlags(answer);
      s = (a < b);
      cy = (a < b);
     clock = 4;
    }
    break;
  case 0xb9: unknownOpCode();
    break;
  case 0xba: unknownOpCode();
    break;
  case 0xbb: unknownOpCode();
    break;
  case 0xbc: //CMP H;
    {
      uint16_t answer =a-h; 
      setFlags(answer);
      s = (a < h);
      cy = (a < h);
     clock =4;
    }
    break;
  case 0xbd: unknownOpCode();
    break;
  case 0xbe: //CMP H;
    {
   	  uint8_t temp = memory[(h<<8) | l];
      uint16_t answer =a-temp; 
      setFlags(answer);
      s = (a < temp);
      cy = (a < temp);
      clock = 7;
    }
    break;
  case 0xbf: unknownOpCode();
    break;
  case 0xc0: //RNZ
   	if(!z){
	pc = (memory[sp+1] << 8) |memory[sp];
	sp += 2;
	clock = 11;
	level--;
    }
   	else{
   		clock = 5;
   	}
    break;
  case 0xc1: //POP B
    b = memory[sp+1];
    c = memory[sp];
    sp += 2;
    clock = 10;
    break;
  case 0xc2:   //JNZ
  	clock = 10;
    if(z){
      pc+=2;
    }
    else{
      pc = (opCode[2] << 8) | opCode[1];
    }
    break;
  case 0xc3: //JMP
    pc = (opCode[2] << 8) | opCode[1];
   clock = 10;
    break;
  case 0xc4: //CNZ
   	if(!z){
      	uint16_t ret = pc+2;
      	memory[sp-1] = (ret >> 8) & 0xff;
   		memory[sp-2] = ret & 0xff;
      	sp -= 2;
      	pc = (opCode[2] << 8) | opCode[1];
     	clock = 11;
    	level++;
    }
    else{
    	pc+=2;
    	clock = 17;
    }
    break;
  case 0xc5: //PUSH B
    memory[sp-1] = b;
    memory[sp-2] = c;
    sp -= 2;
 	clock = 11;
    break;
  case 0xc6: //ADI
  {
  	uint16_t answer = a + opCode[1];
  	pc++;
  	cy = (answer > 0xff);
  	a = answer & 0xff;
  	setFlags(a);
  	clock = 7;
  }	
    break;
  case 0xc7: unknownOpCode();
    break;
  case 0xc8: //RZ
   	if(z){
   		pc = (memory[sp+1] << 8) |memory[sp];
    	sp += 2;
    	clock = 11;
    	level--;
    }
   	else{
   		clock = 5;
   	}
    break;
  case 0xc9: //RT
    pc = (memory[sp+1] << 8) |memory[sp];
    sp += 2;
    clock =10;
    level--;
    break;
  case 0xca: //JZ
  	if(!z){
      pc+=2;
     clock = 7;
    }
    else{
      pc = (opCode[2] << 8) | opCode[1];
      clock = 10;
    }
    break;
  case 0xcb: unknownOpCode();
    break;
  case 0xcc: //CZ
  	if(z){
      	uint16_t ret = pc+2;
      	memory[sp-1] = (ret >> 8) & 0xff;
   		memory[sp-2] = ret & 0xff;
      	sp -= 2;
      	pc = (opCode[2] << 8) | opCode[1];
     	clock = 17;
    	level++;
    }
    else{
    	pc+=2;
    	clock = 11;
    }
    break;
  case 0xcd: //CALL
    {
      uint16_t ret = pc+2;
      memory[sp-1] = (ret >> 8) & 0xff;
      memory[sp-2] = ret & 0xff;
      sp -= 2;
      pc = (opCode[2] << 8) | opCode[1];
      clock = 17;
      level++;
    }
    break;
  case 0xce: unknownOpCode();
    break;
  case 0xcf: unknownOpCode();
    break;
  case 0xd0: //RNC 
   	if(!cy){
   		pc = (memory[sp+1] << 8) |memory[sp];
    	sp += 2;
    	clock = 11;
    	level--;
    }
   	else{
   		 clock = 5;
   	}
    break;
  case 0xd1: //POP D
    d = memory[sp+1];
    e = memory[sp];
    sp += 2;
    clock =10;
    break;
  case 0xd2: //JNC
  	clock = 10;
  	if(cy){
      pc+=2;
    }
    else{
      pc = (opCode[2] << 8) | opCode[1];
    }
    break;
  case 0xd3: //OUT
    machine->out(opCode[1],a,&failed);
    pc++;
    clock = 10;
    break;
  case 0xd4: //CNC
  	if(!cy){
      	uint16_t ret = pc+2;
      	memory[sp-1] = (ret >> 8) & 0xff;
   		memory[sp-2] = ret & 0xff;
      	sp -= 2;
      	pc = (opCode[2] << 8) | opCode[1];
      	clock = 17;
    	level++;
    }
    else{
    	pc+=2;
    	clock = 11;
    }
    break;
  case 0xd5: //PUSH D
    memory[sp-1] = d;
    memory[sp-2] = e;
    sp -= 2;
    clock = 11;
    break;
  case 0xd6: //SUI D8
  	cy = (opCode[1] > a);
  	a = a-opCode[1];
  	setFlags(a);
  	pc++;
  	clock = 7;
    break;
  case 0xd7: unknownOpCode();
    break;
  case 0xd8: //RC
  	if(cy){
   		pc = (memory[sp+1] << 8) |memory[sp];
    	sp += 2;
    	clock = 11;
    	level--;
    }
   	else{
   		clock = 5;
   	}
    break;
  case 0xd9: unknownOpCode();
    break;
  case 0xda: //JC
    clock = 10;
    if(cy){
      pc = (opCode[2] << 8) | opCode[1];
    }
    else{
      pc+=2;
    }
    break;
  case 0xdb: //IN
    clock = 10;
    a = machine->in(opCode[1],&failed);
    pc++;
    break;
  case 0xdc: unknownOpCode();
    break;
  case 0xdd: unknownOpCode();
    break;
  case 0xde: //SBI D8
  	{
  		uint16_t ans = a -opCode[1] - cy;
  		setFlags(a);
  		a = ans & 0xff;
  		cy = (ans > 0xff);
  		pc++;
  		clock = 7;
    }
    break;
  case 0xdf: unknownOpCode();
    break;
  case 0xe0: unknownOpCode();
    break;
  case 0xe1: //POP H
    h = memory[sp+1];
    l = memory[sp];
    sp += 2;
    clock = 10;
    break;
  case 0xe2: unknownOpCode();
    break;
  case 0xe3: //XTHL
  	swap(l,memory[sp]);
  	swap(h,memory[sp+1]);
  	clock = 18;
    break;
  case 0xe4: unknownOpCode();
    break;
  case 0xe5: //PUSH H
    memory[sp-1] = h;
    memory[sp-2] = l;
    sp -= 2;
    clock = 11;
    break;
  case 0xe6: //ANA D8
  	a = a & opCode[1];
  	pc++;
  	setFlags(a);
  	clock = 7;
    break;
  case 0xe7: unknownOpCode();
    break;
  case 0xe8: unknownOpCode();
    break;
  case 0xe9: //PCHL
  	pc = (h << 8) | l;
  	clock = 5;
    break;
  case 0xea: unknownOpCode();
    break;
  case 0xeb: //XCHG
    swap(h,d);
    swap(l,e);
    clock = 4;
    break;
  case 0xec: unknownOpCode();
    break;
  case 0xed: unknownOpCode();
    break;
  case 0xee: unknownOpCode();
    break;
  case 0xef: unknownOpCode();
    break;
  case 0xf0: unknownOpCode();
    break;
  case 0xf1: //POP PSW
	
	{    
    a = memory[sp+1];    
	uint8_t psw = memory[sp];    
    z  = (0x01 == (psw & 0x01));    
    s  = (0x02 == (psw & 0x02));    
    p  = (0x04 == (psw & 0x04));    
	cy = (0x08 == (psw & 0x08));    
	ac = (0x10 == (psw & 0x10));    
    sp += 2;    
   clock = 10;
    } 
    break;
  case 0xf2: unknownOpCode();
    break;
  case 0xf3: unknownOpCode();
    break;
  case 0xf4: unknownOpCode();
    break;
  case 0xf5: //PUSH PSW
  	{    
    memory[sp-1] = a;    
	uint8_t psw = (z |    
		s << 1 |    
    	p << 2 |    
        cy << 3 |    
        ac << 4 );    

    memory[sp-2] = psw;    
    sp = sp - 2;    
    clock = 11;
    }  
    break;
  case 0xf6: //ORI D8
 	a = a | opCode[1];
  	setFlags(a);
  	cy = 0;
  	pc++;
  	clock = 7;
    break;
  case 0xf7: unknownOpCode();
    break;
  case 0xf8: unknownOpCode();
    break;
  case 0xf9: unknownOpCode();
    break;
  case 0xfa: //JM
   	clock = 10;
    if(!s){
      pc+=2;
    }
    else{
      pc = (opCode[2] << 8) | opCode[1];
    }
   	break;
  case 0xfb: //EI
  	ie = true;
  	clock = 4;
    break;
  case 0xfc: unknownOpCode();
    break;
  case 0xfd: unknownOpCode();
    break;
  case 0xfe: //CPI D8
    {
      uint16_t answer =a-opCode[1]; 
      setFlags(answer);
      s = (a < opCode[1]);
      cy = (a < opCode[1]);
      pc++;
      clock = 7;
    }
    break;
  case 0xff: unknownOpCode();
    break;
  }
}
void CPU_8080::unknownOpCode(){
  cout << "Unknown OpCode " << hex << (int) memory[pc-1] << endl;
  failed = true;
}

void CPU_8080::setFlags(uint8_t answer){

  z = (answer == 0);
  s = (answer & 0x80) == 0x80;
  unsigned int count = 1, k, b = 1;
  for(k = 0; k < 8; k++){
    if( answer & (b << k) ){count++;}
  }
  p = count%2;
  ac = 0;
}