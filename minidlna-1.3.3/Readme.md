# Install minidlna-1.3.3 on ReadyNAS Duo Sparc

Notice

1. Install all [Prerequisites](#prerequisites) packages (like `dpkg -i libsqlite3_3.35.5-1_sparc.deb `, [...] )
   - dpkg -i ffmpeg-5.1.6_5.1.6-1_sparc.deb
   - `dpkg -i libsqlite3_3.35.5-1_sparc.deb `
   - dpkg -i libjpeg_9-1_sparc.deb
   - dpkg -i libexif_0.6.21-1_sparc.deb
   - dpkg -i libid3tag_0.15-1_sparc.deb

2. Create a backup of the old minidlna with `mv /usr/sbin/minidlna /usr/sbin/backup.minidlna`.
3. Notice after the installation you cannot start or stop the minidlna over the readynas duo web interface. You have to start and stop the minidlna over the command line! 
4. Remove the old minidlna with `dpkg -r minidlna`
4. Install `dpkg -i minidlna_1.3.3-1_sparc.deb`
3. *Create a startup script for minidlna*: At boot time, the hard disk drives are probably not mounted. In case they are not mounted, we need to wait until they get mounted; otherwise, minidlna will reset the indexed database, and the UPnP client devices will not be able to browse your media. As a workaround, the startup script will start a function asynchronously and periodically check whether /c and /d are mounted. If not, it will sleep for 1 second; otherwise, it will start minidlna.
   - a. Create the startup script for minidlna with `nano /etc/init.d/minidlna` and add the following content if you have TWO mount points /c and /d (in the case you have only one mount point /c use the next option b. !):
```bash
#!/bin/sh
### BEGIN INIT INFO
# Provides:          minidlna
# Required-Start:    $local_fs $network
# Required-Stop:     $local_fs $network
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Start/stop MiniDLNA server
### END INIT INFO

DAEMON=/usr/sbin/minidlnad
DAEMON_OPTS="-f /etc/minidlna.conf"
NAME=minidlna
DESC="MiniDLNA server"
PIDFILE=/var/run/$NAME.pid

is_mounted() {
    MOUNT_POINT=$1
    grep " $MOUNT_POINT " /proc/mounts > /dev/null
}

check_and_restart() {
    TIMEOUT=60
    while [ $TIMEOUT -gt 0 ]; do
        if is_mounted /c && is_mounted /d; then
            echo "/c and /d are mounted. Starting $DESC: $NAME"
            start-stop-daemon --start --quiet --pidfile $PIDFILE --exec $DAEMON -- $DAEMON_OPTS
            return 0
        fi
        sleep 1
        TIMEOUT=$((TIMEOUT - 1))
    done
    echo "Error: /c and /d were not mounted within the timeout period."
    return 1
}

case "$1" in
    start)
        if is_mounted /c && is_mounted /d; then
            echo "/c and /d are mounted. Starting $DESC: $NAME"
            start-stop-daemon --start --quiet --pidfile $PIDFILE --exec $DAEMON -- $DAEMON_OPTS
        else
            echo "/c and /d are not mounted. Checking mounts asynchronously"
            check_and_restart &
        fi
        ;;
    stop)
        echo "Stopping $DESC: $NAME"
        start-stop-daemon --stop --quiet --pidfile $PIDFILE
        sleep 1
        killall minidlnad
        ;;
    restart)
        echo "Restarting $DESC: $NAME"
        start-stop-daemon --stop --quiet --pidfile $PIDFILE
        sleep 1
        start-stop-daemon --start --quiet --pidfile $PIDFILE --exec $DAEMON -- $DAEMON_OPTS
        ;;
    status)
        if ps aux | grep minidlnad | grep -v grep > /dev/null; then
            echo "$DESC is running"
            exit 0
        else
            echo "$DESC is not running"
            exit 1
        fi
        ;;
    *)
        echo "Usage: $0 {start|stop|restart|status}"
        exit 1
        ;;
esac

exit 0
```
  - b. Create the startup script for minidlna with `nano /etc/init.d/minidlna` and add the following content if you have only ONE mount point /c !:
```bash
#!/bin/sh
### BEGIN INIT INFO
# Provides:          minidlna
# Required-Start:    $local_fs $network
# Required-Stop:     $local_fs $network
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Start/stop MiniDLNA server
### END INIT INFO

DAEMON=/usr/sbin/minidlnad
DAEMON_OPTS="-f /etc/minidlna.conf"
NAME=minidlna
DESC="MiniDLNA server"
PIDFILE=/var/run/$NAME.pid

is_mounted() {
    MOUNT_POINT=$1
    grep " $MOUNT_POINT " /proc/mounts > /dev/null
}

check_and_restart() {
    TIMEOUT=60
    while [ $TIMEOUT -gt 0 ]; do
        if is_mounted /c; then
            echo "/c is mounted. Starting $DESC: $NAME"
            start-stop-daemon --start --quiet --pidfile $PIDFILE --exec $DAEMON -- $DAEMON_OPTS
            return 0
        fi
        sleep 1
        TIMEOUT=$((TIMEOUT - 1))
    done
    echo "Error: /c was not mounted within the timeout period."
    return 1
}

case "$1" in
    start)
        if is_mounted /c; then
            echo "/c is mounted. Starting $DESC: $NAME"
            start-stop-daemon --start --quiet --pidfile $PIDFILE --exec $DAEMON -- $DAEMON_OPTS
        else
            echo "/c is not mounted. Checking mount asynchronously"
            check_and_restart &
        fi
        ;;
    stop)
        echo "Stopping $DESC: $NAME"
        start-stop-daemon --stop --quiet --pidfile $PIDFILE
        sleep 1
        killall minidlnad
        ;;
    restart)
        echo "Restarting $DESC: $NAME"
        start-stop-daemon --stop --quiet --pidfile $PIDFILE
        sleep 1
        start-stop-daemon --start --quiet --pidfile $PIDFILE --exec $DAEMON -- $DAEMON_OPTS
        ;;
    status)
        if ps aux | grep minidlnad | grep -v grep > /dev/null; then
            echo "$DESC is running"
            exit 0
        else
            echo "$DESC is not running"
            exit 1
        fi
        ;;
    *)
        echo "Usage: $0 {start|stop|restart|status}"
        exit 1
        ;;
esac

exit 0
```

7. ` chmod +x /etc/init.d/minidlna`
8. ` update-rc.d minidlna defaults`
9. check if the startup script works with ` /etc/init.d/minidlna start`
10. The configuration file is located in `/etc/minidlna.conf`. You can edit the file with `nano /etc/minidlna.conf`.



## Prerequisites:

## zlib
dpkg -i zlib-1.3.1_1.3.1-1_sparc.deb # see parent folder

## sqlite3

Please notice the newer version `libsqlite3_347-1_sparc.deb` is not compatible with the version of minidlna. You need to use the older version `libsqlite3_3.35.5-1_sparc.deb` . 

dpkg -i libsqlite3_3.35.5-1_sparc.deb # see parent folder

~~dpkg -i libsqlite3_347-1_sparc.deb # see parent folder~~

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

open the minidlna.c file and add to the header section:
```c
#include <sys/queue.h> 

#ifndef LIST_EMPTY
#define LIST_EMPTY(head) ((head)->lh_first == NULL)
#endif
```


The original minidlna of the readynas version (Version 1.1.4) is installed in /usr/sbin/minidlna.

fes-a120d19nas:/nas-source/minidlna-1.3.3# dpkg -l | grep mini
ii  minidlna                          1.1.4-netgear1              lightweight DLNA/UPnP-AV server targeted at 

If you want to backup the original version of minidlna you can rename the file to minidlna-1.1.4-netgear1.
