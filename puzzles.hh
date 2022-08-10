#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-warning-option"
#pragma GCC diagnostic ignored "-Wc99-designator"
case 0:
  title = _("Firefly", "萤火");
  tracks = {
    T_cir(vec2(-1, 0), 3),
  };
  fireflies = {
    F(0, 0.6, 1),
  };
  bellflowers = {
    B_ord(vec2(3, 0), 2, 3),
  };
  tutorials = {
    {vec2(-1, -2) + vec2(3, 0).rot(1.2 * M_PI),
      _("This is the firefly", "这是一只萤火虫"),
      vec2(-1, 0) + vec2(3, 0).rot(1.2 * M_PI), 1},
    {vec2(-1, 4.5),
      _("This is its track", "这是它的飞行轨迹"),
      vec2(-1, 0), 3.5},
    {vec2(6, 3.5),
      _("This is the bellflower", "这是一朵风铃花"),
      vec2(3, 0), 2.5},
    {vec2(_(-3.5, -4.5), -6),
      _("Press the button to start flying", "按下按钮让萤火虫飞行"),
      vec2(-10.2, -6), 1,
      .allows_interaction = true},
  };
  break;

case 1:
  title = _("Closer", "傍依");
  tracks = {
    T_cir(vec2(-5, 0), 2.5),
  };
  fireflies = {
    F(0, 0.5, 1),
  };
  bellflowers = {
    B_ord(vec2(5, 0), 2, 3),
  };
  tutorials = {
    {vec2(-1, 0), ">"},
    {vec2(-5, 4),
      _("Drag the track to move it", "拖动轨道并移动之"),
      vec2(-5, 0), 3,
      vec2(3, 0), 3,
      .allows_interaction = true},
    {vec2(_(-7.8, -8.04), -6), _("(Space)", "(空格)")},
    {vec2(-8.18, -4.25), "(Tab)"},
  };
  to_text = 6;
  break;

case 2:
  title = _("Message", "音信");
  tracks = {
    T_cir(vec2(0, 0), 4),
  };
  fireflies = {
    F(0, 0.75, 1),
  };
  bellflowers = {
    B_ord(vec2(-5, 0), 2, 2),
    B_ord(vec2(5, 0), 2, 1),
  };
  tutorials = {
    {vec2(0, -2),
      _("Drag the firefly...", "拖动萤火虫……"),
      vec2(0, -4), 1,
      .allows_interaction = true},
    {vec2(0, 3.5),
      _("So that both bellflowers are lit up",
        "使两朵风铃花都被点亮"),
      vec2(-5, 0), 2.5, vec2(5, 0), 2.5},
  };
  break;

case 3:
  title = _("Arrangement", "罗布");
  tracks = {
    T_cir(vec2(0, 0), 3),
    T_cir(vec2(0, 0), 2),
  };
  fireflies = {
    F(0, 0.75, 1),
    F(1, 0.25, 1),
  };
  bellflowers = {
    B_ord(vec2(-5, 2), 2, 2),
    B_ord(vec2(5, -2), 2, 5),
  };
  to_text = 10;
  break;

case 4:
  title = _("Trail", "僻径");
  tracks = {
    T_seg(vec2(0, 0), vec2(5, 1)),
  };
  fireflies = {
    F(0, 0.3, 1),
  };
  bellflowers = {
    B_ord(vec2(-6, -2), 2, 2),
    B_ord(vec2(6, 2), 2, 2),
    B_ord(vec2(1, -1), 2, 1),
  };
  break;

case 5:
  title = _("Joined Together", "联结");
  tracks = {
    T_cir(vec2(0, 0), 4),
  };
  fireflies = {
    F(0, 0.125, 1),
    F(0, 0.875, 1),
  };
  links = {
    {0, 1},
  };
  bellflowers = {
    B_ord(vec2(-5, 0), 2, 2),
    B_ord(vec2(5, 0), 2, 4),
  };
  break;

