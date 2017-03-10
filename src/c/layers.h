#pragma once

#include <pebble.h>

void create_time_layer(Layer *window_layer, TextLayer *s_time_layer);
void create_date_layer(Layer *window_layer, TextLayer *s_date_layer);
void create_step_layer(Layer *window_layer, TextLayer *s_step_layer);
void create_bpm_layer(Layer *window_layer, TextLayer *s_bpm_layer);
void create_step_icon(Layer *window_layer, GBitmap *s_bitmap_walk, BitmapLayer *s_bitmap_layer_walk);
void create_heart_icon(Layer *window_layer, GBitmap *s_bitmap_heart, BitmapLayer *s_bitmap_layer_heart);