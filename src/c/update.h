#pragma once

#include <pebble.h>
#include "graphics.h"

void update_progress(Layer *layer, GContext *ctx);
void update_time(TextLayer *s_time_layer);
void update_date(TextLayer *s_date_layer);
void update_bpm(TextLayer *s_bpm_layer);
void update_steps(TextLayer *s_step_layer);