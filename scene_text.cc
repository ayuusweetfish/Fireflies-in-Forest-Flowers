#include "main.hh"

#include <cstdio>

struct entry {
  const char *text;
  union {
    const char *image;
    int puzzle;
  };
  entry(const char *text, const char *image = NULL)
    : text(text), image(image)
    { }
  entry(int puzzle)
    : text(NULL), puzzle(puzzle)
    { }
};
static entry script[] = {
  // 0
  entry("Here we are,\nthe Magical Forest of Yonder.", "avatar_up"),
  entry("Where is Nana?", "avatar_up"),
  entry("We don't see her, but we can\nlet her know that we care."),
  entry("Come, meet the fireflies."),
  entry(1),

  // 5
  entry("When a bellflower opens its petals,\na light can be seen from Nana's world as well."),
  entry("Let's light up all of them! She can't miss it!"),
  entry(2),
  entry(-1),
  entry(-1),

  // 10
  entry("Nana! It's me!"),
  entry(4),

  entry("A"),
  entry("B"),
  entry("C"),
  entry(-1),
};

class scene_text : public scene {
public:
  int entry_id;
  int since_change;

  scene_text(int entry_id)
    : entry_id(entry_id), since_change(0)
  {
  }

  void ptoff(float x, float y) {
    if (script[entry_id].text != NULL && since_change >= 180) {
      entry_id++;
      since_change = 0;
    }
  }

  void update() {
    since_change++;
    if (script[entry_id].text == NULL &&
        script[entry_id].puzzle != -1 &&
        since_change == 300) {
      replace_scene(scene_game(script[entry_id].puzzle));
    }
  }

  void draw() {
    using namespace rl;

    ClearBackground((Color){5, 10, 1, 255});
    painter::image("intro_bg", vec2(0, 0), tint4(1, 1, 1, 0.5));

    float cur_alpha = 1, last_alpha = 0;
    float displacement = 0;
    const float MOVE_Y = H * 0.05;

    #define cub(_x) ((_x) * (_x) * (_x))
    if (since_change < 180) {
      float x = (float)since_change / 180;
      cur_alpha = (x < 0.3 ? 0 : (x > 0.7 ? 1 : ((x - 0.3) / 0.4)));
      if (entry_id > 0 && script[entry_id - 1].text != NULL) {
        last_alpha = (x < 0.4 ? cub(1 - x / 0.4) : 0);
      }
      displacement = exp(-2.5 * x) * (1 - x);
    }

    if (last_alpha > 0) {
      if (script[entry_id - 1].image != NULL)
        painter::image(
          script[entry_id - 1].image,
          vec2(W * 0.5, H * 0.47), vec2(0.5, 1), vec2(1, 1),
          tint4(1, 1, 1, last_alpha)
        );
      painter::text(
        script[entry_id - 1].text, 32,
        vec2(W * 0.5, H * 0.53 + (-1 + displacement) * MOVE_Y), vec2(0.5, 0),
        tint4(0.9, 0.9, 0.9, last_alpha)
      );
    }
    if (script[entry_id].text != NULL) {
      if (script[entry_id].image != NULL)
        painter::image(
          script[entry_id].image,
          vec2(W * 0.5, H * 0.47), vec2(0.5, 1), vec2(1, 1),
          tint4(1, 1, 1, cur_alpha)
        );
      painter::text(
        script[entry_id].text, 32,
        vec2(W * 0.5, H * 0.53 + displacement * MOVE_Y), vec2(0.5, 0),
        tint4(0.9, 0.9, 0.9, cur_alpha)
      );
    }
  }
};

scene *scene_text(int entry_id) {
  return new class scene_text(entry_id);
}
