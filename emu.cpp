#include <cstdint>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include "CPU_8080.h"
#include "Machine.h"
#include "SDL.h"

using namespace std;

void readIn(const char* fileName, int* readIndex, uint8_t* memory);

int main(){
  srand (time(NULL));

  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *window = NULL;
  window = SDL_CreateWindow ("Window",
           SDL_WINDOWPOS_UNDEFINED,
           SDL_WINDOWPOS_UNDEFINED,
           448, 512,
           SDL_WINDOW_RESIZABLE);
  if (window == NULL){
    cout << "Something Happened" << endl;
  }

  SDL_Surface *screen = SDL_GetWindowSurface(window);

  bool running = true;
  SDL_Event event;

  uint8_t* memory = new uint8_t[0x4000];
  Machine machine;
  CPU_8080 cpu(&machine);
  cpu.memory = memory;
  cpu.pc = 0;
  cpu.clock = 0;
  cpu.level = 0;
  
  //read in from the rom
  int readIndex = 0;
  readIn("invaders/invaders.h",&readIndex,memory);
  readIn("invaders/invaders.g",&readIndex,memory);
  readIn("invaders/invaders.f",&readIndex,memory);
  readIn("invaders/invaders.e",&readIndex,memory);
  for(int i = 0x2400; i < 0x4000; i++){
    memory[i] = 0xff;
  }
  Uint32 initTime = SDL_GetTicks();
  
  SDL_Rect pixel;
  pixel.x = 0;
  pixel.y = 0;
  pixel.h = 2;
  pixel.w = 2;

  Uint32 white = SDL_MapRGB(screen->format,255,255,255);
  
  Uint32 black = SDL_MapRGB(screen->format,0,0,0);

  Uint64 cycles = 0,totalCycles = 0;
  unsigned int lastFrame = SDL_GetTicks();
  bool coin=0,left=0,right=0,fire=0,start=0;
  bool lastInterupt = false;
  bool hasCycled = false;

  timespec current;
  timespec_get(&current,TIME_UTC);
  timespec lastTime = current;


  while(running){
    while (SDL_PollEvent(&event)){
      
      if (event.type == SDL_QUIT){
        running = false;
        cout << "Goodbye" << endl;
        break;
      }

      if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym){
          case SDLK_LEFT:
            left = true;
            break;
          case SDLK_RIGHT:
            right = true;
            break;
          case SDLK_c:
            coin = true;
            break;
          case SDLK_SPACE:
            fire = true;
            break;
          case SDLK_1:
            start = true;
            break;
           }
         }
         if(event.type == SDL_KEYUP){
          switch(event.key.keysym.sym){
           case SDLK_LEFT:
            left = false;
            break;
          case SDLK_RIGHT:
            right = false;
            break;
          case SDLK_c:
            coin = false;
            break;
          case SDLK_SPACE:
            fire = false;
            break;
          case SDLK_1:
            start = false;
            break;
          }
        }
        machine.input1 = (coin |
                           start << 2 |
                          0x01 << 3 |
                          fire << 4 |
                          left << 5 |
                          right << 6 );
        } 


        
      if(SDL_GetTicks() > lastFrame + 8){
      SDL_FillRect(screen,NULL,black);
      lastFrame = SDL_GetTicks();
      for (int i = 0x2400; i < 0x4000; i++){
        unsigned int k, b = 1;
       for(k = 0; k < 8; k++){      
          if(memory[i] & (b << k) ){
            pixel.y = 512-2*((8*((i-0x2400)%0x20))+k);
            pixel.x = 2*((i-0x2400)/0x20);

            SDL_FillRect(screen,&pixel,white);
          }
        }
      }

      SDL_UpdateWindowSurface(window);
    }

    hasCycled = false;

    if(SDL_GetTicks() > lastFrame + 3 && SDL_GetTicks() < lastFrame + 7 && !lastInterupt){
     cpu.interupt(0x10);
     lastInterupt = true;
     hasCycled = true;

    }

    if(SDL_GetTicks() > lastFrame + 7 && lastInterupt && !hasCycled){
     cpu.interupt(0x08); 
     lastInterupt = false;
  
    }

    cpu.emulate();

    if(cpu.failed){
    	running = false;
     }
  } 
  cout << dec;
}  

void readIn(const char* fileName, int* readIndex, uint8_t* memory){
  
  ifstream input(fileName,ios::binary);

  input >> noskipws;

  while(input >> memory[*readIndex]){
    (*readIndex) ++;
  }
  
}


