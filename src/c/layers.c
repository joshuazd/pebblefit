#include <pebble.h>

/**
 * TIME LAYER
 */
void create_time_layer(int w, int h, Layer *window_layer, TextLayer *s_time_layer) {
  APP_LOG(APP_LOG_LEVEL_INFO,"creating time layer");
  s_time_layer = text_layer_create(GRect(0, h/10, w, 84));

  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorWhite);
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
}