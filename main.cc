#include "main.hh"
using namespace rl;

#ifdef PLATFORM_WEB
  #include <emscripten/emscripten.h>
#endif

#include <cmath>

static scene *cur_scene;
static bool pt_laston = false;
static float pt_lastx, pt_lasty;

static float time = 0;
const float STEP = 1.0f / 240;

static void update_draw_frame()
{
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

int main(int argc, char *argv[])
{
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(W, H, NULL);
  SetTargetFPS(60);

  painter::init();
  cur_scene = scene_game(13);

#ifdef PLATFORM_WEB
  emscripten_set_main_loop(update_draw_frame, 0, 1);
#else
  while (!WindowShouldClose())
    update_draw_frame();
#endif

  CloseWindow();

  return 0;
}
