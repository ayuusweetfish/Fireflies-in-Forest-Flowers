#include "main.hh"

#include <cstdio>

class scene_startup : public scene {
public:
  int count;
  float p[2];

  scene_startup() {
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
    using namespace rl;

    ClearBackground(WHITE);
    char s[32];
    snprintf(s, sizeof s, "%f %f | %d", p[0], p[1], count);
    DrawText(s, 10, H / 2, 30, BLACK);
  }
};

scene *scene_startup() {
  return new class scene_startup();
}
