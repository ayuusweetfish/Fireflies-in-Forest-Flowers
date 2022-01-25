#include "main.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct D {
  int count;
} D;

static void init(void *_d);
static void update(void *_d);
static void draw(void *_d);

scene scene_startup_create()
{
  D *d = (D *)malloc(sizeof(D));
  init(d);
  return (scene){
    .data = d,
    .update = update,
    .draw = draw,
  };
}

static void init(void *_d) {
  D *d = (D *)_d;
  d->count = 100;
}

static void update(void *_d) {
  D *d = (D *)_d;
  d->count++;
}

#include "raylib.h"

static void draw(void *_d) {
  D *d = (D *)_d;

  ClearBackground(WHITE);
  char s[32];
  snprintf(s, sizeof s, "%d", d->count);
  DrawText(s, W / 2, H / 2, 30, BLACK);
}
