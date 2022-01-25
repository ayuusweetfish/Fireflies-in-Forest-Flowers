#include <stdbool.h>

int `count;
float `p[2];

int some_fn() {
  return 100;
}

void `init() {
  `count = some_fn();
  `p[0] = -1;
  `p[1] = -1;
}

void `ptoff(float x, float y) {
  `p[0] = -1;
}

void `ptmove(float x, float y) {
  `p[0] = x;
  `p[1] = y;
}

void `update() {
  `count++;
}

void `draw() {
  ClearBackground(WHITE);
  char s[32];
  snprintf(s, sizeof s, "%f %f | %d", `p[0], `p[1], `count);
  DrawText(s, 10, H / 2, 30, BLACK);
}