case 6:
  title = _("Fate", "命定");
  tracks = {
    T_cir(vec2(-4.5, -1.5), 2.5),
    T_cir(vec2(4.5, -1.5), 2.5, track::FIXED),
    T_seg(vec2(-4.5, 2.5), vec2(3.5, 0.5)),
    T_seg(vec2(4.5, 2.5), vec2(3.5, 0.5), track::FIXED),
  };
  fireflies = {
    F(0, 0.75, M_PI * 2.5 / sqrtf(12.5) / 2),
    F(1, 0.75, M_PI * 2.5 / sqrtf(12.5) / 2),
    F(2, 0.3, 1),
    F(3, 0.3, 1),
  };
  links = {
    {0, 1},
    {2, 3},
  };
  bellflowers = {
    B_ord(vec2(-2, 1), 2, 4),
    B_ord(vec2(7, 1), 2, 3),
  };
  tutorials = {
    {vec2(0, 4.75),
      _("Tracks with fixation marks cannot be moved",
        "带有固定标记的轨道无法移动"),
      vec2(2, -1.5), 1, vec2(1, 2), 1},
    {vec2(0, 4.75),
      _("...but fireflies still can",
        "……但是萤火虫仍可拖动"),
      vec2(4.5, -4), 1,
      vec2(4.5, 2.5) - vec2(3.5, 0.5) * 0.4, 1},
  };
  break;

case 7:
  title = _("Encounter", "邂逅");
  tracks = {
    T_cir(vec2(-4, 1), 3, track::FIXED, M_PI / 2),
    T_cir(vec2(4, 1), 3, track::FIXED, M_PI / 2),
  };
  fireflies = {
    F(0, 0.75, 1),
    F(1, 0.825, -1),
  };
  bellflowers = {
    B_ord(vec2(0, 0), 2, 1),
    B_ord(vec2(-8, 1), 2, 1),
    B_ord(vec2(8, 1), 2, 2),
  };
  links = {
    {0, 1},
  };
  tutorials = {
    {vec2(0, -4.5),
      _("The bellflower is lit up",
        "只要有萤火虫在附近")},
    {vec2(0, -3.5),
      _("as long as any firefly is close",
        "风铃花就会一直被点亮")},
  };
  break;

case 8:
  title = _("Intersection", "交汇");
  tracks = {
    T_cir(vec2(-2, 1), 3, track::FIXED, M_PI / 2),
    T_cir(vec2(2, 1), 3, track::FIXED, M_PI / 2),
  };
  fireflies = {
    F(0, 0.375, 1),
    F(1, 0.875, 1),
  };
  bellflowers = {
    B_ord(vec2(0, -3), 2, 1),
    B_ord(vec2(-6, 1), 2, 2),
    B_ord(vec2(6, 1), 2, 1),
  };
  break;

case 9:
  title = _("Ebb and Flow", "悲欢");
  tracks = {
    T_cir(vec2(0, 0), 4, track::FIXED, M_PI / 2),
  };
  fireflies = {
    F(0, 0.125, 0.5),
    F(0, 0.875, 1.9),
  };
  links = {
    {0, 1},
  };
  bellflowers = {
    B_ord(vec2(-5, 0), 2, 6),
    B_ord(vec2(5, 0), 2, 3),
  };
  tutorials = {
    {vec2(0, -5),
      _("Fireflies may travel at different speeds",
        "萤火虫飞行有快有慢")},
  };
  to_text = 15;
  break;

case 10:
  title = _("Attraction", "吸引");
  tracks = {
    T_cir(vec2(-1, 1), 3, track::FIXED),
    T_cir(vec2(1, 1), 3, track::FIXED | track::ATTRACT),
  };
  fireflies = {
    F(0, 0.375, 1),
    F(0, 0.625, 1),
  };
  links = {
    {0, 1},
  };
  bellflowers = {
    B_ord(vec2(-5, 1), 2, 2),
    B_ord(vec2(5, 1), 2, 2),
  };
  tutorials = {
    {vec2(1, -4.5),
      _("Attracting tracks capture",
        "带有吸引特性的轨道")},
    {vec2(1, -3.5),
      _("fireflies touching them",
        "会捕获触碰它的每一只萤火虫")},
  };
  break;

case 11:
  title = _("Twin Paradox", "荏苒");
  tracks = {
    T_cir(vec2(2, -1), 3, track::FIXED, 1),
    T_cir(vec2(-2, 1), 3, track::FIXED, 1),
    T_cir(vec2(8.5, 3.5), 1.5, track::ATTRACT),
  };
  fireflies = {
    F(0, 0.75, 1),
    F(1, 0.25, 1),
  };
  links = {
    {0, 1},
  };
  bellflowers = {
    B_ord(vec2(-6, 0), 2, 2),
    B_ord(vec2(6, 0), 2, 6),
  };
  break;

