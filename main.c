#include "main.h"

#include "raylib.h"
#include "raymath.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static scene cur_scene;

int main(int argc, char *argv[])
{
  InitWindow(W, H, NULL);
  SetTargetFPS(60);

  cur_scene = scene_startup_create();

  while (!WindowShouldClose()) {
    BeginDrawing();

    cur_scene.update(cur_scene.data);
    cur_scene.draw(cur_scene.data);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
