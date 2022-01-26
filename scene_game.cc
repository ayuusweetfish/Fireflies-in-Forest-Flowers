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
  inline float dot(const vec2 &b) const { return x * b.x + y * b.y; }
  inline float det(const vec2 &b) const { return x * b.y - y * b.x; }
  inline vec2 rot(const float a) const {
    float sin_a = sinf(a), cos_a = cosf(a);
    return vec2(x * cos_a - y * sin_a, x * sin_a + y * cos_a);
  }
  inline float norm() const { return sqrtf(x * x + y * y); }
  inline rl::Vector2 rl() const { return (rl::Vector2){x, y}; }
};

class scene_game : public scene {
public:
  struct firefly {
    vec2 o;
    float T;  // Period
    firefly() { }
    firefly(vec2 o, float T) : o(o), T(T) { }
    // Local position at given phase
    virtual vec2 at(float t) const = 0;
    // Phase of nearest point on path, given a local point
    // Returns <phase, distance>
    virtual std::pair<float, float> nearest(vec2 p) const = 0;
    virtual void draw() const = 0;
  };

  static constexpr float SCALE = 35;

  struct firefly_cir : public firefly {
    float r, v; // Radius and velocity
    firefly_cir(vec2 o, float r, float v)
      : r(r), v(v),
        firefly(o, 2 * M_PI * r / v)
    { }
    vec2 at(float t) const { return vec2(1, 0).rot(t / (2 * M_PI)); }
    std::pair<float, float> nearest(vec2 p) const {
      float a = atan2f(p.y, p.x);
      if (a < 0) a += 2 * M_PI;
      return {a / (2 * M_PI), (p - vec2(1, 0).rot(a)).norm()};
    }
    void draw() const {
      using namespace rl;
      DrawCircleV((o * SCALE).rl(), 3, WHITE);
      DrawRing((o * SCALE).rl(), r * SCALE - 2, r * SCALE + 2, 0, 360, 48, WHITE);
    }
  };

  std::vector<firefly *> fireflies;

  scene_game() {
    fireflies.push_back(new firefly_cir(vec2(4, 3), 2, 1));
    fireflies.push_back(new firefly_cir(vec2(6, 5), 3, 1));
  }

  void draw() {
    using namespace rl;
    ClearBackground(BLACK);
    for (const auto f : fireflies) f->draw();
  }
};

scene *scene_game() {
  return new class scene_game();
}
