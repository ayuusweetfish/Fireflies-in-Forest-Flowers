#include "main.hh"

#include <cmath>
#include <cstdio>
#include <utility>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_TAU
#define M_TAU 6.28318530717958647692
#endif

struct vec2 {
  float x, y;
  vec2(float x = 0, float y = 0) : x(x), y(y) { }
  inline vec2 operator + (const vec2 &b) const { return vec2(x + b.x, y + b.y); }
  inline vec2 operator - (const vec2 &b) const { return vec2(x - b.x, y - b.y); }
  inline vec2 operator - () const { return vec2(-x, -y); }
  inline vec2 operator * (const float k) const { return vec2(x * k, y * k); }
  inline vec2 operator / (const float k) const { return vec2(x / k, y / k); }
  inline float dot(const vec2 &b) const { return x * b.x + y * b.y; }
  inline float det(const vec2 &b) const { return x * b.y - y * b.x; }
  inline vec2 rot(const float a) const {
    float sin_a = sinf(a), cos_a = cosf(a);
    return vec2(x * cos_a - y * sin_a, x * sin_a + y * cos_a);
  }
  inline float norm() const { return sqrtf(x * x + y * y); }
};

static inline bool seg_intxn(
  const vec2 a, const vec2 b,
  const vec2 c, const vec2 d
) {
  return (c - a).det(b - a) * (d - a).det(b - a) <= 0 &&
         (a - c).det(d - c) * (b - c).det(d - c) <= 0;
}

class scene_game : public scene {
public:
  // ==== Display-related constants ====
  static constexpr float BOARD_W = 20;
  static constexpr float BOARD_H = 12;
  static constexpr float SCALE = 35;
  static rl::Vector2 scr(vec2 p) {
    vec2 q = p * SCALE + vec2(W, H) / 2;
    return (rl::Vector2){q.x, q.y};
  }
  static vec2 board(float x, float y) {
    return (vec2(x, y) - vec2(W, H) / 2) / SCALE;
  }

  // ==== Tracks ====
  struct track {
    vec2 o;
    float len;  // Total length in units
    enum {
      ATTRACT = (1 << 0),
      RETURN = (1 << 1),
      COLLI = ATTRACT | RETURN,
      FIXED = (1 << 4),
    };
    unsigned flags;

    bool sel;   // Is selected

    track() { }
    track(vec2 o, float len, float flags)
      : o(o), len(len),
        flags(flags),
        sel(false)
      { }
    // Local position at given phase
    virtual vec2 local_at(float t) const = 0;
    vec2 at(float t) const { return local_at(t) + o; }
    // Phase of nearest point on path, given a local point
    // Returns <phase, distance>
    virtual std::pair<float, float> local_nearest(vec2 p) const = 0;
    std::pair<float, float> nearest(vec2 p) const { return local_nearest(p - o); }

    virtual void draw() const = 0;
  };

  struct track_cir : public track {
    float r;  // Radius
    track_cir(vec2 o, float r, unsigned flags = 0)
      : r(r),
        track(o, 2 * M_PI * r, flags)
      { }
    vec2 local_at(float t) const { return vec2(r, 0).rot(t / r); }
    std::pair<float, float> local_nearest(vec2 p) const {
      float a = atan2f(p.y, p.x);
      if (a < 0) a += 2 * M_PI;
      return {a * r, (p - vec2(r, 0).rot(a)).norm()};
    }
    void draw() const {
      using namespace rl;
      // DrawCircleV(scr(o), 3, GRAY);
      DrawRing(scr(o), r * SCALE - 1, r * SCALE + 1, 0, 360, 48,
        sel ? RED :
        (flags & ATTRACT) ? YELLOW :
        (flags & RETURN) ? ORANGE : GRAY);
    }
  };

  struct track_seg : public track {
    vec2 ext; // Extension on both sides
    track_seg(vec2 o, vec2 ext, unsigned flags = 0)
      : ext(ext / ext.norm()),
        track(o, ext.norm() * 2, flags)
      { }
    vec2 local_at(float t) const { return ext * (t - len / 2); }
    std::pair<float, float> local_nearest(vec2 p) const {
      float t = p.dot(ext);
      t = (t < -len / 2 ? -len / 2 : (t > len / 2 ? len / 2 : t));
      return {t + len / 2, (p - (ext * t)).norm()};
    }
    void draw() const {
      using namespace rl;
      DrawLineEx(
        scr(o - ext * len / 2), scr(o + ext * len / 2),
        2,
        sel ? RED :
        (flags & ATTRACT) ? YELLOW :
        (flags & RETURN) ? ORANGE : GRAY);
    }
  };

