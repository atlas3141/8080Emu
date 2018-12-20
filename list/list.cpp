#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdint>

using namespace std;

int main(){

  uint8_t x;
  unint8 pc;
  unsigned int pos = 0;
  unsigned int byte1, byte2;
  ifstream input("invaders.h", ios::binary);
  bool hasOP = true;

  input >> noskipws;
  while (input >> x && hasOP) {
    pc = x;
    cout << hex << setfill('0') << setw(4) << pos << " ";
    cout << hex << setfill('0') << setw(2) << pc << " ";
    cout << dec;
    switch(pc){

    case 0x00 :
      cout << "NOP" << endl;
      pos += 1;
      break;
    case 0x01 :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "LXI    B,#0x"<<hex<<setfill('0')<<setw(2) << byte1;
      cout << ",0x" << hex<<setfill('0')<<setw(2) << byte2 << endl;
      pos += 2;
      break;
    case 0x03 :
      cout << "INX    B" << endl;
      pos ++;
      break;
    case 0x04:
      cout << "INR    B" << endl;
      pos ++;
      break;
    case 0x05:
      cout << "DCR    B" << endl;
      pos ++;
      break;
    case 0x06 :
      input >> x;
      byte1 = x;
      cout << "MVI    B,#0x"<<hex<<setfill('0')<<setw(2) << byte1 << endl;
      pos += 2;
      break;
    case 0x07 :
      cout << "RLC" << endl;
      pos ++;
      break;
    case 0x08:
      cout << "-" << endl;
      pos ++;
      break;
    case 0x0d :
      cout << "DCR    C" << endl;
      pos ++;
      break;
    case 0x0e :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "MVI    C,#0x"<<hex<<setfill('0')<<setw(2) << byte1;
      cout << ",0x" << hex<<setfill('0')<<setw(2) << byte2 << endl;
      pos += 3;
      break;
    case 0x0f :
      cout << "RRC" << endl;
      pos ++;
      break;
    case 0x11 :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "LXI    D,#0x"<<hex<<setfill('0')<<setw(2) << byte2;
      cout << hex<<setfill('0')<<setw(2) << byte1 << endl;
      pos += 3;
      break;
    case 0x13  :
      cout << "INX    D" << endl;
      pos ++;
      break;
    case 0x14 :
      cout << "INR    D" << endl;
      pos ++;
      break;
    case 0x15 :
      cout << "DCR    D" << endl;
      pos ++;
      break;
    case 0x16 :
      input >> x;
      byte1 = x;
      cout << "MVI    D,#0x"<<hex<<setfill('0')<<setw(2) << byte1 << endl;
      pos += 2;
      break;
    case 0x19 :
      cout << "DAD    D" << endl;
      pos ++;
      break;
    case 0x1a :
      cout << "LDAX   D" << endl;
      pos ++;
      break;
    case 0x1d :
      cout << "DCR    E" << endl;
      pos ++;
      break;
    case 0x20 :
      cout << "RIM" << endl;
      pos ++;
      break;
    case 0x21 :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "LXI    H,#0x"<<hex<<setfill('0')<<setw(2) << byte2;
      cout << hex<<setfill('0')<<setw(2) << byte1 << endl;
      pos += 3;
      break;
    case 0x22 :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "SHLD   $"<<hex<<setfill('0')<< setw(2) << byte2;
      cout << hex<<setfill('0')<< setw(2) << byte1 << endl;
      pos += 3;
      break;
    case 0x23 :
      cout << "INX    H" << endl;
      pos ++;
      break;
    case 0x26 :
      input >> x;
      byte1 = x;
      cout << "MVI    H,#0x"<<hex<<setfill('0')<<setw(2) << byte1 << endl;
      pos += 2;
      break;
    case 0x27:
      cout << "DAA" << endl;
      pos ++;
      break;
    case 0x29:
      cout << "DAD    H" << endl;
      pos ++;
      break;
    case 0x2a :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "LHLD   $"<<hex<<setfill('0')<< setw(2) << byte2;
      cout << hex<<setfill('0')<< setw(2) << byte1 << endl;
      pos += 3;
      break;
    case 0x2b:
      cout << "DCX    H" << endl;
      pos ++;
      break;
    case 0x2c:
      cout << "INR    L" << endl;
      pos ++;
      break;
    case 0x2e:
      input >> x;
      byte1 = x;
      cout << "MVI    L,#0x"<<hex<<setfill('0')<<setw(2) << byte1 << endl;
      pos += 2;
      break;
    case 0x31 :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "LXI   0x"<<hex<<setfill('0')<< setw(2) << byte2;
      cout << hex<<setfill('0')<< setw(2) << byte1 << endl;
      pos += 3;
      break;
    case 0x32 :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "STA    $"<<hex<<setfill('0')<< setw(2) << byte2;
      cout << hex<<setfill('0')<< setw(2) << byte1 << endl;
      pos += 3;
      break;
    case 0x34:
      cout << "INR    M" << endl;
      pos ++;
      break;
    case 0x35:
      cout << "DCR    M" << endl;
      pos += 1;
      break;
    case 0x36 :
      input >> x;
      byte1 = x;
      cout << "MVI    M,#0x"<<hex<<setfill('0')<<setw(2) << byte1 << endl;
      pos += 2;
      break;
    case 0x37 :
      cout << "STC" << endl;
      pos++;
      break;
    case 0x3a :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "LDA    $"<<hex<<setfill('0')<< setw(2) << byte2;
      cout << hex<<setfill('0')<< setw(2) << byte1 << endl;
      pos += 3;
      break;
    case 0x3c:
      cout << "INR    A" << endl;
      pos ++;
      break;
    case 0x3d:
      cout << "DCR    A" << endl;
      pos ++;
      break;
    case 0x3e :
      input >> x;
      byte1 = x;
      cout << "MVI    A,#0x"<<hex<<setfill('0')<<setw(2) << byte1 << endl;
      pos += 2;
      break;
    case 0x46:
      cout << "MOV    B,M" << endl;
      pos ++;
      break;
    case 0x47:
      cout << "MOV    B,A" << endl;
      pos ++;
      break;
    case 0x4a:
      cout << "MOV    C,D" << endl;
      pos ++;
      break;
    case 0x4e:
      cout << "MOV    C,M" << endl;
      pos ++;
      break;
    case 0x4f :
      cout << "MOV    C,A" << endl;
      pos ++;
      break;
    case 0x50 :
      cout << "MOV    D,B" << endl;
      pos ++;
      break;
    case 0x56:
      cout << "MOV    D,M" << endl;
      pos ++;
      break;
    case 0x57:
      cout << "MOV    D,A" << endl;
      pos ++;
      break;
    case 0x5e:
      cout << "MOV    E,M" << endl;
      pos ++;
      break;
    case 0x5f :
      cout << "MOV    E,A" << endl;
      pos ++;
      break;
    case 0x61 :
      cout << "MOV    H,C" << endl;
      pos ++;
      break;
    case 0x66 :
      cout << "MOV    H,M" << endl;
      pos ++;
      break;
    case 0x67 :
      cout << "MOV    H,C" << endl;
      pos ++;
      break;
    case 0x68 :
      cout << "MOV    L,B" << endl;
      pos ++;
      break;
    case 0x69 :
      cout << "MOV    L,C" << endl;
      pos++;
      break;
    case 0x6f :
      cout << "MOV    L,A" << endl;
      pos ++;
      break;
    case 0x70 :
      cout << "MOV    M,B" << endl;
      pos ++;
      break;
    case 0x71 :
      cout << "MOV    M,C" << endl;
      pos ++;
      break;
    case 0x72 :
      cout << "MOV    M,D" << endl;
      pos ++;
      break;
    case 0x73 :
      cout << "MOV    M,E" << endl;
      pos ++;
      break;
    case 0x77 :
      cout << "MOV    M,A" << endl;
      pos ++;
      break;
    case 0x78 :
      cout << "MOV    A,B" << endl;
      pos ++;
      break;
    case 0x79 :
      cout << "MOV    A,C" << endl;
      pos ++;
      break;
    case 0x7a:
      cout << "MOV    A,D" << endl;
      pos ++;
      break;
    case 0x7b:
      cout << "MOV    A,E" << endl;
      pos ++;
      break;
    case 0x7c:
      cout << "MOV    A,H" << endl;
      pos ++;
      break;
    case 0x7d :
      cout << "MOV    A,L" << endl;
      pos ++;
      break;
    case 0x7e :
      cout << "MOV    A,M" << endl;
      pos ++;
      break;
    case 0x80 :
      cout << "ADA    B" << endl;
      pos++;
      break;
    case 0x85 :
      cout << "ADD    L" << endl;
      pos ++;
      break;
    case 0x86 :
      cout << "ADD    M" << endl;
      pos ++;
      break;
    case 0x90 :
      cout << "SUB    B" << endl;
      pos++;
      break;
    case 0x97 :
      cout << "SUB    A" << endl;
      pos++;
      break;
    case 0x9b :
      cout << "SBB    E" << endl;
      pos ++;
      break;
    case 0xa0 :
      cout << "ANA    B" << endl;
      pos++;
      break;
    case 0xa5 :
      cout << "ANA    L" << endl;
      pos++;
      break;
    case 0xa7 :
      cout << "ADA    A" << endl;
      pos++;
      break;
    case 0xaf:
      cout << "XRA    A" << endl;
      pos ++;
      break;
    case 0xb0 :
      cout << "ORA    B" << endl;
      pos ++;
      break;
    case 0xb4 :
      cout << "ORA    H" << endl;
      pos ++;
      break;
    case 0xb8 :
      cout << "CMP    B" << endl;
      pos ++;
      break;
    case 0xbe :
      cout << "CMP    M" << endl;
      pos ++;
      break;
    case 0xc0 :
      cout << "RNZ" << endl;
      pos ++;
      break;
    case 0xc1 :
      cout << "POP    B" << endl;
      pos ++;
      break;
    case 0xc2 :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "JNZ    $"<<hex<<setfill('0')<< setw(2) << byte2 << byte1 << endl;
      pos += 3;
      break;
    case 0xc3 :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "JMP    $"<<hex<<setfill('0')<< setw(2) << byte2;
      cout << hex<< setfill('0')<< setw(2) << byte1 << endl;
      pos += 3;
      break;
    case 0xc4 :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "CNZ    $"<<hex<<setfill('0')<< setw(2) << byte2;
      cout << hex<<setfill('0')<< setw(2) << byte1 << endl;
      pos += 3;
      break;
    case 0xc5:
      cout << "PUSH   B" << endl;
      pos ++;
      break;
    case 0xc6 :
      input >> x;
      byte1 = x;
      cout << "ADI    #0x"<<hex<<setfill('0')<<setw(2) << byte1 << endl;
      pos += 2;
      break;
    case 0xc8 :
      cout << "RZ" << endl;
      pos ++;
      break;
    case 0xc9:
      cout << "RET" << endl;
      pos++;
      break;
    case 0xcc :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "JZ     $"<<hex<<setfill('0')<< setw(2) << byte2 << byte1 << endl;
      pos += 3;
      break;
    case 0xca :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "CZ     $"<<hex<<setfill('0')<< setw(2) << byte2 << byte1 << endl;
      pos += 3;
      break;
    case 0xcd :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "CALL   $"<<hex<<setfill('0')<< setw(2) << byte2 << byte1 << endl;
      pos += 3;
      break;
    case 0xd0:
      cout << "RNC" << endl;
      pos ++;
      break;
    case 0xd1 :
      cout << "POP    D" << endl;
      pos ++;
      break;
    case 0xd2 :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "JNC    $"<<hex<<setfill('0')<< setw(2) << byte2 << byte1 << endl;
      pos += 3;
      break;
    case 0xd3 :
      input >> x;
      byte1 = x;
      cout << "OUT    #0x"<<hex<<setfill('0')<<setw(2) << byte1 << endl;
      pos += 2;
      break;
    case 0xd5:
      cout << "PUSH   D" << endl;
      pos ++;
      break;
    case 0xd6 :
      input >> x;
      byte1 = x;
      cout << "SUI    #0x"<<hex<<setfill('0')<<setw(2) << byte1 << endl;
      pos += 2;
      break;
    case 0xda :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "JC     $"<<hex<<setfill('0')<< setw(2) << byte2;
      cout << hex<<setfill('0')<< setw(2) << byte1 << endl;
      pos += 3;
      break;
    case 0xdb :
      input >> x;
      byte1 = x;
      cout << "IN     #0x"<<hex<<setfill('0')<<setw(2) << byte1 << endl;
      pos += 2;
      break;
    case 0xde:
      input >> x;
      byte1 = x;
      cout << "SBI    #0x"<<hex<<setfill('0')<<setw(2) << byte1 << endl;
      pos += 2;
      break;
    case 0xe1 :
      cout << "POP    H" << endl;
      pos ++;
      break;
    case 0xe3:
      cout << "XTHL" << endl;
      pos ++;
      break;
    case 0xe5:
      cout << "PUSH   H" << endl;
      pos ++;
      break;
    case 0xe6:
      input >> x;
      byte1 = x;
      cout << "ANI    #0x"<<hex<<setfill('0')<<setw(2) << byte1 << endl;
      pos += 2;
      break;
    case 0xe9:
      cout << "PCHL" << endl;
      pos ++;
      break;
    case 0xeb :
      cout << "XCHG" << endl;
      pos ++;
      break;
    case 0xf1 :
      cout << "POP    PSW" << endl;
      pos ++;
      break;
    case 0xf3:
      cout << "DI" << endl;
      pos ++;
      break;
    case 0xf5:
      cout << "PUSH   PSW" << endl;
      pos++;
      break;
    case 0xf6 :
      input >> x;
      byte1 = x;
      cout << "ORI    #0x"<<hex<<setfill('0')<<setw(2) << byte1 << endl;
      pos += 2;
      break;
    case 0xfa :
      input >> x;
      byte1 = x;
      input >> x;
      byte2 = x;
      cout << "JM     $"<<hex<<setfill('0')<< setw(2) << byte2;
      cout << hex<<setfill('0')<< setw(2) << byte1 << endl;
      pos += 3;
      break;
    case 0xfb :
      cout << "EI" << endl;
      pos++;
      break;
    case 0xfe :
      input >> x;
      byte1 = x;
      cout << "CPI    #0x"<<hex<<setfill('0')<<setw(2) << byte1 << endl;
      pos += 2;
      break;
    default :
      cout << endl;
      pos ++;
      hasOP = false;
      break;
    }
  }
}
