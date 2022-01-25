#include "main.hh"

#include "raylib.h"
#include <cstdio>

class _scene_startup : public scene {
public:
  int count;
  float p[2];

  _scene_startup() {
    count = 100;
    p[0] = -1;
    p[1] = -1;
  }

  void ptmove(float x, float y) {
    p[0] = x;
    p[1] = y;
  }

  void ptoff(float x, float y) {
    p[0] = -1;
  }

  void update() {
    count++;
  }

  void draw() {
    ClearBackground(WHITE);
    char s[32];
    snprintf(s, sizeof s, "%f %f | %d", p[0], p[1], count);
    DrawText(s, 10, H / 2, 30, BLACK);
  }
};

scene *scene_startup() {
  return new _scene_startup();
}
