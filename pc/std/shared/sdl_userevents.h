//sdl_userevents.h
#pragma once

namespace UserEvents
{
  enum Events
  {
    #include "sdl_dblclick_events.enum"
    mouse_ani,
    callback,

    play_pitch,
    keyoff,
    sound_stop,

		report_tracker_incrow,
		report_tracker_setrow,
		report_tracker_setpattern,
  };
}
