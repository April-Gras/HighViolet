#include "hv.h"

void apply_frame_delay(ENGINE_TIMERS *timers) {
  timers->ellapsed_milliseconds =
      timers->new_frame_time_stamp - timers->last_frame_time_stamp;
  const Uint32 expected_frame_time = 1000 / timers->target_frames_per_seconds;

  if (timers->ellapsed_milliseconds < expected_frame_time)
    SDL_Delay(expected_frame_time - timers->ellapsed_milliseconds);
}
void engine_timer_update(ENGINE_TIMERS *timers) {
  timers->new_frame_time_stamp = SDL_GetTicks();
  apply_frame_delay(timers);
  timers->last_frame_time_stamp = timers->new_frame_time_stamp;
}
