cat >merge.ff <<'EOF'
# fontforge -lang=ff -script %
Open("AaKaiSong2_subset.ttf")
em1=$em
Close()

Open("Imprima_subset.ttf")
ScaleToEm(Round(em1 * 1.1))
MergeFonts("AaKaiSong2_subset.ttf")
Generate("Imprima_AaKaiSong2.ttf")
Close()
EOF

pyftsubset fonts/AaKaiSong2.ttf \
  --output-file=AaKaiSong2_subset.ttf \
  --text=`cat ../*.hh ../*.cc | perl -CIO -pe 's/[\p{ASCII} \N{U+2500}-\N{U+257F}]//g'`
pyftsubset fonts/Imprima.ttf \
  --output-file=Imprima_subset.ttf \
  --unicodes=20-fe

fontforge -lang=ff -script merge.ff
rm merge.ff AaKaiSong2_subset.ttf Imprima_subset.ttf

fc-query --format=%{charset} Imprima_AaKaiSong2.ttf \
  | python3 parse_charset.py > ../charset.hh
mv Imprima_AaKaiSong2.ttf ../res
