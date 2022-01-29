#include "main.hh"

using particle = psys::particle;

static inline particle spawn(psys &s)
{
  particle p;
  unsigned seed = s.seed;

#define rnd() ( \
  (seed = (seed * 1103515245 + 12345) & 0x7fffffff), \
  ((float)seed / (float)0x7fffffff) \
)
  p.dur = s.dur_min + rnd() * (s.dur_max - s.dur_min);
  p.off = s.off_min + rnd() * (s.off_max - s.off_min);
  p.vel = s.vel_min + rnd() * (s.vel_max - s.vel_min);
  p.fre = s.fre_min + rnd() * (s.fre_max - s.fre_min);
  p.amp = s.amp_min + rnd() * (s.amp_max - s.amp_min);
  p.phs = rnd();
#undef rnd

  p.age = 0;
  s.seed = seed;
  return p;
}

static const int STEPS = 240;

psys::psys(
  int cap,
  float spawn_intv,
  float dur_min, float dur_max,
  float off_min, float off_max,
  float vel_min, float vel_max,
  float fre_min, float fre_max,
  float amp_min, float amp_max,
  unsigned seed)
: num(1), cap(cap),
  spawn_intv(spawn_intv * STEPS),
  dur_min(dur_min * STEPS), dur_max(dur_max * STEPS),
  off_min(off_min), off_max(off_max),
  vel_min(vel_min / STEPS), vel_max(vel_max / STEPS),
  fre_min(fre_min * STEPS), fre_max(fre_max * STEPS),
  amp_min(amp_min), amp_max(amp_max),
  seed(seed),
  particles(new particle[cap])
{
  particles[0] = spawn(*this);
}

psys::~psys()
{
  delete[] particles;
}

void psys::update()
{
  // Starting up?
  // NOTE: This requires that dur_min >= spawn_intv
  if (num < cap && particles[num - 1].age >= spawn_intv) {
    particles[num++] = spawn(*this);
  }

  for (int i = 0; i < num; i++) {
    if (particles[i].age++ >= particles[i].dur) {
      particles[i] = spawn(*this);
    }
  }
}
