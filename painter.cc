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
  const int chars_zh[] = {
    32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,
0x3002,0x4e0d,0x4e4b,0x4e86,0x4eec,0x4f1a,0x4f60,0x513f,0x5230,0x529e,0x5417,0x5440,0x544a,0x54ea,0x5566,0x5728,0x5948,0x5979,0x59cb,0x5c4f,0x5cb8,0x5e55,0x5f00,0x5f7c,0x6211,0x6309,0x662f,0x6709,0x6765,0x6797,0x68ee,0x6cd5,0x6d41,0x706b,0x70b9,0x7247,0x7684,0x77e5,0x82b1,0x8424,0x866b,0x89c1,0x8ba9,0x8bc9,0x8bed,0x8fc7,0x8fd9,0x9053,0x91cc,0xff01,0xff0c,0xff1f
  };
  for (int size : {24, 32, 36, 60}) {
    // 95 = ASCII range (32 ~ 126)
    font[size] = LoadFontEx("res/Imprima_AaKaiSong2.ttf", size,
      (int *)chars_zh, sizeof chars_zh / sizeof chars_zh[0]);
  }
  load_tex("intro_bg", "res/intro_bg.png");
  load_tex("avatar_intro", "res/avatar_intro.png");
  load_tex("avatar_question", "res/avatar_question.png");
  load_tex("avatar_bellflowers", "res/avatar_bellflowers.png");
  load_tex("avatar_lightall", "res/avatar_lightall.png");
  load_tex("avatar_lantern", "res/avatar_lantern.png");
  load_tex("avatar_cat", "res/avatar_cat.png");
  load_tex("avatar_bedside", "res/avatar_bedside.png");
  load_tex("avatar_rain", "res/avatar_rain.png");
  load_tex("avatar_bush", "res/avatar_bush.png");
  load_tex("avatar_oracle", "res/avatar_oracle.png");
  load_tex("avatar_night", "res/avatar_night.png");

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
