#include "graphics.h"

static Window *s_window;

static GPath *s_my_path_ptr = NULL;

static const GPathInfo TOP_RIGHT_PATH = {
  .num_points = 2,
  //.points = (GPoint []) {{21, 0}, {14, 26}, {28, 26}, {7, 60}, {14, 34}, {0, 34}}
  .points = (GPoint []) {{72,3}, {141,3}}
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
  .points = (GPoint []) {{3,3}, {72,3}}
};

void graphics_draw_rectangle(GRect bounds, GContext *ctx, int border_parts, int pixels) {
  graphics_context_set_stroke_width(ctx, 3);
  graphics_context_set_stroke_color(ctx, GColorWhite);

  GPoint last_point = {0,0};
  GPathInfo paths[] = {TOP_RIGHT_PATH, RIGHT_PATH, BOTTOM_PATH, LEFT_PATH, TOP_LEFT_PATH};
  int PATH_COUNT = 5;
//  int i=0;
  for(int i=0; i < PATH_COUNT; ++i) {
      GPathInfo path = paths[i];
      if(border_parts > 0) {
          s_my_path_ptr = gpath_create(&path);
          gpath_draw_outline(ctx, s_my_path_ptr);
          last_point.x = path.points[1].x;
          last_point.y = path.points[1].y;
      }
      border_parts--;
  }

  if(last_point.x != 0) {

    GPoint draw_to = {0,0};

    if(last_point.x == 141) {
        if(last_point.y == 3) {
            draw_to = (GPoint){141, 3+pixels};
        } else {
            draw_to = (GPoint){141-pixels, 165};
        }
    } else if(last_point.x == 3) {
        if(last_point.y == 165) {
            draw_to = (GPoint){3, 165-pixels};
        } else {
            pixels = (pixels > 69) ? 69 : pixels;
            draw_to = (GPoint){3, 3+pixels};
        }
    }

    APP_LOG(APP_LOG_LEVEL_INFO, "%d, %d", draw_to.x, draw_to.y);
    const int x1=last_point.x;
    const int y1=last_point.y;
    const int x2=draw_to.x;
    const int y2=draw_to.y;

    //static const GPathInfo LAST_PATH = {
    //  .num_points = 2,
    //  .points = (GPoint []) {{x1, y1}, {x2, y2}}
    //};
    s_my_path_ptr = gpath_create(&(GPathInfo){.num_points=2, .points=((GPoint []){{x1, y1}, {x2, y2}})});
    gpath_draw_outline(ctx, s_my_path_ptr);
  }

//  gpath_draw_outline(ctx, s_my_path_ptr);
//   GRect rect = GRect(5, 5, bounds.size.w - 10, bounds.size.h - 10);
//   graphics_draw_rect(ctx, rect);
}

void graphics_set_window(Window *window) {
  s_window = window;
}

