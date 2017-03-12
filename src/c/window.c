#include "window.h"

static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_date_layer;
static TextLayer *s_step_layer;
static TextLayer *s_bpm_layer;
static BitmapLayer *s_bitmap_layer_walk;
static GBitmap *s_bitmap_walk;
static BitmapLayer *s_bitmap_layer_heart;
static GBitmap *s_bitmap_heart;
static Layer *s_canvas_layer;
static Layer *s_typical_layer;

void window_date_update() {
  update_date(s_date_layer);
}

void window_time_update() {
  update_time(s_time_layer);
}

void window_step_update() {
  update_steps(s_step_layer);
  layer_mark_dirty(s_canvas_layer);
}

void window_bpm_update() {
  update_bpm(s_bpm_layer);
}

static void main_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  int h = bounds.size.h;
  int w = bounds.size.w;
  APP_LOG(APP_LOG_LEVEL_INFO, "Height: %d, Width: %d", h, w);

  s_time_layer = text_layer_create(GRect(0, h/10, w, 84));
  create_time_layer(window_layer,s_time_layer);

  s_date_layer = text_layer_create(GRect(0, (h/3)+5, w, 56));
  create_date_layer(window_layer,s_date_layer);

  s_step_layer = text_layer_create(GRect(50, PBL_IF_ROUND_ELSE(75,95), w, 50));
  create_step_layer(window_layer,s_step_layer);

  s_bpm_layer = text_layer_create(GRect(50, PBL_IF_ROUND_ELSE(75,120), w, 50));
  create_bpm_layer(window_layer,s_bpm_layer);

  create_step_icon(window_layer, s_bitmap_walk, s_bitmap_layer_walk);

  create_heart_icon(window_layer, s_bitmap_heart, s_bitmap_layer_heart);

  s_canvas_layer = layer_create(bounds);
  layer_set_update_proc(s_canvas_layer, update_progress);
  layer_add_child(window_layer, s_canvas_layer);

  s_typical_layer = layer_create(bounds);
  layer_set_update_proc(s_typical_layer, update_typical);
  layer_add_child(window_layer, s_typical_layer);
}

static void main_window_unload(Window *window) {
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_step_layer);
  gbitmap_destroy(s_bitmap_walk);
  bitmap_layer_destroy(s_bitmap_layer_walk);
  gbitmap_destroy(s_bitmap_heart);
  bitmap_layer_destroy(s_bitmap_layer_heart);
  layer_destroy(s_canvas_layer);
  layer_destroy(s_typical_layer);
}

void main_window_push() {

  // Create main Window element and assign to pointer
  s_main_window = window_create();

  window_set_background_color(s_main_window, GColorBlack);

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);

  graphics_set_window(s_main_window);
}

void main_window_destroy() {
  window_destroy(s_main_window);
}
