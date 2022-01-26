#include "main.hh"

#include <cmath>
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
  static constexpr float OFFSET_X = W / 2 - BOARD_W / 2 * SCALE;
  static constexpr float OFFSET_Y = H / 2 - BOARD_H / 2 * SCALE;
  static rl::Vector2 scr(vec2 p) {
    vec2 q = p * SCALE + vec2(OFFSET_X, OFFSET_Y);
    return (rl::Vector2){q.x, q.y};
  }
  static vec2 board(float x, float y) {
    return (vec2(x, y) - vec2(OFFSET_X, OFFSET_Y)) / SCALE;
  }

  // ==== Tracks ====
  struct track {
    vec2 o;
    float len;  // Total length in units
    enum {
      ATTRACT = 1,
      RETURN = 2,
    };
    unsigned int colli;

    bool sel;   // Is selected

    track() { }
    track(vec2 o, float len)
      : o(o), len(len),
        colli(0),
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
    track_cir(vec2 o, float r)
      : r(r),
        track(o, 2 * M_PI * r)
      { }
    vec2 local_at(float t) const { return vec2(r, 0).rot(t / r); }
    std::pair<float, float> local_nearest(vec2 p) const {
      float a = atan2f(p.y, p.x);
      if (a < 0) a += 2 * M_PI;
      return {a * r, (p - vec2(r, 0).rot(a)).norm()};
    }
    void draw() const {
      using namespace rl;
      // DrawCircleV(scr(o), 3, DARKGRAY);
      DrawRing(scr(o), r * SCALE - 2, r * SCALE + 2, 0, 360, 48,
        sel ? RED : ((colli & ATTRACT) ? YELLOW : WHITE));
    }
  };

  struct track_seg : public track {
    vec2 ext; // Extension on both sides
    track_seg(vec2 o, vec2 ext)
      : ext(ext / ext.norm()),
        track(o, ext.norm() * 2)
      { }
    vec2 local_at(float t) const { return ext * (t - len / 2); }
    std::pair<float, float> local_nearest(vec2 p) const {
      float t = p.dot(ext);
      t = (t < -len / 2 ? -len / 2 : (t > len / 2 ? len / 2 : t));
      return {t + len / 2, (p - (ext * t)).norm()};
    }
    void draw() const {
      using namespace rl;
      DrawLineV(
        scr(o - ext * len / 2), scr(o + ext * len / 2),
        sel ? RED : ((colli & RETURN) ? ORANGE : WHITE));
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
      t += v / 240;
      if (t >= tr->len) t -= tr->len;
      vec2 p2 = pos();

      // Attracting tracks
      for (const auto tr : tracks) if (tr != this->tr && tr->colli != 0) {
        auto near = tr->nearest(p1);
        if (near.second >= 0.01) continue;
        float t1 = near.first;
        float t2 = tr->nearest(p2).first;
        // Lemma: (p1, p2) crosses the curve C iff
        // (p1, p2) crosses (C(t1), C(t2))
        if (seg_intxn(p1, p2, tr->at(t1), tr->at(t2))) {
          // Point of intersection
          // XXX: Find the intersection with the curve with ternary search?
          float ti = (t1 + t2) / 2;
          if (tr->colli & track::ATTRACT) {
            // Move to the new track
            this->tr = tr;
            this->t = ti;
            // Reverse if making acute turns
            if (this->v * (t2 - t1) < 0) this->v = -this->v;
          }
          if (tr->colli & track::RETURN) {
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
    void reset() {
      last_on = false;
      c = c0;
    }
    void update(bool on) {
      if (!last_on && on) c--;
      last_on = on;
    }
    virtual void update(const std::vector<firefly> &fireflies) = 0;
    virtual void draw() const = 0;
  };

  struct bellflower_ord : public bellflower {
    bellflower_ord(vec2 o, float r, int c0)
      : bellflower(o, r, c0)
      { }
    void update(const std::vector<firefly> &fireflies) {
      bool on = false;
      for (const auto f : fireflies)
        if ((f.pos() - o).norm() <= r) {
          on = true;
          break;
        }
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

  // ==== Scene ====
  std::vector<track *> tracks;
  std::vector<firefly> fireflies, fireflies_init;
  std::vector<bellflower *> bellflowers;

  firefly *sel_ff;
  track *sel_track;
  vec2 sel_offs;
  int run_state = 0;

  scene_game()
    : sel_ff(nullptr), sel_track(nullptr)
  {
    tracks.push_back(new track_cir(vec2(4, 3), 2));
    tracks.push_back(new track_cir(vec2(6, 5), 3));
    tracks.push_back(new track_cir(vec2(10, 5), 3));
    tracks.back()->colli = track::ATTRACT;
    tracks.push_back(new track_seg(vec2(11, 7), vec2(2, 1)));
    tracks.back()->colli = track::RETURN;
    fireflies.push_back(firefly(tracks[0], 0, 1));
    fireflies.push_back(firefly(tracks[1], 0.25, 1));
    bellflowers.push_back(new bellflower_ord(vec2(5, 7), 2, 4));
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
    for (const auto t : tracks) {
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
    if (run_state & 1) {
      for (auto &f : fireflies) f.update(tracks);
      for (auto b : bellflowers) b->update(fireflies);
    }
  }

  void draw() {
    using namespace rl;
    ClearBackground(BLACK);
    for (int i = 0; i <= BOARD_W; i++)
      DrawLineV(scr(vec2(i, 0)), scr(vec2(i, BOARD_H)), (Color){48, 48, 48, 255});
    for (int i = 0; i <= BOARD_H; i++)
      DrawLineV(scr(vec2(0, i)), scr(vec2(BOARD_W, i)), (Color){48, 48, 48, 255});
    for (const auto t : tracks) t->draw();
    for (const auto b : bellflowers) b->draw();
    for (const auto &f : fireflies) f.draw();
  }
};

scene *scene_game() {
  return new class scene_game();
}
