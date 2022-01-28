#ifndef _main_hh_
#define _main_hh_

namespace rl {
#include "raylib.h"
}
#include <cmath>

static const int W = 800;
static const int H = 500;

class scene {
public:
  virtual void update() {}
  virtual void draw() {}
  virtual void pton(float, float) {}
  virtual void ptmove(float, float) {}
  virtual void ptoff(float, float) {}
};

scene *scene_startup();
scene *scene_game(int level_id);

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

struct tint4 {
  float r, g, b, a;
  tint4(float r = 0, float g = 0, float b = 0, float a = 1)
    : r(r), g(g), b(b), a(a) { }
};

class painter {
public:
  static void init();
  static void text(
    const char *s, int size,
    vec2 pos, vec2 anchor, float alpha);
  static void image(
    const char *name,
    vec2 pos, vec2 dims,
    tint4 tint);
  static void image(
    const char *name,
    vec2 pos, vec2 dims,
    vec2 src_pos, vec2 src_dims,
    vec2 anchor, float rot,
    tint4 tint);
};

#endif
