
## ffmpeg-5.1.6
./configure 
--disable-libvpx --disable-decoder=vp9 --disable-encoder=vp9 --disable-parser=vp9 --disable-bsf=vp9_metadata --disable-bsf=vp9_raw_reorder --disable-bsf=vp9_superframe --disable-bsf=vp9_superframe_split --enable-nonfree --enable-gpl --cc=/c/opt/gcc-4.6.0/bin/gcc && /usr/local/bin/make

Notes:
- vp9 resulted in an internal compiler error therefore we disabled it.
- During compilation there was an error in `error.c` which was fixed with copilot.

## libjpeg_9-1_sparc

## libexif-0.6.21