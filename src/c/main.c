#include <pebble.h>
#include "update.h"
#include "layers.h"
#include "window.h"
#include "graphics.h"

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  if(tick_time->tm_min == 0) {
    window_date_update();
  }
  window_time_update();
}

static void health_handler(HealthEventType event, void *context) {
  // Which type of event occurred?
  switch(event) {
    case HealthEventSignificantUpdate:
      APP_LOG(APP_LOG_LEVEL_INFO,
              "New HealthService HealthEventSignificantUpdate event");
      window_step_update();
      window_bpm_update();
      break;
    case HealthEventMovementUpdate:
      APP_LOG(APP_LOG_LEVEL_INFO,
              "New HealthService HealthEventMovementUpdate event");
      window_step_update();
      break;
    case HealthEventSleepUpdate:
      APP_LOG(APP_LOG_LEVEL_INFO,
              "New HealthService HealthEventSleepUpdate event");
      break;
    case HealthEventMetricAlert:
      APP_LOG(APP_LOG_LEVEL_INFO,
              "New HealthService HealthEventMetricAlert event");
      window_step_update();
      window_bpm_update();
      break;
    case HealthEventHeartRateUpdate:
      APP_LOG(APP_LOG_LEVEL_INFO,
              "New HealthService HealthEventHeartRateUpdate event");
      window_bpm_update();
      break;
  }
}

static void init() {

  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  bool health_available = health_service_events_subscribe(health_handler, NULL);
  if(health_available == false) {
    APP_LOG(APP_LOG_LEVEL_WARNING,
            "Health unavailable");
  }

  main_window_push();

  // Make sure the time is displayed from the start
  APP_LOG(APP_LOG_LEVEL_INFO, "updating date and time");
  window_time_update();
  window_date_update();

}

static void deinit() {
  // Destroy Window
  main_window_destroy();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