  // ==== Fireflies ===
  struct firefly {
    // Position (track + phase)
    const track *tr;
    float t;
    inline vec2 pos() const { return tr->at(t); }
    float v;    // Velocity
    bool sel;   // Selected?

    firefly(const track *tr, float t, float v)
      : tr(tr), t(t), v(v),
        sel(false)
      { }

    inline void update(const std::vector<track *> &tracks) {
      float t_prev = t;
      vec2 p1 = pos();
      t += v / 480;
      if (t >= tr->len) t -= tr->len;
      if (t < 0) t += tr->len;
      vec2 p2 = pos();

      // Attracting tracks
      for (const auto tr : tracks) if (tr != this->tr && (tr->flags & track::COLLI)) {
        auto near = tr->nearest(p1);
        if (near.second >= 0.01) continue;
        float t1 = near.first;
        float t2 = tr->nearest(p2).first;
        if (fabs(t1 - t2) < 1e-6) {
          float d = (t1 < 1 ? 1e-6 : (t1 * 1e-6));
          t1 -= d;
          t2 += d;
        }
        // Lemma: (p1, p2) crosses the curve C iff
        // (p1, p2) crosses (C(t1), C(t2))
        if (seg_intxn(p1, p2, tr->at(t1), tr->at(t2))) {
          // Point of intersection
          // XXX: Find the intersection with the curve with ternary search?
          float ti = (t1 + t2) / 2;
          if (tr->flags & track::ATTRACT) {
            // Move to the new track
            this->tr = tr;
            this->t = ti;
            // Reverse if making acute turns
            if (this->v * (t2 - t1) < 0) this->v = -this->v;
          }
          if (tr->flags & track::RETURN) {
          /*
            printf("p1 = (%f, %f)\n", p1.x, p1.y);
            printf("p2 = (%f, %f)\n", p2.x, p2.y);
            printf("tr->at(t1) = (%f, %f)\n", tr->at(t1).x, tr->at(t1).y);
            printf("tr->at(t2) = (%f, %f)\n", tr->at(t2).x, tr->at(t2).y);
          */
            this->t = t_prev;
            this->v = -this->v;
          }
          break;
        }
      }
    }
    inline void draw() const {
      using namespace rl;
      DrawCircleV(scr(pos()), 4, sel ? RED : YELLOW);
    }
  };

  // ==== Bellflowers ====
  struct bellflower {
    vec2 o;
    float r;
    int c0, c;  // Initial count and current count

    bellflower(vec2 o, float r, int c0)
      : o(o), r(r), c0(c0)
    {
      reset();
    }

    bool last_on;
    virtual void reset() {
      last_on = false;
      c = c0;
    }
    void update(bool on) {
      if (!last_on && on) c--;
      last_on = on;
    }
    virtual void update(const std::vector<firefly> &fireflies) = 0;
    virtual void draw() const = 0;

    inline bool fireflies_within(const std::vector<firefly> &fireflies) {
      for (const auto f : fireflies)
        if ((f.pos() - o).norm() <= r) return true;
      return false;
    }
  };

  struct bellflower_ord : public bellflower {
    bellflower_ord(vec2 o, float r, int c0)
      : bellflower(o, r, c0)
      { }
    void update(const std::vector<firefly> &fireflies) {
      bool on = fireflies_within(fireflies);
      bellflower::update(on);
    }
    void draw() const {
      using namespace rl;
      DrawCircleV(scr(o), r * SCALE, (Color){64, 64, 64, 128});
      DrawCircleV(scr(o), 0.5 * SCALE, last_on ? GREEN : GRAY);
      char s[8];
      snprintf(s, sizeof s, "%d", c);
      DrawText(s, scr(o).x - 4, scr(o).y - 8, 16, BLACK);
    }
  };

  struct bellflower_delay : public bellflower {
    int d, d0;
    bellflower_delay(vec2 o, float r, int c0, float d0)
      : bellflower(o, r, c0), d0(d0 * 480)
      { reset(); }
    void reset() {
      bellflower::reset();
      d = d0;
    }
    void update(const std::vector<firefly> &fireflies) {
      bool on = fireflies_within(fireflies);
      if (on) {
        if (d > 0) d--;
      } else {
        d = d0;
      }
      bellflower::update(d == 0);
    }
    void draw() const {
      using namespace rl;
      DrawCircleV(scr(o), r * SCALE, (Color){64, 64, 64, 128});
      DrawCircleV(scr(o), 0.5 * SCALE, GRAY);
      DrawCircleV(scr(o), 0.5 * SCALE * (d0 - d) / d0, GREEN);
      char s[8];
      snprintf(s, sizeof s, "%d", c);
      DrawText(s, scr(o).x - 4, scr(o).y - 8, 16, BLACK);
    }
  };

