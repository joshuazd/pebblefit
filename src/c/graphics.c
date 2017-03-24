#include "graphics.h"
#include <stdlib.h>

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

void graphics_draw_typical(GRect bounds, GContext *ctx, int pixels) {
    graphics_context_set_fill_color(ctx, GColorWhite);
    int offset = 9;
    int w = bounds.size.w, h = bounds.size.h;

    APP_LOG(APP_LOG_LEVEL_INFO, "Pixels: %d", pixels);

    GPoint corners[] = {{w/2,offset}, {w-offset, offset}, {w-offset,h-offset}, {offset,h-offset}, {offset,offset}, {w/2,offset}};
    int num_corners = 6;
    int last_corner = -1;
    for(int i=1; i<num_corners; ++i) {
        int distance = abs(corners[i].x - corners[i-1].x) + abs(corners[i].y - corners[i-1].y);
        if(pixels >= distance && last_corner == -1) {
            pixels -= distance;
        } else if(last_corner == -1){
            last_corner = i-1;
        }
    }

    if(last_corner == -1) {
      last_corner = 5;
    }

    APP_LOG(APP_LOG_LEVEL_INFO, "Last corner: %d", last_corner);
    APP_LOG(APP_LOG_LEVEL_INFO, "Pixels: %d", pixels);
    GPoint point = (GPoint){0,0};
    GPoint last = corners[last_corner];

    if(last.x == w-offset) {
        if(last.y == offset) {
            point.x = last.x;
            point.y = last.y + pixels;
        } else {
            point.x = last.x - pixels;
            point.y = last.y;
        }
    } else if(last.x == offset) {
        if(last.y == offset) {
            point.x = last.x + pixels;
            point.y = last.y;
        } else {
            point.x = last.x;
            point.y = last.y - pixels;
        }
    } else {
        point.x = last.x + pixels;
        point.y = last.y;
    }

    graphics_fill_circle(ctx, point, 2);

}


void graphics_draw_rectangle(GRect bounds, GContext *ctx, int border_parts, int pixels) {
  graphics_context_set_stroke_width(ctx, 3);
  graphics_context_set_stroke_color(ctx, GColorWhite);

  GPoint last_point = {72,3};
  GPathInfo paths[] = {TOP_RIGHT_PATH, RIGHT_PATH, BOTTOM_PATH, LEFT_PATH, TOP_LEFT_PATH};
  int PATH_COUNT = 5;
  for(int i=0; i < PATH_COUNT; ++i) {
      GPathInfo path = paths[i];
      if(border_parts > 0) {
          s_my_path_ptr = gpath_create(&path);
          gpath_draw_outline(ctx, s_my_path_ptr);
          last_point.x = path.points[1].x;
          last_point.y = path.points[1].y;
          border_parts--;
      }
  }

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
          draw_to = (GPoint){3+pixels, 3};
      }
  } else if(border_parts == -1){
      draw_to = (GPoint){72+pixels, 3};
  }

  const int x1=last_point.x;
  const int y1=last_point.y;
  const int x2=draw_to.x;
  const int y2=draw_to.y;

  if(x2 != 0) {
      s_my_path_ptr = gpath_create(&(GPathInfo){.num_points=2, .points=((GPoint []){{x1, y1}, {x2, y2}})});
      gpath_draw_outline(ctx, s_my_path_ptr);
  }

}

void graphics_set_window(Window *window) {
  s_window = window;
}


void graphics_destroy() {
    gpath_destroy(s_my_path_ptr);    
}
