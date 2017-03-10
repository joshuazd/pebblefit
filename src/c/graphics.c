#include "graphics.h"

static Window *s_window;

void graphics_draw_rectangle(GRect bounds, GContext *ctx) {
  graphics_context_set_stroke_width(ctx, 3);
  graphics_context_set_stroke_color(ctx, GColorWhite);
  GRect rect = GRect(5, 5, bounds.size.w - 10, bounds.size.h - 10);
  graphics_draw_rect(ctx, rect);
}

void graphics_set_window(Window *window) {
  s_window = window;
}