case 12:
  title = _("Capture", "采撷");
  tracks = {
    T_cir(vec2(2, 1), 3, track::FIXED | track::ATTRACT),
    T_cir(vec2(-2, 1), 3),
  };
  fireflies = {
    F(1, 0.75, 1),
  };
  bellflowers = {
    B_ord(vec2(6, -1), 2, 1),
    B_ord(vec2(6, 3), 2, 2),
    B_ord(vec2(-4, 1), 2, 1),
  };
  tutorials = {
    {vec2(0, _(-5.0, -4.5)),
      _("Fireflies pick a direction to avoid acute turns",
        "当萤火虫变换轨道时，会尽可能保持原本的方向")},
    {vec2(0, -4),
      _("when entering a different track",
        "")}
  };
  break;

case 13:
  title = _("Comet", "彗星");
  tracks = {
    T_cir(vec2(-3, 0), sqrtf(5), track::FIXED, M_PI / 2),
    T_cir(vec2(-3, 0), 4, track::ATTRACT | track::FIXED, M_PI / 2),
    T_cir(vec2(5, -0.5), 3.5),
  };
  fireflies = {
    F(0, 0.875, 1),
    F(2, 0.125, 4 / sqrtf(5)),
  };
  bellflowers = {
    B_ord(vec2(6, -3), 2, 1),
    B_ord(vec2(-5.5, -2), 2, 4),
    B_ord(vec2(-5.5, 2), 2, 4),
  };
  break;

case 14:
  title = _("Circulation", "萦回");
  tracks = {
    T_cir(vec2(0, 0.5), 4.5, track::FIXED | track::ATTRACT),
    T_cir(vec2(0, 0.5), 2.5),
  };
  fireflies = {
    F(0, 0.95, 1),
    F(1, 0.5, 1),
  };
  bellflowers = {
    B_ord(vec2(0, -5), 2, 1),
    B_ord(vec2(-5, 3), 2, 4),
    B_ord(vec2(5, 3), 2, 1),
  };
  to_text = 20;
  break;

case 15:
  title = _("Return", "复归");
  tracks = {
    T_cir(vec2(0, 1), 4, track::FIXED, M_PI / 2),
    T_cir(vec2(-5, 1), 4, track::FIXED | track::RETURN, M_PI / 2),
    T_cir(vec2(5, 1), 4, track::FIXED | track::RETURN, M_PI / 2),
  };
  fireflies = {
    F(0, 0.75 - 0./3, 1),
    F(0, 0.75 - 1./3, 1),
    F(0, 0.75 - 2./3, 1),
  };
  links = {
    {0, 1, 2},
  };
  bellflowers = {
    B_ord(vec2(-5, -1), 2, 4),
    B_ord(vec2(5, 3), 2, 2),
  };
  tutorials = {
    {vec2(0, -4.5),
      _("Repelling lines make fireflies turn around",
        "萤火虫触碰到排斥线时会转向")},
  };
  break;

case 16:
  title = _("Accompany", "相伴");
  tracks = {
    T_seg(vec2(0, -1), vec2(5, 0), track::FIXED),
    T_seg(vec2(0, 1), vec2(5, 0), track::FIXED),
    T_seg(vec2(0, 3), vec2(0, 0.5), track::RETURN),
  };
  fireflies = {
    F(0, 0.2, 1),
    F(1, 0.3, 1),
  };
  bellflowers = {
    B_ord(vec2(-6, 0), 2, 3),
    B_ord(vec2(6, 0), 2, 1),
  };
  break;

case 17:
  title = _("Lingering", "流连");
  tracks = {
    T_cir(vec2(0, -1), 3),
    T_cir(vec2(0, 1), 3, track::ATTRACT | track::FIXED, 1),
    T_seg(vec2(4, 1), vec2(1.8, 0), track::RETURN | track::FIXED),
  };
  fireflies = {
    F(0, 0.75, 1),
  };
  bellflowers = {
    B_ord(vec2(-4, 1), 2, 1),
    B_ord(vec2(4, 1), 2, 3),
  };
  break;

