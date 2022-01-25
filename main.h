#ifndef _main_h_
#define _main_h_

static const int W = 800;
static const int H = 450;

typedef struct {
  void *data;
  void (*update)(void *);
  void (*draw)(void *);
  void (*pton)(void *, float, float);
  void (*ptmove)(void *, float, float);
  void (*ptoff)(void *, float, float);
} scene;

scene scene_startup_create();

#endif
