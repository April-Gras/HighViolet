#include "hv.h"

ENGINE_TIMERS *new_engine_timers() {
  ENGINE_TIMERS *timers = (ENGINE_TIMERS *)malloc(sizeof(ENGINE_TIMERS));

  timers->ellapsed_milliseconds = 0;
  timers->last_frame_time_stamp = 0;
  timers->new_frame_time_stamp = 0;
  return timers;
}

void destroy_engine_timers(ENGINE_TIMERS *timers) { free(timers); }