#ifndef _main_hh_
#define _main_hh_

namespace rl {
#include "raylib.h"
}
#include <cmath>

static const int W = 800;
static const int H = 500;

// Scenes

class scene {
public:
  virtual void update() {}
  virtual void draw() {}
  virtual void pton(float, float) {}
  virtual void ptmove(float, float) {}
  virtual void ptoff(float, float) {}
  virtual ~scene() { }
};

scene *scene_startup();
scene *scene_text(int text_id);
scene *scene_game(int level_id);

void replace_scene(scene *s);

// Maths

#ifndef M_PI
#define M_PI 3.14159265358979323846
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
  inline vec2 operator * (const vec2 &b) const { return vec2(x * b.x, y * b.y); }
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

// Painter

class painter {
public:
  static void init();
  static void text(
    const char *s, int size,
    vec2 pos, vec2 anchor,
    tint4 tint);
  static void image(
    const char *name,
    vec2 pos,
    tint4 tint);
  static void image(
    const char *name,
    vec2 pos, vec2 dims,
    tint4 tint);
  static void image(
    const char *name,
    vec2 pos, vec2 anchor, vec2 scale,
    tint4 tint);
  static void image(
    const char *name,
    vec2 pos, vec2 dims,
    vec2 src_pos, vec2 src_dims,
    vec2 anchor, float rot,
    tint4 tint);
};

// Particle system

struct psys {
  int num, cap;
  int spawn_intv;
  int dur_min, dur_max;
  float off_min, off_max;
  float vel_min, vel_max;
  float fre_min, fre_max; // Period
  float amp_min, amp_max;
  unsigned seed;

  struct particle {
    int dur, age;
    float off, phs, vel, fre, amp;
    inline vec2 pos() const {
      return vec2(vel * age, off + sinf((phs + age / fre) * (2 * M_PI)) * amp);
    }
    inline float faint() const { return (float)(dur - age) / dur; }
    inline float faint(int fade_in) const {
      float f = faint();
      if (age >= fade_in) return f;
      float x = (float)age / fade_in;
      return f * (1 - (1 - x) * (1 - x) * (1 - x));
    }
  };
  particle *particles;

  psys(
    int cap,
    float spawn_intv,
    float dur_min, float dur_max,
    float off_min, float off_max,
    float vel_min, float vel_max,
    float fre_min, float fre_max,
    float amp_min, float amp_max,
    unsigned seed);
  ~psys();
  void update();
};

#endif
