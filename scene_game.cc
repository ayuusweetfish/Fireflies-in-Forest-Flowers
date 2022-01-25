#include "main.hh"

#include "raylib.h"
#include <cstdio>

class _scene_game : public scene {
public:
};

scene *scene_game() {
  return new _scene_game();
}
