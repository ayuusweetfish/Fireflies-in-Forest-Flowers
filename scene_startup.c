#include <stdbool.h>

int `count;
bool `c2[3];

int some_fn() {
  return 100;
}

void `init() {
  `count = some_fn();
}

void `pton(float x, float y) {
}

void `ptmove(float x, float y) {
}

void `update() {
  `count++;
}

void `draw() {
  ClearBackground(WHITE);
  char s[32];
  snprintf(s, sizeof s, "%d", `count);
  DrawText(s, W / 2, H / 2, 30, BLACK);
}
