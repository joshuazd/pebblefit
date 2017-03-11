#include "layers.h"

/**
 * TIME LAYER
 */
void create_time_layer(Layer *window_layer, TextLayer *s_time_layer) {
  APP_LOG(APP_LOG_LEVEL_INFO, "creating time layer");

  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorWhite);
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
}

/**
 * DATE LAYER
 */
void create_date_layer(Layer *window_layer, TextLayer *s_date_layer) {
  APP_LOG(APP_LOG_LEVEL_INFO, "creating date layer");
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_color(s_date_layer, GColorWhite);
  text_layer_set_font(s_date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);

  layer_add_child(window_layer, text_layer_get_layer(s_date_layer));
}

/**
 * STEP LAYER
 */
void create_step_layer(Layer *window_layer, TextLayer *s_step_layer) {
  APP_LOG(APP_LOG_LEVEL_INFO, "creating step layer");

  text_layer_set_background_color(s_step_layer, GColorClear);
  text_layer_set_text_color(s_step_layer, GColorWhite);
  text_layer_set_font(s_step_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(s_step_layer, GTextAlignmentLeft);

  layer_add_child(window_layer, text_layer_get_layer(s_step_layer));
}

/**
 * HEART RATE LAYER
 */
void create_bpm_layer(Layer *window_layer, TextLayer *s_bpm_layer) {
  APP_LOG(APP_LOG_LEVEL_INFO, "creating bpm layer");

  text_layer_set_background_color(s_bpm_layer, GColorClear);
  text_layer_set_text_color(s_bpm_layer, GColorWhite);
  text_layer_set_font(s_bpm_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(s_bpm_layer, GTextAlignmentLeft);

  layer_add_child(window_layer, text_layer_get_layer(s_bpm_layer));
}

/**
 * STEP ICON
 */
void create_step_icon(Layer *window_layer, GBitmap *s_bitmap_walk, BitmapLayer *s_bitmap_layer_walk) {
  APP_LOG(APP_LOG_LEVEL_INFO, "creating step icon layer");

  s_bitmap_walk = gbitmap_create_with_resource(RESOURCE_ID_WALK_ICON);
  s_bitmap_layer_walk = bitmap_layer_create(GRect(28, 103, 18, 18));
  bitmap_layer_set_compositing_mode(s_bitmap_layer_walk, GCompOpSet);
  bitmap_layer_set_bitmap(s_bitmap_layer_walk, s_bitmap_walk);

  layer_add_child(window_layer, bitmap_layer_get_layer(s_bitmap_layer_walk));
}

/**
 * HEART ICON
 */
void create_heart_icon(Layer *window_layer, GBitmap *s_bitmap_heart, BitmapLayer *s_bitmap_layer_heart) {
  APP_LOG(APP_LOG_LEVEL_INFO, "creating heart icon layer");
  s_bitmap_heart = gbitmap_create_with_resource(RESOURCE_ID_HEART_ICON);
  s_bitmap_layer_heart = bitmap_layer_create(GRect(28, 128, 18, 18));
  bitmap_layer_set_compositing_mode(s_bitmap_layer_heart, GCompOpSet);
  bitmap_layer_set_bitmap(s_bitmap_layer_heart, s_bitmap_heart);

  layer_add_child(window_layer, bitmap_layer_get_layer(s_bitmap_layer_heart));
}
