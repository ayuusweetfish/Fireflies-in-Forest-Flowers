#include "main.hh"
#include "utils.hh"
using namespace rl;

#include <cstdio>
#include <cstring>
#include <map>

static std::map<hash_t, Sound> sounds;

static inline void load_sound(const char *name)
{
  hash_t h = hash(name);
  if (sounds.count(h) > 0) {
    puts("Collision!");
    return;
  }

  size_t l = strlen(name) + 9;
  char *path = new char[l];
  snprintf(path, l, "res/%s.ogg", name);
  Sound snd = LoadSound(path);
  delete[] path;
  sounds[h] = snd;
}

void sound::init()
{
  load_sound("bellflower_pop_ord");
  load_sound("bellflower_pop_zero_0");
  load_sound("bellflower_pop_zero_1");
  load_sound("bellflower_pop_zero_2");
  load_sound("bellflower_pop_zero_3");
  load_sound("bellflower_pop_zero_4");
  load_sound("puzzle_solved");
  load_sound("hint");
}

void sound::play(const char *name, float pan)
{
  auto p = sounds.find(hash(name));
  if (p == sounds.end()) {
    puts("Unknown sound");
    return;
  }
  // Raylib 4.1 ensures that each instance has its own panning value
  SetSoundPan(p->second, pan);
  PlaySoundMulti(p->second);
}

float sound::bellflowers_pan(float x, float x_min, float x_max)
{
  if (fabs(x_min - x_max) < 1e-4) return 0.5;
  float span = (x_max - x_min) / 5;
  if (span > 1) span = 1;
  span *= 0.4;
  return 0.5 - ((x - x_min) / (x_max - x_min) - 0.5) * span;
}

const char *sound::bellflower_pop_zero(int cur, int total)
{
  static char name[] = "bellflower_pop_zero_?";
  size_t len = strlen(name);
  static const char table[4][4] = {
    {1},
    {1, 3},
    {1, 2, 4},
    {1, 2, 3, 4},
  };
  name[len - 1] = '0' + table[total - 1][cur - 1];
  return (const char *)name;
}
