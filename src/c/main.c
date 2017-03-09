#include <pebble.h>
#include "update.h"
#include "layers.h"
Window *s_main_window;
TextLayer *s_time_layer;
TextLayer *s_date_layer;
TextLayer *s_step_layer;
TextLayer *s_bpm_layer;
BitmapLayer *s_bitmap_layer_walk;
GBitmap *s_bitmap_walk;
BitmapLayer *s_bitmap_layer_heart;
GBitmap *s_bitmap_heart;

static void update_health() {
  update_steps(s_step_layer);
  update_bpm(s_bpm_layer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time(s_time_layer);
  update_date(s_date_layer);
}

static void main_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  int h = bounds.size.h;
  int w = bounds.size.w;
  
//     s_time_layer = text_layer_create(GRect(0, h/10, w, 84));

//   text_layer_set_background_color(s_time_layer, GColorClear);
//   text_layer_set_text_color(s_time_layer, GColorWhite);
//   text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
//   text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

//   layer_add_child(window_layer, text_layer_get_layer(s_time_layer));

  create_time_layer(w,h,window_layer);
  
  /*
   * DATE LAYER
   */
  s_date_layer = text_layer_create(GRect(0, (h/3)+5, w, 56));
  
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_color(s_date_layer, GColorWhite);
  text_layer_set_font(s_date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
  
  layer_add_child(window_layer, text_layer_get_layer(s_date_layer));
  
  /*
   * STEP LAYER
   */
  s_step_layer = text_layer_create(GRect(50, PBL_IF_ROUND_ELSE(75,95), w, 50));
  
  text_layer_set_background_color(s_step_layer, GColorClear);
  text_layer_set_text_color(s_step_layer, GColorWhite);
  text_layer_set_font(s_step_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(s_step_layer, GTextAlignmentLeft);
  
  layer_add_child(window_layer, text_layer_get_layer(s_step_layer));
  
  /*
   * HEART RATE LAYER
   */
  s_bpm_layer = text_layer_create(GRect(50, PBL_IF_ROUND_ELSE(75,120), w, 50));
  
  text_layer_set_background_color(s_bpm_layer, GColorClear);
  text_layer_set_text_color(s_bpm_layer, GColorWhite);
  text_layer_set_font(s_bpm_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(s_bpm_layer, GTextAlignmentLeft);
  
  layer_add_child(window_layer, text_layer_get_layer(s_bpm_layer));
  
  /*
   * STEP BITMAP
   */
  s_bitmap_walk = gbitmap_create_with_resource(RESOURCE_ID_WALK_ICON);
  s_bitmap_layer_walk = bitmap_layer_create(GRect(28, 103, 18, 18));
  bitmap_layer_set_compositing_mode(s_bitmap_layer_walk, GCompOpSet);
  bitmap_layer_set_bitmap(s_bitmap_layer_walk, s_bitmap_walk);
  
  layer_add_child(window_layer, bitmap_layer_get_layer(s_bitmap_layer_walk));
  
  /*
   * HEART BITMAP
   */
  s_bitmap_heart = gbitmap_create_with_resource(RESOURCE_ID_HEART_ICON);
  s_bitmap_layer_heart = bitmap_layer_create(GRect(28, 128, 18, 18));
  bitmap_layer_set_compositing_mode(s_bitmap_layer_heart, GCompOpSet);
  bitmap_layer_set_bitmap(s_bitmap_layer_heart, s_bitmap_heart);
  
  layer_add_child(window_layer, bitmap_layer_get_layer(s_bitmap_layer_heart));



}


static void health_handler(HealthEventType event, void *context) {
  // Which type of event occurred?
  switch(event) {
    case HealthEventSignificantUpdate:
      APP_LOG(APP_LOG_LEVEL_INFO, 
              "New HealthService HealthEventSignificantUpdate event");
      update_health();
      break;
    case HealthEventMovementUpdate:
      APP_LOG(APP_LOG_LEVEL_INFO, 
              "New HealthService HealthEventMovementUpdate event");
      update_steps(s_step_layer);
      break;
    case HealthEventSleepUpdate:
      APP_LOG(APP_LOG_LEVEL_INFO, 
              "New HealthService HealthEventSleepUpdate event");
      break;
    case HealthEventMetricAlert:
      APP_LOG(APP_LOG_LEVEL_INFO, 
              "New HealthService HealthEventMetricAlert event");
      update_health();
      break;
    case HealthEventHeartRateUpdate:
      APP_LOG(APP_LOG_LEVEL_INFO,
              "New HealthService HealthEventHeartRateUpdate event");
      update_bpm(s_bpm_layer);
      break;
  }
}


static void main_window_unload(Window *window) {
  // Destroy TextLayer
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_step_layer);
  gbitmap_destroy(s_bitmap_walk);
  bitmap_layer_destroy(s_bitmap_layer_walk);
  gbitmap_destroy(s_bitmap_heart);
  bitmap_layer_destroy(s_bitmap_layer_heart);

}

static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();
  
  window_set_background_color(s_main_window, GColorBlack);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  bool health_available = health_service_events_subscribe(health_handler, NULL);
  if(health_available == false) {
    APP_LOG(APP_LOG_LEVEL_WARNING,
            "Health unavailable");
  }


  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  // Make sure the time is displayed from the start
  APP_LOG(APP_LOG_LEVEL_INFO, "updating date and time");
  update_time();
  update_date();

}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
