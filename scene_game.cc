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

class scene_game : public scene {
public:
  struct firefly {
    vec2 o;
    float T;  // Period

    float tc;       // Current phase
    float tc0;      // Phase at start
    bool selpath;   // Selected path
    bool selpt;     // Selected lighting point

    firefly() { }
    firefly(vec2 o, float T, float tc)
      : o(o), T(T), tc(tc),
        selpath(false), selpt(false)
      { }
    // Local position at given phase
    virtual vec2 local_at(float t) const = 0;
    vec2 at(float t) const { return local_at(t) + o; }
    vec2 at() const { return at(tc); }
    // Phase of nearest point on path, given a local point
    // Returns <phase, distance>
    virtual std::pair<float, float> local_nearest(vec2 p) const = 0;
    std::pair<float, float> nearest(vec2 p) const { return local_nearest(p - o); }

    virtual void draw() const = 0;
  };

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

  struct firefly_cir : public firefly {
    float r, v; // Radius and velocity
    firefly_cir(vec2 o, float r, float v, float tc)
      : r(r), v(v),
        firefly(o, 2 * M_PI * r / v, tc)
      { }
    vec2 local_at(float t) const { return vec2(r, 0).rot(t * (2 * M_PI)); }
    std::pair<float, float> local_nearest(vec2 p) const {
      float a = atan2f(p.y, p.x);
      if (a < 0) a += 2 * M_PI;
      return {a / (2 * M_PI), (p - vec2(r, 0).rot(a)).norm()};
    }
    void draw() const {
      using namespace rl;
      // DrawCircleV(scr(o), 3, DARKGRAY);
      DrawRing(scr(o), r * SCALE - 2, r * SCALE + 2, 0, 360, 48, selpath ? RED : WHITE);
      DrawCircleV(scr(at()), 4, selpt ? RED : YELLOW);
    }
  };

  std::vector<firefly *> fireflies;

  scene_game() {
    fireflies.push_back(new firefly_cir(vec2(4, 3), 2, 1, 0));
    fireflies.push_back(new firefly_cir(vec2(6, 5), 3, 1, 0.25));
  }

  firefly *sel_ff;
  vec2 sel_offs;
  int run_state = 0;

  void pton(float x, float y) {
    if (run_state & 1) return;
    vec2 p = board(x, y);
    firefly *bestf = nullptr;

    // Find the nearest firefly point
    float bestpt = 0.75;
    for (const auto f : fireflies) {
      float dist = (p - f->at()).norm();
      if (dist < bestpt) {
        bestpt = dist;
        bestf = f;
      }
    }
    if (bestf != nullptr) {
      sel_ff = bestf;
      sel_ff->selpt = true;
      sel_offs = sel_ff->at() - p;
      return;
    }

    // Find the nearest firefly path
    std::pair<float, float> bestpath = {0, 0.5};
    for (const auto f : fireflies) {
      auto result = f->nearest(p);
      if (result.second < bestpath.second) {
        bestpath = result;
        bestf = f;
      }
    }
    if (bestf != nullptr) {
      sel_ff = bestf;
      sel_ff->selpath = true;
      sel_offs = sel_ff->o - p;
    }
  }

  void ptmove(float x, float y) {
    vec2 p = board(x, y);
    if (sel_ff != nullptr) {
      if (sel_ff->selpath) {
        sel_ff->o = p + sel_offs;
      } else {
        sel_ff->tc = sel_ff->nearest(p + sel_offs).first;
      }
    }
  }

  void ptoff(float x, float y) {
    if (sel_ff != nullptr) {
      sel_ff->selpath = sel_ff->selpt = false;
      sel_ff = nullptr;
    }
  }

  inline void start_run() {
    for (auto f : fireflies) f->tc0 = f->tc;
  }
  inline void stop_run() {
    for (auto f : fireflies) f->tc = f->tc0;
  }

  bool last_space_down = false;
  void update() {
    bool space_down = rl::IsKeyDown(rl::KEY_SPACE);
    if (sel_ff == nullptr && !last_space_down && space_down) {
      run_state ^= 1;
      if (run_state & 1) start_run(); else stop_run();
    }
    last_space_down = space_down;
    if (run_state & 1) {
      for (auto f : fireflies) {
        if ((f->tc += 1 / (240 * f->T)) >= 1)
          f->tc -= 1;
      }
    }
  }

  void draw() {
    using namespace rl;
    ClearBackground(BLACK);
    for (int i = 0; i <= BOARD_W; i++)
      DrawLineV(scr(vec2(i, 0)), scr(vec2(i, BOARD_H)), (Color){48, 48, 48, 255});
    for (int i = 0; i <= BOARD_H; i++)
      DrawLineV(scr(vec2(0, i)), scr(vec2(BOARD_W, i)), (Color){48, 48, 48, 255});
    for (const auto f : fireflies) f->draw();
  }
};

scene *scene_game() {
  return new class scene_game();
}
