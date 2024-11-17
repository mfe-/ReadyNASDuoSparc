
# Prerequisites:

## zlib
dpkg -i zlib-1.3.1_1.3.1-1_sparc.deb # see parent folder

## sqlite3
dpkg -i libsqlite3_347-1_sparc.deb # see parent folder

## ffmpeg-5.1.6
dpkg -i ffmpeg-5.1.6_5.1.6-1_sparc.deb

dpkg -i ../bzip2-1.0.8/bzip2_1.0.8-1_sparc.deb 
dpkg -i ReadyNASDuoSparc/xz-5.2.2_5.2.2-1_sparc.deb 


./configure 
--disable-libvpx --disable-decoder=vp9 --disable-encoder=vp9 --disable-parser=vp9 --disable-bsf=vp9_metadata --disable-bsf=vp9_raw_reorder --disable-bsf=vp9_superframe --disable-bsf=vp9_superframe_split --enable-nonfree --enable-gpl --cc=/c/opt/gcc-4.6.0/bin/gcc && /usr/local/bin/make

Notes:
- vp9 resulted in an internal compiler error therefore we disabled it.
- During compilation there was an error in `error.c` which was fixed with copilot.

## libjpeg_9-1_sparc
dpkg -i libjpeg_9-1_sparc.deb

./configure 
## libexif-0.6.21
dpkg -i libexif_0.6.21-1_sparc.deb

./configure 
## libid3tag-0.15.1b

dpkg -i libid3tag_0.15-1_sparc.deb

./configure --build=sparc

## minidlna-1.3.3

LIBS="-lavformat -lavcodec -lavutil -lz -lm -lpthread -lswresample  -lavutil -lz -lm -lpthread -lswresample -lbz2 -llzma -liconv -lrt" ./configure --prefix=/usr --enable-tivo --enable-netgear  --enable-readynas

```config.log
checking for gcc -std=gnu99 options needed to detect all undeclared functions... none needed
checking whether SEEK_HOLE is declared... no
checking for library containing clock_gettime... none required
checking for struct ip_mreqn... yes
checking for syscall.h... yes
checking for sys/syscall.h... yes
checking for mach/mach_time.h... no
checking for __NR_clock_gettime syscall... yes
checking for linux/netlink.h... yes
checking for libavutil/avutil.h... yes
checking for ffmpeg/libavutil/avutil.h... yes
checking for libav/libavutil/avutil.h... yes
checking for avutil.h... no
checking for ffmpeg/avutil.h... yes
checking for libav/avutil.h... yes
checking for libavcodec/avcodec.h... yes
checking for ffmpeg/libavcodec/avcodec.h... no
checking for libav/libavcodec/avcodec.h... no
checking for avcodec.h... no
checking for ffmpeg/avcodec.h... no
checking for libav/avcodec.h... no
checking for libavformat/avformat.h... yes
checking for ffmpeg/libavformat/avformat.h... no
checking for libav/libavformat/avformat.h... no
checking for avformat.h... no
checking for ffmpeg/avformat.h... no
checking for libav/avformat.h... no
checking for jpeglib.h... yes
checking for sqlite3.h... yes
checking for libexif/exif-loader.h... yes
checking for id3tag.h... yes
checking for ogg/ogg.h... yes
checking for vorbis/codec.h... yes
checking for FLAC/metadata.h... yes
checking if we should use the daemon() libc function... yes
checking if scandir declaration requires const char cast... yes
checking for linux sendfile support... yes
checking for darwin sendfile support... no
checking for freebsd sendfile support... no
checking for jpeg_set_defaults in -ljpeg... yes
checking for exif_data_new_from_file in -lexif... yes
checking for id3_file_open in -lid3tag -lz... yes
checking for sqlite3_open in -lsqlite3... yes
checking for sqlite3_malloc in -lsqlite3... yes
checking for sqlite3_prepare_v2 in -lsqlite3... yes
checking for avformat_open_input in -lavformat -lavcodec -lavutil -lz... yes
checking for pthread_create in -lpthread... yes
checking for ov_open_callbacks in -lvorbisfile... no
checking for FLAC__stream_decoder_init_stream in -lFLAC... no
checking for FLAC__stream_decoder_init_ogg_stream in -lFLAC... no
checking for vorbis_comment_query in -lvorbisfile... no
checking for avahi_threaded_poll_new in -lavahi-client... no
checking for arpa/inet.h... yes
checking for asm/unistd.h... yes
checking for endian.h... yes
checking for machine/endian.h... no
checking for fcntl.h... yes
checking for libintl.h... yes
checking for locale.h... yes
checking for netdb.h... yes
checking for netinet/in.h... yes
checking for poll.h... yes
checking for stddef.h... yes
checking for stdlib.h... (cached) yes
checking for string.h... (cached) yes
checking for sys/file.h... yes
checking for sys/inotify.h... no
checking for sys/ioctl.h... yes
checking for sys/param.h... yes
checking for sys/queue.h... yes
checking for sys/socket.h... yes
checking for sys/time.h... yes
checking for unistd.h... (cached) yes
checking for inotify_init... no
checking for __NR_inotify_init syscall... yes
checking for kqueue... no
checking whether to enable TiVo support... yes
checking whether to enable generic NETGEAR device support... yes
checking whether to enable NETGEAR ReadyNAS support... yes
checking whether to build a static binary executable... no
checking whether to enable LTO... no
checking that generated files are newer than configure... done
configure: creating ./config.status
config.status: creating po/Makefile.in
config.status: creating Makefile
config.status: creating config.h
config.status: executing depfiles commands
config.status: executing po-directories commands
config.status: creating po/POTFILES
config.status: creating po/Makefile
```

The original minidlna of the readynas version is installed with:

fes-a120d19nas:/nas-source/minidlna-1.3.3# dpkg -l | grep mini
ii  iptables                          1.2.11-10                   Linux kernel 2.4+ iptables administration to
ii  minidlna                          1.1.4-netgear1              lightweight DLNA/UPnP-AV server targeted at 
ii  passwd                            1:4.0.3-31sarge9            change and administer password and group dat
fes-a120d19nas:/nas-source/minidlna-1.3.3# /usr/bin/
Display all 310 possibilities? (y or n)
fes-a120d19nas:/nas-source/minidlna-1.3.3# /usr/sbin/minidlna --help
Usage:
	/usr/sbin/minidlna [-d] [-v] [-f config_file] [-p port]
		[-i network_interface] [-u uid_to_run_as]
		[-t notify_interval] [-P pid_filename]
		[-s serial] [-m model_number]
		[-w url] [-R] [-L] [-S] [-V] [-h]

Notes:
	Notify interval is in seconds. Default is 895 seconds.
	Default pid file is /var/run/minidlna/minidlna.pid.
	With -d minidlna will run in debug mode (not daemonize).
	-w sets the presentation url. Default is http address on port 80
	-v enables verbose output
	-h displays this text
	-R forces a full rescan
	-L do not create playlists
	-S changes behaviour for systemd
	-V print the version number
fes-a120d19nas:/nas-source/minidlna-1.3.3# /usr/sbin/minidlna -V
Version 1.1.4
