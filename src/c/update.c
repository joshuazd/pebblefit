#include <pebble.h>


void update_time(TextLayer *s_time_layer) {
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
    APP_LOG(APP_LOG_LEVEL_INFO,"updating time layer");
    text_layer_set_text(s_time_layer,s_buffer+(('0' == s_buffer[0])?1:0));  
  }
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
  APP_LOG(APP_LOG_LEVEL_INFO, "Updating bpm");
  HealthMetric metric = HealthMetricHeartRateBPM;
  
  APP_LOG(APP_LOG_LEVEL_INFO, "BPM: %d", 
          (int)health_service_peek_current_value(metric));
  static char s_buffer[3];
  snprintf(s_buffer, 6, "%d", (int)health_service_peek_current_value(metric));
  text_layer_set_text(s_bpm_layer, s_buffer);
}

void update_steps(TextLayer *s_step_layer) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Updating step count");
  HealthMetric metric = HealthMetricStepCount;
  time_t start = time_start_of_today();
  time_t end = time(NULL);

  // Check the metric has data available for today
  HealthServiceAccessibilityMask mask = health_service_metric_accessible(metric, 
    start, end);
  
  if(mask & HealthServiceAccessibilityMaskAvailable) {
    // Data is available!
    APP_LOG(APP_LOG_LEVEL_INFO, "Steps today: %d", 
            (int)health_service_sum_today(metric));
    static char s_buffer[6];
    snprintf(s_buffer, 6, "%d", (int)health_service_sum_today(metric));
    text_layer_set_text(s_step_layer, s_buffer);
  } else {
    // No data recorded yet today
    APP_LOG(APP_LOG_LEVEL_ERROR, "Data unavailable!");
    text_layer_set_text(s_step_layer, "N/A");
  }
}