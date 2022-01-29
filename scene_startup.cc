#include "main.hh"

#include <cstdio>

class scene_startup : public scene {
public:
  scene_startup() {
  }

  void ptoff(float x, float y) {
    replace_scene(scene_text(0));
  }

  void update() {
  }

  void draw() {
    using namespace rl;
    painter::image("intro_bg", vec2(0, 0), vec2(W, H), tint4(1, 1, 1, 1));
    painter::text("Fireflies, Flowers", 60,
      vec2(40, 40), vec2(0, 0),
      tint4(0.9, 0.9, 0.9, 1));
  }
};

scene *scene_startup() {
  return new class scene_startup();
}
