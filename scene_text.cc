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
  entry(_("Here we are,\nthe Magical Forest of Yonder.",
          "我们到了！这里是彼岸之林。"),
        "avatar_intro"),
  entry(_("Where is Nana?\nIs she in this forest?",
          "奈奈在哪儿呀？在这片森林里吗？"),
        "avatar_question"),
  entry(_("We won't see her, but we can\nlet her know that we've come.",
          "我们在这里见不到她，\n不过有办法让她知道我们来啦。"),
        "avatar_intro"),
  entry(_("...", "……"), "avatar_question"),
  entry(_("Here, let the fireflies tell you.",
          "来这儿，萤火虫会告诉你的。"),
        "avatar_intro"),
  // 5
  entry(0),

  // 6
  entry(_("When a bellflower opens its petals,\na light can be seen from Nana's world as well.",
          "当一朵风铃花绽放时，\n奈奈的世界里也能看到一束光亮。"),
    "avatar_bellflowers"),
  entry(_("She will know it.",
          "她会知道的。"),
        "avatar_intro"),
  entry(_("Let's light up all of them! She can't miss it!",
          "那就把它们全都点亮吧！别让她错过了！"),
        "avatar_lightall"),
  entry(2),

  // 10
  entry("Nana! It's me!", "avatar_lantern"),
  entry("How is your life there?", "avatar_bellflowers"),
  entry("We miss you so much!", "avatar_lantern"),
  entry(4),
  entry(-1),

  // 15
  entry("", "avatar_rain"),
  entry("Nana does not want to see you sad.", "avatar_bedside"),
  entry("You might meet her in the dreams.", "avatar_intro"),
  entry("Nighty-night.", "avatar_night"),
  entry(10),

  // 20
  entry("Nana, if you can hear me...", "avatar_bush"),
  entry("... please let your wild friend come to me.", "avatar_oracle"),
  entry("...", "avatar_bush"),
  entry("...", "avatar_oracle"),
  entry("...", "avatar_bush"),
  entry("Maybe I should finally stop daydreaming like this.", "avatar_oracle"),
  entry(15),

  // 27
  entry("...?!", "avatar_cat"),
  entry("Nana, we can't give you treats any more...", "avatar_lantern"),
  entry("Remember to take care of yourself!", "avatar_bellflowers"),
  entry("Alice?! Is that you, Alice?!", "avatar_cat"),
  entry("We love you always...!", "avatar_lantern"),
  entry("", "avatar_cat"),
  entry("", "avatar_lantern"),
  entry("", "avatar_night"),
  entry(-2),
};

static inline bool empty(const char *s) { return s != NULL && s[0] == '\0'; }

class scene_text : public scene {
public:
  int entry_id;
  int since_change;

  scene_text(int entry_id)
    : entry_id(entry_id), since_change(0)
  {
  }

  void ptoff(float x, float y) {
    if (script[entry_id].puzzle != -2 && since_change >= 180) {
      entry_id++;
      since_change = 0;
    }
  }

  void update() {
    since_change++;
    if (script[entry_id].text == NULL &&
        script[entry_id].puzzle >= 0 &&
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
    #define prog_alpha(_x) ((_x) < 0.3 ? 0 : ((_x) > 0.7 ? 1 : (((_x) - 0.3) / 0.4)))
    #define prog_displ(_x) exp(-2.5 * (_x)) * (1 - (_x))
    if (since_change < 180) {
      float x = (float)since_change / 180;
      cur_alpha = prog_alpha(x);
      if (entry_id > 0 && script[entry_id - 1].text != NULL) {
        last_alpha = (x < 0.4 ? cub(1 - x / 0.4) : 0);
      }
      displacement = prog_displ(x);
    }

    if (last_alpha > 0) {
      if (script[entry_id - 1].image != NULL)
        painter::image(
          script[entry_id - 1].image,
          vec2(W * 0.5, H *
            (empty(script[entry_id - 1].text) ? 0.57 : 0.47)),
          vec2(0.5, 1), vec2(1, 1),
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
          vec2(W * 0.5, H *
            (empty(script[entry_id].text) ? 0.57 : 0.47)),
          vec2(0.5, 1), vec2(1, 1),
          tint4(1, 1, 1, cur_alpha)
        );
      painter::text(
        script[entry_id].text, 32,
        vec2(W * 0.5, H * 0.53 + displacement * MOVE_Y), vec2(0.5, 0),
        tint4(0.9, 0.9, 0.9, cur_alpha)
      );
    } else if (script[entry_id].puzzle == -2) {
      painter::text(
        "Fireflies and Forest Flowers", 32,
        vec2(W * 0.5, H * 0.49 + displacement * MOVE_Y - 24), vec2(0.5, 0),
        tint4(0.9, 0.9, 0.9, cur_alpha)
      );
      painter::text(
        "-   The End   -", 32,
        vec2(W * 0.5, H * 0.49 + displacement * MOVE_Y + 24), vec2(0.5, 0),
        tint4(0.9, 0.9, 0.9, cur_alpha)
      );
      float x1 = (float)(since_change - 480) / 240;
      float x2 = (float)(since_change - 500) / 240;
      x1 = (x1 > 1 ? 1 : x1 < 0 ? 0 : x1);
      x2 = (x2 > 1 ? 1 : x2 < 0 ? 0 : x2);
      painter::text(
        "Thanks for playing!", 24,
        vec2(W - 16, H - 44 + prog_displ(x1) * MOVE_Y), vec2(1, 1),
        tint4(0.6, 0.6, 0.6, prog_alpha(x1))
      );
      painter::text(
        "Ayu  2022.02-08", 24,
        vec2(W - 16, H - 16 + prog_displ(x2) * MOVE_Y), vec2(1, 1),
        tint4(0.4, 0.4, 0.4, prog_alpha(x2))
      );
    }
  }
};

scene *scene_text(int entry_id) {
  return new class scene_text(entry_id);
}
