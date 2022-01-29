#include "main.hh"

#include <cstdio>

class scene_startup : public scene {
public:
  // Particle system
  psys ps_fireflies;

  rl::Texture2D tex_glow;
  rl::RenderTexture2D render[2];

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
    )
  {
    tex_glow = rl::LoadTexture("res/intro_glow.png");
    rl::GenTextureMipmaps(&tex_glow);
    rl::SetTextureFilter(tex_glow, rl::TEXTURE_FILTER_BILINEAR);
  }

  ~scene_startup() {
    rl::UnloadTexture(tex_glow);
  }

  void ptoff(float x, float y) {
    replace_scene(scene_text(0));
  }

  void update() {
    ps_fireflies.update();
  }

  void draw() {
    using namespace rl;
    painter::image("intro_bg", vec2(0, 0), tint4(1, 1, 1, 1));
    painter::text("Fireflies, Flowers", 60,
      vec2(40, 40), vec2(0, 0),
      tint4(0.9, 0.9, 0.9, 1));

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
  }
};

scene *scene_startup() {
  return new class scene_startup();
}