case 18:
  title = _("Pearl", "明珠");
  tracks = {
    T_cir(vec2(-6, -1), 2, track::FIXED, 4, true),
    T_cir(vec2(-3, 1), 2, track::FIXED, 2, true),
    T_cir(vec2(0, -1), 2, track::FIXED, 4, true),
    T_cir(vec2(3, 1), 2, track::FIXED, 2, true),
    T_cir(vec2(6, -1), 2, track::FIXED, 4, true),
    T_cir(vec2(6, 3), 0.25, track::RETURN),
  };
  fireflies = {
    F(0, 0.875, 1),
    F(1, 0.125, 1),
    F(2, 0.875, 1),
    F(3, 0.125, 1),
    F(4, 0.875, 1),
  };
  links = {
    {0, 2, 4},
    {1, 3},
  };
  bellflowers = {
    B_ord(vec2(-4.5, 0), 1, 3),
    B_ord(vec2(-1.5, 0), 1, 3),
    B_ord(vec2(1.5, 0), 1, 6),
    B_ord(vec2(4.5, 0), 1, 6),
  };
  break;

case 19:
  title = _("Chords", "弦歌");
  tracks = {
    T_cir(vec2(0, 0), 5, track::FIXED | track::ATTRACT, 1.35),
    T_seg(vec2(-0.5, -0.25), vec2(3, -6), track::ATTRACT),
    T_seg(vec2(0.5, 0.25), vec2(3, -6), track::RETURN),
  };
  fireflies = {
    F(0, 0./5 + 0.75, 1),
    F(0, 1./5 + 0.75, 1),
    F(0, 2./5 + 0.75, 1),
    F(0, 3./5 + 0.75, 1),
    F(0, 4./5 + 0.75, 1),
  };
  links = {
    {0, 1, 2, 3, 4},
  };
  bellflowers = {
    B_ord(vec2(0, 0), 2, 2),
    B_ord(vec2(-6, 0), 2, 5),
    B_ord(vec2(6, 0), 2, 3),
  };
  break;

case 20:
  title = _("Intertwined", "交织");
  tracks = {
    T_cir(vec2(-1, 0), 2.5, track::ATTRACT),
    T_cir(vec2(0, 0), 2.5, track::ATTRACT),
    T_cir(vec2(1, 0), 2.5, track::ATTRACT),
  };
  fireflies = {
    F(0, 0.5, 1),
  };
  bellflowers = {
    B_ord(vec2(-6, 1), 4, 1),
    B_ord(vec2(6, -1), 4, 6),
  };
  to_text = 27;
  break;

case 98:
  title = "";
  tracks = {
    T_cir(vec2(0, -4), 5.3),
    T_cir(vec2(0, -4), 6, track::ATTRACT),
  };
  fireflies = {
    F(0, 0.19, 1),
    F(1, 0.13, -1),
  };
  bellflowers = {
    B_ord(vec2(-99, -99), 1, 1),
  };
  break;

/*
case 96:
  title = "Embellishment";
  tracks = {
    T_cir(vec2(0, 0), 5, track::FIXED, M_PI / 2),
    T_cir(vec2(-6, 0), 3, track::FIXED | track::RETURN, M_PI, 1),
    T_cir(vec2(6, 0), 3, track::FIXED | track::RETURN, 0, 1),
  };
  fireflies = {
    F(0, 0./5, 1),
    F(0, 1./5, 1),
    F(0, 2./5, 1),
    F(0, 3./5, 1),
    F(0, 4./5, 1),
  };
  links = {
    {0, 1, 2, 3, 4},
  };
  bellflowers = {
    B_ord(vec2(-5, -4), 2, 7),
    B_ord(vec2(5, 4), 2, 10),
  };
  break;

case 99:
  title = "Testbed";
  tracks = {
    T_cir(vec2(-6, -3), 2),
    T_cir(vec2(-4, -1), 3),
    T_cir(vec2(0, -1), 3, track::ATTRACT),
    T_seg(vec2(1, 1), vec2(2, 1), track::RETURN | track::FIXED),
  };
  fireflies = {
    F(0, 0, 1),
    F(0, .1, 1),
    F(0, .2, 1),
    F(0, .3, 1),
    F(0, .4, 1),
    F(1, 0.25, 1),
  };
  links = {
    {0, 1},
    {2, 3, 4},
  };
  bellflowers = {
    B_ord(vec2(-5, 1), 2, 4),
    B_ord(vec2(1, 1), 2, 4),
  };
  break;
*/
#pragma GCC diagnostic pop
