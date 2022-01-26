#include "main.hh"
using namespace rl;

#include <cmath>

int main(int argc, char *argv[])
{
  InitWindow(W, H, NULL);
  SetTargetFPS(60);

  scene *cur_scene = scene_game();
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
      cur_scene->pton(pt_pos.x, pt_pos.y);
      pt_lastx = pt_lasty = nanf("");
    }
    if (pt_on && (pt_pos.x != pt_lastx || pt_pos.y != pt_lasty)) {
      cur_scene->ptmove(pt_pos.x, pt_pos.y);
      pt_lastx = pt_pos.x;
      pt_lasty = pt_pos.y;
    }
    if (pt_laston && !pt_on) {
      cur_scene->ptoff(pt_pos.x, pt_pos.y);
    }
    pt_laston = pt_on;

    // Update
    time += GetFrameTime();
    while (time >= STEP) {
      time -= STEP;
      cur_scene->update();
    }

    // Draw
    cur_scene->draw();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
