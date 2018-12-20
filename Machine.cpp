#include "Machine.h"

using namespace std;

void Machine::out(uint8_t pin, uint8_t a, bool* failed){

  switch(pin){
    
  case 0x02:
      shiftValue = a & 0X07;
      break;
  case 0x03:
    break;
  case 0x04:
      shiftb =shiftm;
      shiftm = a;
      break;
  case 0x05:
    break;
  case 0x06:
    break;
  default:
    cout << " Unknown register " << (int) pin << endl;
    (*failed) = true;
  }
}
uint8_t Machine::in(uint8_t pin,bool* failed){

  switch(pin){

  case 0x00 :
    return 0x0e;
    break;
  case 0x01 :
    return input1;
    break;
  case 0x02:
    return 0x08;
    break;
  case 3:
    {
      uint16_t v = (shiftm<<8) | shiftb;
      return ((v >> (8-shiftValue)) & 0xff);
    }
    break;
  default:
    cout << " Unknown register " << (int)pin << endl;
    (*failed) = true;
  }
}