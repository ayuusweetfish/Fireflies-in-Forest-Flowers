case 0:
  title = "Firefly";
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
      "This is the firefly", vec2(-1, 0) + vec2(3, 0).rot(1.2 * M_PI), 1},
    {vec2(-1, 4.5), "This is its track", vec2(-1, 0), 3.5},
    {vec2(6, 3.5), "This is the bellflower", vec2(3, 0), 2.5},
    {vec2(-3.25, -6), "Now press the button to start flying"},
  };
  break;

case 1:
  title = "Closer";
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
    {vec2(-5, 4), "Drag the track to move it",
      vec2(-5, 0), 3,
      vec2(3, 0), 3},
    {vec2(-7.8, -6), "(Space)"},
    {vec2(-8.18, -4.25), "(Tab)"},
  };
  to_text = 6;
  break;

case 2:
  title = "Message";
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
    {vec2(0, -2), "Drag the firefly...", vec2(0, -4), 1},
    {vec2(0, 3.5), "So that both bellflowers count down to zero", vec2(-5, 0), 2.5, vec2(5, 0), 2.5},
  };
  break;

case 3:
  title = "Arrangement";
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
  title = "Trail";
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
  title = "Joined Together";
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
  title = "Fate";
  tracks = {
    T_cir(vec2(-6, -1), 2),
    T_cir(vec2(0, -1), 2, track::FIXED),
    T_seg(vec2(-6, 2.5), vec2(2, 0.5)),
    T_seg(vec2(0, 2.5), vec2(2, 0.5), track::FIXED),
  };
  fireflies = {
    F(0, 0.75, M_PI / sqrtf(4.25)),
    F(1, 0.75, M_PI / sqrtf(4.25)),
    F(2, 0.3, 1),
    F(3, 0.3, 1),
  };
  bellflowers = {
    B_ord(vec2(6, 0), 2, 2),
  };
  tutorials = {
    {vec2(0, -5.5), "Tracks with fixation marks"},
    {vec2(0, -4.5), "cannot be moved", vec2(-2, -1), 1, vec2(2, 3), 1},
    {vec2(0, 4.5), "...but fireflies still can",
      vec2(0, -3), 1,
      vec2(0, 2.5) - vec2(2, 0.5) * 0.4, 1},
    {vec2(0, -5.5), "Tracks with fixation marks"},
    {vec2(0, -4.5), "cannot be moved"},
    {vec2(0, 4.5), "...but fireflies still can"},
  };
  break;

case 7:
  title = "Encounter";
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
    {vec2(0, -4.5), "The bellflower is lit up"},
    {vec2(0, -3.5), "as long as any firefly is close"},
  };
  break;

case 8:
  title = "Intersection";
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
  to_text = 15;
  break;

case 9:
  title = "Ebb and Flow";
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
    {vec2(0, -5), "Fireflies may travel at different speeds"},
  };
  break;

case 10:
  title = "Attraction";
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
    {vec2(1, -4.5), "Attracting tracks capture"},
    {vec2(1, -3.5), "all fireflies touching them"},
  };
  break;

case 11:
  title = "Twin Paradox";
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
    B_ord(vec2(-6, 0), 2, 1),
    B_ord(vec2(6, 0), 2, 4),
  };
  break;

case 12:
  title = "Entrance";
  tracks = {
    T_cir(vec2(2, 0), 3, track::FIXED | track::ATTRACT),
    T_cir(vec2(-2, 0), 3),
  };
  fireflies = {
    F(1, 0.75, 1),
  };
  bellflowers = {
    B_ord(vec2(6, -2), 2, 1),
    B_ord(vec2(6, 2), 2, 2),
    B_ord(vec2(-4, 0), 2, 1),
  };
  tutorials = {
    {vec2(0, -5), "Fireflies pick the nearest direction when entering"},
  };
  break;

case 13:
  title = "Comet";
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
  title = "Circulation";
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
  title = "Return";
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
    {vec2(0, -4.5), "Repelling lines make fireflies turn around"},
  };
  break;

case 16:
  title = "Accompany";
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
  title = "Linger";
  tracks = {
    T_cir(vec2(0, -2), 3),
    T_cir(vec2(0, 0), 3, track::ATTRACT | track::FIXED, 1),
    T_seg(vec2(4, 0), vec2(1.8, 0), track::RETURN | track::FIXED),
  };
  fireflies = {
    F(0, 0.75, 1),
  };
  bellflowers = {
    B_ord(vec2(-4, 0), 2, 1),
    B_ord(vec2(4, 0), 2, 3),
  };
  break;

case 18:
  title = "Pearl";
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
  title = "Chords";
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
  title = "Intertwined";
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
  to_text = 25;
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
