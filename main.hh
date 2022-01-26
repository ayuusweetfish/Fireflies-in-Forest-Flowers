#ifndef _main_hh_
#define _main_hh_

namespace rl {
#include "raylib.h"
}

static const int W = 800;
static const int H = 500;

class scene {
public:
  virtual void update() {}
  virtual void draw() {}
  virtual void pton(float, float) {}
  virtual void ptmove(float, float) {}
  virtual void ptoff(float, float) {}
};

scene *scene_startup();
scene *scene_game(int level_id);

#endif