  // ==== Scene ====
  const char *level_title;
  std::vector<track *> tracks;
  std::vector<firefly> fireflies, fireflies_init;
  std::vector<bellflower *> bellflowers;
  std::vector<std::vector<std::pair<firefly *, float>>> ff_links;

  firefly *sel_ff;
  track *sel_track;
  vec2 sel_offs;
  int run_state = 0;

  const float RT_SCALE = 2; // Scaling factor for render targets
  rl::RenderTexture2D texBloomBase, texBloomStage1, texBloomStage2;
  rl::Shader shaderBloom;
  int shaderBloomPassLoc;

  scene_game(int puzzle_id)
    : sel_ff(nullptr), sel_track(nullptr)
  {
    std::vector<std::vector<int>> links;
    switch (puzzle_id) {
      #define T_cir   new track_cir
      #define T_seg   new track_seg
      #define B_ord   new bellflower_ord
      #define B_delay new bellflower_delay
      #define F(_i, _t, ...) \
        firefly(tracks[_i], tracks[_i]->len * (_t), __VA_ARGS__)
      #include "puzzles.hh"
    }
    build_links(links);

    texBloomBase = rl::LoadRenderTexture(W * RT_SCALE, H * RT_SCALE);
    rl::SetTextureFilter(texBloomBase.texture, rl::TEXTURE_FILTER_BILINEAR);
    texBloomStage1 = rl::LoadRenderTexture(W * RT_SCALE, H * RT_SCALE);
    rl::SetTextureFilter(texBloomStage1.texture, rl::TEXTURE_FILTER_BILINEAR);
    texBloomStage2 = rl::LoadRenderTexture(W, H);
    rl::SetTextureFilter(texBloomStage2.texture, rl::TEXTURE_FILTER_BILINEAR);
  #ifdef PLATFORM_WEB
    shaderBloom = rl::LoadShader("res/bloom_web.vert", "res/bloom_web.frag");
  #else
    shaderBloom = rl::LoadShader("res/bloom.vert", "res/bloom.frag");
  #endif
    shaderBloomPassLoc = rl::GetShaderLocation(shaderBloom, "pass");
  }

  inline void build_links(std::vector<std::vector<int>> links) {
    ff_links.clear();
    ff_links.resize(fireflies.size());
    for (const auto group : links) {
      for (const auto indep : group) {
        auto &list = ff_links[indep];
        float t = fireflies[indep].t;
        list.reserve(group.size() - 1);
        for (const auto dep : group) if (dep != indep)
          list.push_back({&fireflies[dep], fireflies[dep].t - t});
      }
    }
  }

  inline std::pair<firefly *, track *> find(const vec2 p) {
    // Find the nearest firefly
    firefly *best_ff = nullptr;
    float best_dist = 0.75;
    for (auto &f : fireflies) {
      float dist = (p - f.pos()).norm();
      if (dist < best_dist) {
        best_dist = dist;
        best_ff = &f;
      }
    }
    if (best_ff != nullptr) return {best_ff, nullptr};

    // Find the nearest firefly track
    track *best_track = nullptr;
    std::pair<float, float> best_result = {0, 0.5};
    for (const auto t : tracks) if (!(t->flags & track::FIXED)) {
      auto result = t->nearest(p);
      if (result.second < best_result.second) {
        best_result = result;
        best_track = t;
      }
    }
    return {nullptr, best_track};
  }

  void pton(float x, float y) {
    if (run_state & 1) return;
    vec2 p = board(x, y);

    auto near = find(p);
    if (near.first != nullptr) {
      sel_ff = near.first;
      sel_ff->sel = true;
      sel_offs = sel_ff->pos() - p;
    }
    if (near.second != nullptr) {
      sel_track = near.second;
      sel_track->sel = true;
      sel_offs = sel_track->o - p;
    }
  }

  void ptmove(float x, float y) {
    vec2 p = board(x, y);
    if (sel_ff != nullptr) {
      sel_ff->t = sel_ff->tr->nearest(p + sel_offs).first;
      // Move linked fireflies
      int index = sel_ff - &fireflies[0];
      for (const auto link : ff_links[index])
        link.first->t = sel_ff->t + link.second;
    }
    if (sel_track != nullptr) {
      sel_track->o = p + sel_offs;
    }
  }

