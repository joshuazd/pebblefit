#include "update.h"

static int cur_steps;
static int perimeter;

void update_progress(Layer *layer, GContext *ctx) {
  
  GRect bounds = layer_get_bounds(layer);
  perimeter = 2*bounds.size.w + 2*bounds.size.h;
  int border_parts = 0;
  int pixels = 0;

  HealthMetric metric = HealthMetricStepCount;
  time_t start = time_start_of_today();
  time_t now = time(NULL);
  time_t end = start + (SECONDS_PER_HOUR * HOURS_PER_DAY) - 1;

  // Check the metric has data available for today
  HealthServiceAccessibilityMask mask = health_service_metric_accessible(metric, 
    start, now);
  
  if(mask & HealthServiceAccessibilityMaskAvailable) {
    // Data is available!
    int avg_steps;
    avg_steps = (int)health_service_sum_averaged(metric, start, now, HealthServiceTimeScopeWeekly);
    APP_LOG(APP_LOG_LEVEL_INFO, "Avg Step so far: %d", avg_steps);
    
    avg_steps = (int)health_service_sum_averaged(metric, start, end, HealthServiceTimeScopeWeekly);
    APP_LOG(APP_LOG_LEVEL_INFO, "Avg steps for this day: %d", avg_steps);
    
    APP_LOG(APP_LOG_LEVEL_INFO, "Current steps for today: %d", cur_steps);

    float percent_of_steps = (float)cur_steps/avg_steps;
    APP_LOG(APP_LOG_LEVEL_INFO, "Percent of typical: %i%%", (int)(percent_of_steps*100)); 

    pixels = (int)(percent_of_steps*perimeter);
    APP_LOG(APP_LOG_LEVEL_INFO, "Pixels around perimeter: %i", pixels);

  

    // TOP_RIGHT
    if ( pixels > 69 ) {
      border_parts++; 
      pixels -= 64;
    }
    // RIGHT
    if ( pixels > 162 ) {
      border_parts++;
      pixels -= 162;
    }
    // BOTTOM
    if ( pixels > 138 ) {
      border_parts++;
      pixels -= 138;
    }
    // LEFT
    if ( pixels > 162 ) {
      border_parts++;
      pixels -= 162;
    }
    // TOP LEFT
    if ( pixels > 69 ) {
      border_parts++;
      pixels -= 69;
    }
    
    APP_LOG(APP_LOG_LEVEL_INFO, "Border parts: %d, pixels: %d", border_parts, pixels);


    
  } else {
    // No data recorded yet today
    APP_LOG(APP_LOG_LEVEL_ERROR, "Data unavailable!");
  }
  
  graphics_draw_rectangle(bounds, ctx, border_parts, pixels);
}

void update_time(TextLayer *s_time_layer) {
  APP_LOG(APP_LOG_LEVEL_INFO, "updating time");
  // Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into a buffer
  static char s_buffer[9];
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(s_buffer, sizeof(s_buffer), "%H:%M", tick_time);
    text_layer_set_text(s_time_layer,s_buffer);
  } else {
    // Use 12 hour format
    strftime(s_buffer, sizeof(s_buffer), "%I:%M", tick_time);
    text_layer_set_text(s_time_layer,s_buffer+(('0' == s_buffer[0])?1:0));  
  }
  APP_LOG(APP_LOG_LEVEL_INFO, "time updated");
}

void update_date(TextLayer *s_date_layer) {
  APP_LOG(APP_LOG_LEVEL_INFO, "updating date");
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  
  static char s_buffer[8];
  strftime(s_buffer, sizeof(s_buffer), "%b %d", tick_time);
  
  text_layer_set_text(s_date_layer, s_buffer);
  APP_LOG(APP_LOG_LEVEL_INFO, "date updated");
}

void update_bpm(TextLayer *s_bpm_layer) {
  APP_LOG(APP_LOG_LEVEL_INFO, "updating bpm");
  HealthMetric metric = HealthMetricHeartRateBPM;
  
  APP_LOG(APP_LOG_LEVEL_INFO, "BPM: %d", 
          (int)health_service_peek_current_value(metric));
  static char s_buffer[3];
  snprintf(s_buffer, 3, "%d", (int)health_service_peek_current_value(metric));
  text_layer_set_text(s_bpm_layer, s_buffer);
  APP_LOG(APP_LOG_LEVEL_INFO, "bpm updated");
}

void update_steps(TextLayer *s_step_layer) {
  APP_LOG(APP_LOG_LEVEL_INFO, "updating step count");
  HealthMetric metric = HealthMetricStepCount;
  time_t start = time_start_of_today();
  time_t end = time(NULL);

  // Check the metric has data available for today
  HealthServiceAccessibilityMask mask = health_service_metric_accessible(metric, 
    start, end);
  
  if(mask & HealthServiceAccessibilityMaskAvailable) {
    // Data is available!
    static char s_buffer[6];
    cur_steps = (int)health_service_sum_today(metric);
    snprintf(s_buffer, 6, "%d", cur_steps);
    text_layer_set_text(s_step_layer, s_buffer);
  } else {
    // No data recorded yet today
    APP_LOG(APP_LOG_LEVEL_ERROR, "Data unavailable!");
    // text_layer_set_text(s_step_layer, "N/A");
  }
  APP_LOG(APP_LOG_LEVEL_INFO, "step count updated");
}
