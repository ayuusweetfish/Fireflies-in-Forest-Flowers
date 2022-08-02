#include "main.hh"
using namespace rl;

#include <cstdio>
#include <map>

typedef unsigned long hash_t;

static std::map<int, Font> font;

struct tex_record {
  Texture2D tex;
  int width, height;
};
static std::map<hash_t, tex_record> textures;

static inline hash_t hash(const char *s)
{
  hash_t r = 0;
  for (; *s != '\0'; s++) r = r * 997 + *s;
  return r;
}

static inline void load_tex(const char *name, const char *path)
{
  hash_t h = hash(name);
  if (textures.count(h) > 0) {
    puts("Collision!");
    return;
  }
  Image img = LoadImage(path);
  textures[h] = (tex_record){
    .tex = LoadTextureFromImage(img),
    .width = img.width,
    .height = img.height,
  };
  UnloadImage(img);
}

static inline tex_record tex(const char *name)
{
  auto p = textures.find(hash(name));
  if (p == textures.end()) {
    puts("Unknown texture");
    return (tex_record){};
  }
  return p->second;
}

void painter::init()
{
  for (int size : {24, 32, 36, 60}) {
    // 95 = ASCII range (32 ~ 126)
    font[size] = LoadFontEx("res/Imprima.ttf", size, NULL, 95);
  }
  load_tex("intro_bg", "res/intro_bg.png");
  load_tex("avatar_intro", "res/avatar_intro.png");
  load_tex("avatar_question", "res/avatar_question.png");
  load_tex("avatar_bellflowers", "res/avatar_bellflowers.png");
  load_tex("avatar_lightall", "res/avatar_lightall.png");
  load_tex("avatar_lantern", "res/avatar_lantern.png");
  load_tex("avatar_cat", "res/avatar_cat.png");
  load_tex("avatar_bedside", "res/avatar_bedside.png");
  load_tex("avatar_night", "res/avatar_night.png");
  load_tex("avatar_bush", "res/avatar_bush.png");
  load_tex("avatar_oracle", "res/avatar_oracle.png");

  load_tex("bellflower_ord", "res/bellflower_ord.png");
  load_tex("bellflower_call", "res/bellflower_call.png");
  load_tex("board_bg", "res/board_bg.png");

  load_tex("btn_play", "res/btn_play.png");
  load_tex("btn_stop", "res/btn_stop.png");
  load_tex("btn_1x", "res/btn_1x.png");
  load_tex("btn_2x", "res/btn_2x.png");
}

static inline unsigned char to_u8(float x) { return (unsigned char)(255.0f * x); }
static inline Color to_rl(tint4 tint) {
  return (Color){
    to_u8(tint.r), to_u8(tint.g),
    to_u8(tint.b), to_u8(tint.a)
  };
}

void painter::text(
  const char *s, int size,
  vec2 pos, vec2 anchor,
  tint4 tint)
{
  Vector2 dims = MeasureTextEx(font[size], s, size, 0);
  DrawTextEx(
    font[size], s,
    (Vector2){pos.x - dims.x * anchor.x, pos.y - dims.y * anchor.y},
    size, 0,
    to_rl(tint)
  );
}

void painter::image(
  const char *name,
  vec2 pos,
  tint4 tint)
{
  auto rec = tex(name);
  image(name, pos, vec2(rec.width, rec.height), tint);
}

void painter::image(
  const char *name,
  vec2 pos, vec2 dims,
  tint4 tint)
{
  auto rec = tex(name);
  image(name, pos, dims,
    vec2(0, 0), vec2(rec.width, rec.height),
    vec2(0, 0), 0,
    tint);
}

void painter::image(
  const char *name,
  vec2 pos, vec2 anchor, vec2 scale,
  tint4 tint)
{
  auto rec = tex(name);
  auto dims = vec2(rec.width, rec.height);
  image(name,
    pos + (vec2(1, 1) - scale) * dims * anchor,
    dims * scale,
    vec2(0, 0), dims,
    anchor * dims, 0,
    tint);
}

void painter::image(
  const char *name,
  vec2 pos, vec2 dims,
  vec2 src_pos, vec2 src_dims,
  vec2 anchor, float rot,
  tint4 tint)
{
  auto rec = tex(name);
  DrawTexturePro(rec.tex,
    (Rectangle){src_pos.x, src_pos.y, src_dims.x, src_dims.y},
    (Rectangle){pos.x, pos.y, dims.x, dims.y},
    (Vector2){anchor.x, anchor.y},
    rot / M_PI * 180,
    to_rl(tint)
  );
}