  void ptoff(float x, float y) {
    if (sel_ff != nullptr) {
      sel_ff->sel = false;
      sel_ff = nullptr;
    }
    if (sel_track != nullptr) {
      sel_track->sel = false;
      sel_track = nullptr;
    }
  }

  inline void start_run() {
    // Save
    fireflies_init = fireflies;
  }
  inline void stop_run() {
    fireflies = fireflies_init;
    for (auto b : bellflowers) b->reset();
  }

  bool last_space_down = false;
  void update() {
    bool space_down = rl::IsKeyDown(rl::KEY_SPACE);
    if (sel_track == nullptr && !last_space_down && space_down) {
      run_state ^= 1;
      if (run_state & 1) start_run(); else stop_run();
    }
    last_space_down = space_down;
    run_state = (run_state & 1) |
      ((rl::IsKeyDown(rl::KEY_GRAVE) ? 1 :
        rl::IsKeyDown(rl::KEY_ONE) ? 16 : 4) << 1);
    if (run_state & 1) for (int i = 0; i < (run_state >> 1); i++) {
      for (auto &f : fireflies) f.update(tracks);
      for (auto b : bellflowers) b->update(fireflies);
    }
  }

  void draw() {
    using namespace rl;

    ClearBackground(BLACK);
    int x_range = (W / 2 / SCALE) + 1;
    for (int i = -x_range; i <= x_range; i++) {
      float x = scr(vec2(i, 0)).x;
      DrawLineV((Vector2){x, 0}, (Vector2){x, H}, (Color){30, 30, 30, 255});
    }
    int y_range = (H / 2 / SCALE) + 1;
    for (int i = -y_range; i <= y_range; i++) {
      float y = scr(vec2(0, i)).y;
      DrawLineV((Vector2){0, y}, (Vector2){W, y}, (Color){30, 30, 30, 255});
    }

    // Render scaled to texture
    BeginBlendMode(BLEND_ADD_COLORS);

    Color bg = (Color){0, 0, 0, 0};
    BeginTextureMode(texBloomBase);
    BeginMode2D((Camera2D){(Vector2){0, 0}, (Vector2){0, 0}, 0, RT_SCALE});
      ClearBackground(bg);
      for (const auto t : tracks) t->draw();
      for (const auto &f : fireflies) f.draw();
      // DrawRectangle(0, 0, 100, 100, (Color){255, 255, 255, 128});
    EndMode2D();
    EndTextureMode();
    //GenTextureMipmaps(&texBloomBase.texture);

    int pass;
    BeginTextureMode(texBloomStage1);
    BeginMode2D((Camera2D){(Vector2){0, 0}, (Vector2){0, 0}, 0, RT_SCALE});
    pass = 1;
    SetShaderValue(shaderBloom, shaderBloomPassLoc, &pass, SHADER_UNIFORM_INT);
    BeginShaderMode(shaderBloom);
      ClearBackground(bg);
      DrawTexturePro(texBloomBase.texture,
        (Rectangle){0, 0, W * RT_SCALE, -H * RT_SCALE},
        (Rectangle){0, 0, W, H},
        (Vector2){0, 0}, 0, WHITE);
    EndShaderMode();
    EndMode2D();
    EndTextureMode();
    //GenTextureMipmaps(&texBloomStage1.texture);

    BeginTextureMode(texBloomStage2);
    pass = 2;
    SetShaderValue(shaderBloom, shaderBloomPassLoc, &pass, SHADER_UNIFORM_INT);
    BeginShaderMode(shaderBloom);
      ClearBackground(bg);
      DrawTexturePro(texBloomStage1.texture,
        (Rectangle){0, 0, W * RT_SCALE, -H * RT_SCALE},
        (Rectangle){0, 0, W, H},
        (Vector2){0, 0}, 0, WHITE);
    EndShaderMode();
    EndTextureMode();

    EndBlendMode();

    DrawTexturePro(texBloomBase.texture,
      (Rectangle){0, 0, W * RT_SCALE, -H * RT_SCALE},
      (Rectangle){0, 0, W, H},
      (Vector2){0, 0}, 0, (Color){255, 255, 255, 160});
    DrawTexturePro(texBloomStage2.texture,
      (Rectangle){0, 0, W, -H},
      (Rectangle){0, 0, W, H},
      (Vector2){0, 0}, 0, WHITE);

    for (const auto b : bellflowers) b->draw();
    DrawTextEx(
      GetFontDefault(),
      level_title,
      (Vector2){20, H - 40},
      32, 3, WHITE);
  }
};

scene *scene_game(int level_id) {
  return new class scene_game(level_id);
}
