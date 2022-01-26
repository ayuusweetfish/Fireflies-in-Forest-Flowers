case 0:
  tracks = {
    T_cir(vec2(8, 6), 3),
  };
  fireflies = {
    F(0, 0.5, 1),
  };
  bellflowers = {
    B_ord(vec2(14, 6), 2, 3),
  };
  break;

case 1:
  tracks = {
    T_cir(vec2(10, 6), 4),
  };
  fireflies = {
    F(0, 0.75, 1),
  };
  bellflowers = {
    B_ord(vec2(5, 6), 2, 2),
    B_ord(vec2(15, 6), 2, 1),
  };
  break;

case 10:
  tracks = {
    T_cir(vec2(12, 5), 3, track::FIXED),
    T_cir(vec2(8, 7), 3, track::FIXED),
    T_cir(vec2(17.5, 9.5), 1.5, track::ATTRACT),
  };
  fireflies = {
    F(0, 0.75, 1),
    F(1, 0.25, 1),
  };
  links = {
    {0, 1},
  };
  bellflowers = {
    B_ord(vec2(4, 6), 2, 1),
    B_ord(vec2(16, 6), 2, 4),
  };
  break;

case 99:
  tracks = {
    T_cir(vec2(4, 3), 2),
    T_cir(vec2(6, 5), 3),
    T_cir(vec2(10, 5), 3, track::ATTRACT),
    T_seg(vec2(11, 7), vec2(2, 1), track::RETURN | track::FIXED),
  };
  fireflies = {
    F(0, 0, 1),
    F(0, 1, 1),
    F(0, 2, 1),
    F(0, 3, 1),
    F(0, 4, 1),
    F(1, 0.25, 1),
  };
  links = {
    {0, 1},
    {2, 3, 4},
  };
  bellflowers = {
    B_ord(vec2(5, 7), 2, 4),
    B_delay(vec2(11, 7), 2, 4, 480),
  };
  break;
