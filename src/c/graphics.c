#include "graphics.h"

static Window *s_window;

static GPath *s_my_path_ptr = NULL;

static const GPathInfo TOP_RIGHT_PATH = {
  .num_points = 2,
  //.points = (GPoint []) {{21, 0}, {14, 26}, {28, 26}, {7, 60}, {14, 34}, {0, 34}}
  .points = (GPoint []) {{77,3}, {141,3}}
};

static const GPathInfo RIGHT_PATH = {
  .num_points = 2,
  //.points = (GPoint []) {{21, 0}, {14, 26}, {28, 26}, {7, 60}, {14, 34}, {0, 34}}
  .points = (GPoint []) {{141,3}, {141,165}}
};

static const GPathInfo BOTTOM_PATH = {
  .num_points = 2,
  //.points = (GPoint []) {{21, 0}, {14, 26}, {28, 26}, {7, 60}, {14, 34}, {0, 34}}
  .points = (GPoint []) {{141,165}, {3,165}}
};

static const GPathInfo LEFT_PATH = {
  .num_points = 2,
  //.points = (GPoint []) {{21, 0}, {14, 26}, {28, 26}, {7, 60}, {14, 34}, {0, 34}}
  .points = (GPoint []) {{3,165}, {3,3}}
};

static const GPathInfo TOP_LEFT_PATH = {
  .num_points = 2,
  //.points = (GPoint []) {{21, 0}, {14, 26}, {28, 26}, {7, 60}, {14, 34}, {0, 34}}
  .points = (GPoint []) {{3,3}, {77,3}}
};

void graphics_draw_rectangle(GRect bounds, GContext *ctx) {
  graphics_context_set_stroke_width(ctx, 3);
  graphics_context_set_stroke_color(ctx, GColorWhite);
  s_my_path_ptr = gpath_create(&TOP_RIGHT_PATH);
  gpath_draw_outline(ctx, s_my_path_ptr);
  s_my_path_ptr = gpath_create(&RIGHT_PATH);
  gpath_draw_outline(ctx, s_my_path_ptr);
  s_my_path_ptr = gpath_create(&BOTTOM_PATH);
  gpath_draw_outline(ctx, s_my_path_ptr);
  s_my_path_ptr = gpath_create(&LEFT_PATH);
  gpath_draw_outline(ctx, s_my_path_ptr);
  s_my_path_ptr = gpath_create(&TOP_LEFT_PATH);
  gpath_draw_outline(ctx, s_my_path_ptr);
  
  gpath_draw_outline(ctx, s_my_path_ptr);
//   GRect rect = GRect(5, 5, bounds.size.w - 10, bounds.size.h - 10);
//   graphics_draw_rect(ctx, rect);
}

void graphics_set_window(Window *window) {
  s_window = window;
}