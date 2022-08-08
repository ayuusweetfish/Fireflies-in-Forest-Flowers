BASE="/Users/lsq/Documents/Tracktion/work220706/Exported/work220706 Edit 2 - Copy(2) Export 1"
FFMPEG=/Users/lsq/Downloads/ffmpeg-5.0.1

cvt() {
  $FFMPEG -y -i "$BASE $1 Render 0.wav" ../res/$2.ogg
}

cvt "Track 1" bellflower_pop_zero_1
cvt "Track 2" bellflower_pop_zero_2
cvt "Track 3" bellflower_pop_zero_3
cvt "Track 4" bellflower_pop_zero_4
cvt "Track 5" bellflower_pop_zero_0
cvt "Track 6" hint
cvt "Submix 1" puzzle_solved
cvt "Submix 2" bellflower_pop_ord
