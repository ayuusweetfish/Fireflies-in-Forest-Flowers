#ifndef _utils_hh_
#define _utils_hh_

#include "main.hh"

#include <functional>
#include <vector>

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

struct button_group {
  struct button {
    vec2 pos, size;
    const char *content;
    std::function<void ()> fn;
  };
  std::vector<button> buttons;

  button *sel_button = nullptr;
  bool cur_in;

  void draw(
    tint4 tint = tint4(1, 1, 1, 1),
    int text_size = 36,
    vec2 text_anchor = vec2(0.5, 0.5));
  bool pton(float, float);
  bool ptmove(float, float);
  bool ptoff(float, float);
};

#endif
