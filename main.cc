#include "main.hh"
using namespace rl;

#ifdef PLATFORM_WEB
  #include <emscripten/emscripten.h>
#endif

#include <cmath>

static scene *cur_scene, *prev_scene = NULL;
static const int TRANSITION_DUR = 360;
static int transition_timer;
static bool pt_laston = false;
static float pt_lastx, pt_lasty;

static float time = 0;
const float STEP = 1.0f / 240;

void replace_scene(scene *s)
{
  prev_scene = cur_scene;
  cur_scene = s;
  transition_timer = 0;
}

#include <cstdio>
static inline void transition_draw()
{
  float t = (float)transition_timer / TRANSITION_DUR;
  float alpha = (1 - cosf(t * (2 * M_PI))) / 2;
  if (t < 0.5) prev_scene->draw();
  else cur_scene->draw();
  rl::DrawRectangle(0, 0, W, H,
    (Color){0, 0, 0, (unsigned char)(alpha * 255.5)});
}

static void update_draw_frame()
{
  BeginDrawing();

  // Mouse
  bool pt_on = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
  // Disable all pointer events during transition
  if (prev_scene != NULL) pt_on = false;
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
    // Transition
    if (prev_scene != NULL) {
      prev_scene->update();
      transition_timer++;
      if (transition_timer == TRANSITION_DUR) {
        delete prev_scene;
        prev_scene = NULL;
      }
    }
  }

  // Draw
  if (prev_scene != NULL) {
    transition_draw();
  } else {
    cur_scene->draw();
  }

  EndDrawing();
}

int main(int argc, char *argv[])
{
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(W, H, NULL);
  SetTargetFPS(60);

  painter::init();
  cur_scene = scene_startup();
  //cur_scene = scene_game(9);
  //cur_scene = scene_game(20);
  //cur_scene = scene_text(25);

#if defined(PLATFORM_WEB) && defined(NO_ASYNCIFY)
  // Not using Asyncify might incur additional power consumption
  emscripten_set_main_loop(update_draw_frame, 0, 1);
#else
  while (!WindowShouldClose())
    update_draw_frame();
#endif

  CloseWindow();

  return 0;
}
