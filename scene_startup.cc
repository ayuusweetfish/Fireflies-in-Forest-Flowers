#include "main.hh"
#include "utils.hh"

#include <cstdio>

class scene_startup : public scene {
public:
  // Particle system
  psys ps_fireflies;

  rl::Texture2D tex_glow;
  rl::RenderTexture2D render[2];

  int hold_time;

  // Puzzle selection
  struct puzzle_sel {
    button_group btns;
    char *s;

    bool pt_captured;

    int T;
    bool entering;
    const int T_MAX = 120;

    puzzle_sel() : T(0), pt_captured(false) {
      s = new char[3 * 21];
      for (int i = 0; i <= 20; i++) {
        s[i * 3 + 0] = '0' + i / 10;
        s[i * 3 + 1] = '0' + i % 10;
        s[i * 3 + 2] = 0;
        btns.buttons.push_back((button_group::button){
          vec2((W - 90 * 7) / 2 + 90 * (i % 7), H * 0.32 + 90 * (i / 7)),
          vec2(90, 90),
          &s[i * 3],
          [this, i]() { replace_scene(scene_game(i)); }
        });
      }
    }

    ~puzzle_sel() {
      delete[] s;
    }

    bool pton(float x, float y) {
      if (T == 0 || (T < T_MAX && !entering)) return false;
      if (btns.pton(x, y)) return true;
      pt_captured = true;
      return true;
    }

    bool ptmove(float x, float y) {
      if (T == 0 || (T < T_MAX && !entering)) return false;
      if (btns.ptmove(x, y)) return true;
      return true;
    }

    bool ptoff(float x, float y) {
      if (T == 0 || (T < T_MAX && !entering)) return false;
      if (btns.ptoff(x, y)) return true;
      T--;
      entering = false;
      return true;
    }

    void update() {
      if (T > 0 && T < T_MAX) {
        if (entering) T++; else T--;
      }
    }

    void draw() {
      float x = (float)T / T_MAX;
      if (entering) x = 1 - (1 - x) * (1 - x) * (1 - x);
      else x = x * x * x;
      rl::DrawRectangle(0, 0, W, H,
        (rl::Color){16, 16, 16, (unsigned char)(192 * x + 0.5f)});
      painter::text(_("Skip to a puzzle", "跳到谜题"), 36,
        vec2(W / 2, H * 0.21), vec2(0.5, 0.5),
        tint4(1, 1, 1, x));
      btns.draw(tint4(1, 1, 1, x));
    }
  } ps;

  scene_startup()
  : ps_fireflies(
      15,
      2,
      12, 24,
      -100, 20,
      60, 90,
      4, 8,
      30, 55,
      20220129
    ),
    hold_time(-1)
  {
    tex_glow = rl::LoadTexture("res/intro_glow.png");
    rl::GenTextureMipmaps(&tex_glow);
    rl::SetTextureFilter(tex_glow, rl::TEXTURE_FILTER_BILINEAR);
  }

  ~scene_startup() {
    rl::UnloadTexture(tex_glow);
  }

  void pton(float x, float y) {
    if (ps.pton(x, y)) return;
    hold_time = 0;
  }

  void ptmove(float x, float y) {
    if (ps.ptmove(x, y)) return;
  }

  void ptoff(float x, float y) {
    if (hold_time >= 240) {
      hold_time = -1;
      return;
    }
    if (ps.ptoff(x, y)) return;
    hold_time = -1;
    replace_scene(scene_text(0));
  }

  void update() {
    ps_fireflies.update();
    ps.update();
    if (hold_time >= 0) {
      hold_time++;
      if (hold_time == 240) {
        ps.T = 1;
        ps.entering = true;
      }
    }
  }

  void draw() {
    using namespace rl;
    painter::image("intro_bg", vec2(0, 0), tint4(1, 1, 1, 1));
    painter::text(
      _("Fireflies and Forest Flowers",
        "流萤花语"),
      60,
      vec2(40, 60), vec2(0, 0),
      tint4(0.9, 0.9, 0.9, 1));
    painter::text(
      _("Press anywhere to start",
        "点按屏幕开始"),
      32,
      vec2(40, 130), vec2(0, 0),
      tint4(0.9, 0.9, 0.9, 0.4));

    for (int i = 0; i < ps_fireflies.num; i++) {
      auto p = ps_fireflies.particles[i];
      int age = p.age;
      for (int t = (age < 9 * 6 ? age / 6 : 9); t >= 0; t--) {
        p.age = age - t * 6;
        vec2 pos = p.pos();
        vec2 scr = vec2(W * 0.1, H * 1.0) + pos.rot(-0.1 - 0.01 * i);
        float scale = p.faint(240)
          * (1 - (float)t / 9 * 0.6)
          * (0.8 + 0.2 * p.phs) // Use phase as another random parameter
          * 0.5;
        scr = scr - vec2(36, 36) * scale;
        float alpha = (1 - (float)t / 9) * 0.4;
        DrawTextureEx(
          tex_glow,
          (Vector2){scr.x, scr.y},
          0, scale, (Color){255, 255, 255, (unsigned char)(255 * alpha)});
      }
    }

    ps.draw();
  }
};

scene *scene_startup() {
  return new class scene_startup();
}
