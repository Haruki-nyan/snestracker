/* 

SDL Mouse Double Click functionality
author : bazz

How-to: 
@Init: 
call dblclick::init();

in event loop, for example: 
while (SDL_PollEvent(&ev))
{
  dblclick::check_event(&ev);
  ...
  ..
  .
}

*/


#pragma once
#include "SDL.h"
#include "sdl_userevents.h"

namespace dblclick
{ 
  extern SDL_Event trigger_event;
  // Holds event details at time-of-double-click, since a new USER_EVENT
  // is sent, the USER_EVENT itself can't hold the mouse events details..

  extern Uint8 numclicks; // =0;
  extern SDL_TimerID timerid;
  
  // Timer Callback.. Resets double click possibility
  Uint32 reset_dblclicktimer(Uint32 interval=0, void *param=NULL);
  void init();

  
  // You must call this from your Main SDL EVENT LOOP
  void check_event(SDL_Event *ev);

}
