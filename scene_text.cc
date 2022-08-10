#include "main.hh"

#include <cstdio>

struct entry {
  const char *_text[2];
  union {
    const char *image;
    int puzzle;
  };
  entry(const char *text, const char *image = NULL)
    : _text{text, text}, image(image)
    { }
  entry(const char *text1, const char *text2, const char *image)
    : _text{text1, text2}, image(image)
    { }
  entry(int puzzle)
    : _text{NULL, NULL}, puzzle(puzzle)
    { }
  inline const char *text() const { return _(_text[0], _text[1]); }
};

#define _(...) __VA_ARGS__

static entry script[] = {
  // 0
  entry(_("Here we are,\nthe Magical Forest of Yonder.",
          "我们到了！这里是彼岸仙林。"),
        "avatar_intro"),
  entry(_("Where is Nana?\nIs she in this forest?",
          "奈奈在哪儿呀？在这片森林里吗？"),
        "avatar_question"),
  entry(_("We won't see her, but we can\nlet her know that we've come.",
          "我们在这里见不到她，\n不过有办法让她知道我们来啦。"),
        "avatar_intro"),
  entry(_("...", "……"), "avatar_question"),
  entry(_("Here, let the fireflies tell you.",
          "来这儿，看看萤火虫就知道了。"),
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
  entry(_("Nana! It's me!",
          "奈奈！是我呀！"),
        "avatar_lantern"),
  entry(_("How is your life there?",
          "你在那边过得怎么样呀？"),
        "avatar_bellflowers"),
  entry(_("We miss you so much!",
          "我们可太想你啦！"),
        "avatar_lantern"),
  entry(4),
  entry(-1),

  // 15
  entry("", "avatar_rain"),
  entry(_("Nana does not want to see you sad.",
          "奈奈看到你那么难过，也会伤心的吧。"),
        "avatar_bedside"),
  entry(_("You might meet her in the dreams.",
          "说不定你能在梦里见到她呢。"),
        "avatar_intro"),
  entry(_("Nighty-night.",
          "晚安宝贝。"),
        "avatar_night"),
  entry(10),

  // 20
  entry(_("Nana, if you can hear me...",
          "奈奈如果你能听得见这些的话……"),
        "avatar_bush"),
  entry(_("... please let your wild friend come to me.",
          "……就请让你的野生朋友出来吧。"),
        "avatar_oracle"),
  entry(_("...",
          "……"),
        "avatar_bush"),
  entry(_("...",
          "……"),
        "avatar_oracle"),
  entry(_("...",
          "……"),
        "avatar_bush"),
  entry(_("Maybe I should finally stop daydreaming like this.",
          "我是不是真的该从这种幻想里醒醒了。"),
        "avatar_oracle"),
  entry(15),

  // 27
  entry(_("...?!",
          "……？！"),
        "avatar_cat"),
  entry(_("Nana, we can't give you treats any more...",
          "奈奈，我们没法再给你小鱼干了……"),
        "avatar_lantern"),
  entry(_("Remember to take care of yourself!",
          "记得一定照顾好自己呀！"),
        "avatar_bellflowers"),
  entry(_("Alice?! Is that you, Alice?!",
          "爱莉丝？！是你吗，爱莉丝？！"),
        "avatar_cat"),
  entry(_("We love you always...!",
          "我们一直一直爱你……！"),
        "avatar_lantern"),
  entry("", "avatar_cat"),
  entry("", "avatar_lantern"),
  entry("", "avatar_night"),
  entry(-2),
};

#undef _

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
    // Not ending, enough time, and not an entry for a puzzle
    if (script[entry_id].puzzle != -2 && since_change >= 180 &&
      !(script[entry_id].text() == NULL && script[entry_id].puzzle >= 0)) {
      entry_id++;
      since_change = 0;
    }
  }

  void update() {
    since_change++;
    if (script[entry_id].text() == NULL &&
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
      if (entry_id > 0 && script[entry_id - 1].text() != NULL) {
        last_alpha = (x < 0.4 ? cub(1 - x / 0.4) : 0);
      }
      displacement = prog_displ(x);
    }

    if (last_alpha > 0) {
      if (script[entry_id - 1].image != NULL)
        painter::image(
          script[entry_id - 1].image,
          vec2(W * 0.5, H *
            (empty(script[entry_id - 1].text()) ? 0.57 : 0.47)),
          vec2(0.5, 1), vec2(1, 1),
          tint4(1, 1, 1, last_alpha)
        );
      painter::text(
        script[entry_id - 1].text(), 32,
        vec2(W * 0.5, H * 0.53 + (-1 + displacement) * MOVE_Y), vec2(0.5, 0),
        tint4(0.9, 0.9, 0.9, last_alpha)
      );
    }
    if (script[entry_id].text() != NULL) {
      if (script[entry_id].image != NULL)
        painter::image(
          script[entry_id].image,
          vec2(W * 0.5, H *
            (empty(script[entry_id].text()) ? 0.57 : 0.47)),
          vec2(0.5, 1), vec2(1, 1),
          tint4(1, 1, 1, cur_alpha)
        );
      painter::text(
        script[entry_id].text(), 32,
        vec2(W * 0.5, H * 0.53 + displacement * MOVE_Y), vec2(0.5, 0),
        tint4(0.9, 0.9, 0.9, cur_alpha)
      );
    } else if (script[entry_id].puzzle == -2) {
      painter::text(
        _("Fireflies in Forest Flowers",
          "流萤花语"), 32,
        vec2(W * 0.5, H * 0.49 + displacement * MOVE_Y - 24), vec2(0.5, 0),
        tint4(0.9, 0.9, 0.9, cur_alpha)
      );
      painter::text(
        _("-   The End   -",
          "-   终   -"), 32,
        vec2(W * 0.5, H * 0.49 + displacement * MOVE_Y + 24), vec2(0.5, 0),
        tint4(0.9, 0.9, 0.9, cur_alpha)
      );
      float x1 = (float)(since_change - 480) / 240;
      float x2 = (float)(since_change - 505) / 240;
      float x3 = (float)(since_change - 520) / 240;
      x1 = (x1 > 1 ? 1 : x1 < 0 ? 0 : x1);
      x2 = (x2 > 1 ? 1 : x2 < 0 ? 0 : x2);
      x3 = (x3 > 1 ? 1 : x3 < 0 ? 0 : x3);
      painter::text(
        _("Thanks for playing!", "谢谢玩到这里！比心~"), 24,
        vec2(W - 16, H - 72 + prog_displ(x1) * MOVE_Y), vec2(1, 1),
        tint4(0.6, 0.6, 0.6, prog_alpha(x1))
      );
      painter::text(
        "Ayu  2022.01-08", 24,
        vec2(W - 16, H - 44 + prog_displ(x2) * MOVE_Y), vec2(1, 1),
        tint4(0.4, 0.4, 0.4, prog_alpha(x2))
      );
      painter::text(
        _("Dedicated to our piebald cat", "献给我们的黑白花猫"), 24,
        vec2(W - 16, H - 16 + prog_displ(x3) * MOVE_Y), vec2(1, 1),
        tint4(0.3, 0.3, 0.3, prog_alpha(x3))
      );
    }
  }
};

scene *scene_text(int entry_id) {
  return new class scene_text(entry_id);
}
