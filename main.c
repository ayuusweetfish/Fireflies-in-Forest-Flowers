#include "main.h"

#include "raylib.h"
#include "raymath.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  InitWindow(W, H, NULL);
  SetTargetFPS(60);

  scene cur_scene = scene_startup_create();
  bool pt_laston = false;
  float pt_lastx, pt_lasty;

  float time = 0;
  float STEP = 1.0f / 240;

  while (!WindowShouldClose()) {
    BeginDrawing();

    // Mouse
    bool pt_on = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    Vector2 pt_pos = GetMousePosition();
    if (!pt_laston && pt_on) {
      if (cur_scene.pton) cur_scene.pton(cur_scene.data, pt_pos.x, pt_pos.y);
      pt_lastx = pt_lasty = nanf("");
    }
    if (pt_on && (pt_pos.x != pt_lastx || pt_pos.y != pt_lasty)) {
      if (cur_scene.ptmove) cur_scene.ptmove(cur_scene.data, pt_pos.x, pt_pos.y);
      pt_lastx = pt_pos.x;
      pt_lasty = pt_pos.y;
    }
    if (pt_laston && !pt_on) {
      if (cur_scene.ptoff) cur_scene.ptoff(cur_scene.data, pt_pos.x, pt_pos.y);
    }
    pt_laston = pt_on;

    // Update
    time += GetFrameTime();
    while (time >= STEP) {
      time -= STEP;
      cur_scene.update(cur_scene.data);
    }

    // Draw
    cur_scene.draw(cur_scene.data);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
