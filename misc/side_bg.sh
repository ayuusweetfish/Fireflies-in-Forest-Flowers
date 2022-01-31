convert side_bg.png -crop 400x400+000+000 side_bg_1.png
convert side_bg.png -crop 400x400+400+000 side_bg_2.png
convert side_bg.png -crop 400x400+000+400 side_bg_3.png
convert side_bg.png -crop 400x400+400+400 side_bg_4.png
convert side_bg_{1..4}.png +repage -background None -layers Flatten side_bg_comp.png
rm side_bg.png side_bg_{1..4}.png
