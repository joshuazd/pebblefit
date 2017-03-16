#pragma once

#include <pebble.h>

void graphics_draw_typical(GRect bounds, GContext *ctx, int pixels);
void graphics_draw_rectangle(GRect bounds, GContext *ctx, int border_parts, int pixels);
void graphics_set_window(Window *window);
void graphics_destroy();
