#include "raylib.h"
#include "raymath.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int W = 800;
static const int H = 450;

int main(int argc, char *argv[])
{
  InitWindow(W, H, NULL);
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(WHITE);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
