#pragma once

#include <pebble.h>
#include "graphics.h"
#include "update.h"
#include "layers.h"

void window_date_update();
void window_time_update();
void window_step_update();
void window_bpm_update();
void main_window_push();
void main_window_destroy();