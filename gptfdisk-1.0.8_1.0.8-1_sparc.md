
# Install gptfdisk-1.0.8_1.0.8-1_sparc

1. curl -kLO https://sourceforge.net/projects/gptfdisk/files/gptfdisk/1.0.8/gptfdisk-1.0.8.tar.gz
2. tar -xzf gptfdisk-1.0.8.tar.gz
3. cd gptfdisk-1.0.8
4. make
5. check make install

# Update GetPhysBlockSize in diskio-unix.cc

Otherwise it would result in unknown reference BLKPBSZGET error.

Set default blocksize to 1024.

```
int DiskIO::GetPhysBlockSize(void) {
   int err = -1, physBlockSize = 0;

   // If disk isn't open, try to open it....
   if (!isOpen) {
      OpenForRead();
   } // if

   if (isOpen) {
#if defined __linux__ && !defined(EFI)
            #ifndef BLKPBSZGET
      #define BLKPBSZGET _IO(0x12,123) // Define a fallback value if not defined
      #endif
      err = ioctl(fd, BLKPBSZGET, &physBlockSize);
#endif
   } // if (isOpen)
   if (err == -1)
      physBlockSize = 1024;
   return (physBlockSize);
} // DiskIO::GetPhysBlockSize(void)


```

# Update Makefile

The version of gptfdisk did not provide an install therefore the content for Makefile was updated to:

```bash
CFLAGS+=-D_FILE_OFFSET_BITS=64
#CXXFLAGS+=-Wall -D_FILE_OFFSET_BITS=64 -D USE_UTF16
CXXFLAGS+=-Wall -D_FILE_OFFSET_BITS=64
LDFLAGS+=
LIB_NAMES=crc32 support guid gptpart mbrpart basicmbr mbr gpt bsd parttypes attributes diskio diskio-unix
MBR_LIBS=support diskio diskio-unix basicmbr mbrpart
LIB_OBJS=$(LIB_NAMES:=.o)
MBR_LIB_OBJS=$(MBR_LIBS:=.o)
LIB_HEADERS=$(LIB_NAMES:=.h)
DEPEND= makedepend $(CXXFLAGS)

PREFIX=/usr/local
BINDIR=$(PREFIX)/bin
LIBDIR=$(PREFIX)/lib

all:	cgdisk gdisk sgdisk fixparts

gdisk:	$(LIB_OBJS) gdisk.o gpttext.o
    $(CXX) $(LIB_OBJS) gdisk.o gpttext.o $(LDFLAGS) -luuid $(LDLIBS) -o gdisk
#	$(CXX) $(LIB_OBJS) gdisk.o gpttext.o $(LDFLAGS) -licuio -licuuc -luuid -o gdisk

cgdisk: $(LIB_OBJS) cgdisk.o gptcurses.o
    $(CXX) $(LIB_OBJS) cgdisk.o gptcurses.o $(LDFLAGS) -luuid -lncursesw $(LDLIBS) -o cgdisk
#	$(CXX) $(LIB_OBJS) cgdisk.o gptcurses.o $(LDFLAGS) -licuio -licuuc -luuid -lncurses -o cgdisk

sgdisk: $(LIB_OBJS) sgdisk.o gptcl.o
    $(CXX) $(LIB_OBJS) sgdisk.o gptcl.o $(LDFLAGS) -luuid -lpopt $(LDLIBS) -o sgdisk
#	$(CXX) $(LIB_OBJS) sgdisk.o gptcl.o $(LDFLAGS) -licuio -licuuc -luuid -lpopt -o sgdisk

fixparts: $(MBR_LIB_OBJS) fixparts.o
    $(CXX) $(MBR_LIB_OBJS) fixparts.o $(LDFLAGS) $(LDLIBS) -o fixparts

test:
    ./gdisk_test.sh

lint:	#no pre-reqs
    lint $(SRCS)

clean:	#no pre-reqs
    rm -f core *.o *~ gdisk sgdisk cgdisk fixparts

# what are the source dependencies
depend: $(SRCS)
    $(DEPEND) $(SRCS)

install: gdisk cgdisk sgdisk fixparts
    install -d $(BINDIR)
    install -m 755 gdisk $(BINDIR)
    install -m 755 cgdisk $(BINDIR)
    install -m 755 sgdisk $(BINDIR)
    install -m 755 fixparts $(BINDIR)
    install -d $(LIBDIR)
    install -m 644 $(LIB_NAMES:=.a) $(LIBDIR)

uninstall:
    rm -f $(BINDIR)/gdisk
    rm -f $(BINDIR)/cgdisk
    rm -f $(BINDIR)/sgdisk
    rm -f $(BINDIR)/fixparts
    rm -f $(LIBDIR)/$(LIB_NAMES:=.a)

$(OBJS):
    $(CRITICAL_CXX_FLAGS) 

# makedepend dependencies below -- type "makedepend *.cc" to regenerate....
# DO NOT DELETE
``
