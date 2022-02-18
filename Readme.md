# ReadyNASDuoSparc

This repository contains information, binaries, scripts regarding the readynas duo v1 sparc machine from netgear.</p>
"The ReadyNAS RAIDiator 4.1.x firmware is a 32-bit SPARC Debian derivative mated to a Linux 2.6.17 kernel with numerous proprietary drivers"

Qemu image of readynas <https://community.netgear.com/t5/Community-Add-ons/Sparc-platform-development-envrionment-using-Qemu/td-p/720841> (dev version)

## Hints

1. If there is no space left on the root partition you can workaround the issue with: `mount --bind /path/to/dir/with/plenty/of/space /tmp`
2. Better create a symlink for /usr/local/ -> /c/usr/local/
3. create dpkg packages with `checkinstall --dpkgflags=--force-overwrite --exclude /usr/local/share/ make install`
4. use `dpkg -i --force-overwrite whatever.deb` to install debian packages from this repository.
5. If you retriev error messages like `debian-sparc:~# curl --version
curl: error while loading shared libraries: libnettle.so.6: cannot open shared object file: No such file or directory` when executing an installed application (in this case it would be curl), make sure you installed the required library (in this example it would be libnettle) and exported the enviroment variable LD_LIBRARY_PATH with the proper paths.

## Start

1. Download this github repository with `wget --no-check-certificate https://github.com/mfe-/ReadyNASDuoSparc/archive/master.zip`
2. Unzip and install your required software
3. You can execute steps 1 to 12 of init.
4. It makes sense to export some enviroment variables when logging into bash.
    a. You can make use of `.bashrc`
    b. add the following lines to export some paths

```bash
        export PATH=$PATH:/opt/rfw/bin/:/usr/local/ssl/bin/:/opt/git-2.21.0/bin/
        export PATH=$HOME/.local/bin:$PATH
        export LD_LIBRARY_PATH=/opt/gcc-4.6.0/lib/:/usr/local/ssl/lib/:/usr/local/lib/
```

## Init

I reset my readynas and did the following steps:

Because netgear turned off there package repository you can't get the customized netgear packages like libc6-dev for the debian system.
You can get the contained files from the [libc6-dev](https://github.com/mfe-/ReadyNASDuoSparc/tree/master/libc6-dev) folder. You only need to copy them to the system root partion /.

1. Remove netgear sources from apt.sources
2. apt-get update

Fix some broken stuff on the readynas

3. apt-get install grep --reinstall (rly important this was related to <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81421>)
4. Apt-get install nano -y
5. apt-get install less --reinstall -y
6. useradd -s /bin/false man
7. apt-get install man-db
8. apt-get install manpages-dev

9. apt-get install --reinstall perl
10. Apt-get install screen
11. Apt-get install less
12. ln -s /usr/bin/less /usr/bin/sensible-pager
13. Apt-get install checkinstall

Do not execute the underneath steps. Those are only for documentation purposes.
Install gcc 3.3.5 with apt

14. apt-get install gcc
15. gcc --v
Reading specs from /usr/lib/gcc-lib/sparc-linux/3.3.5/specs
Configured with: ../src/configure -v --enable-languages=c,c++,java,f77,pascal,objc,ada,treelang --prefix=/usr --mandir=/usr/share/man --infodir=/usr/share/info --with-gxx-include-dir=/usr/include/c++/3.3 --enable-shared --enable-__cxa_atexit --with-system-zlib --enable-nls --without-included-gettext --enable-clocale=gnu --enable-debug --enable-java-gc=boehm --enable-java-awt=xlib --with-cpu=v7 --enable-objc-gc sparc-linux
Thread model: posix
gcc version 3.3.5 (Debian 1:3.3.5-13)

Install gcc 4.0.4 from source

16. download mpc-0.9.tar.gz, gmp-4.3.2.tar, mpfr-3.1.1.tar.gz and extract them
17. download and extract gcc-4.0.4.tar.gz
18. rename the extracted folder to mpc, gmp, mpfr and move them to into the extracted gcc source folder
19. create a new folder outside of the gcc sourcefolder called gcc-4.0.4-compiled
20. cd to gcc-4.0.4-compiled
21. ../gcc-4.0.4/configure --prefix=/opt/gcc-4.0.4 --mandir=/usr/share/man --infodir=/usr/share/info --with-cpu=v7 --enable-objc-gc --enable-shared --enable-__cxa_atexit --with-system-zlib --enable-nls --without-included-gettext --enable-clocale=gnu --enable-languages=c,c++ --build=sparc-linux --host=sparc-linux
22. make && make install
23. export LD_LIBRARY_PATH=/opt/gcc-4/lib:/usr/local/lib/ or add it to /root/.bashrc
24. checkinstall --dpkgflags=--force-overwrite make install #create .deb package
Use the new gcc by setting CC and CXX. For example ./configure CC=/opt/gcc-4/bin/gcc CXX=/opt/gcc-4/bin/g++

Install last gnu enviroment libraries

25. install with dpkg -i -f perl-base_5.8.8-7.infrant2_sparc.deb, perl-modules_5.8.8-7.infrant2_all.deb, perl_5.8.8-7.infrant2_sparc.deb from this repository
26. install last make
27. install last automake
28. install last m4
29. install last gmp, mpfr, mpc
30. install libiconv
31. install Bison
32. install libtool
33. install ncurse
34. install expat
35. install libxml
36. install gettext
37. install texinfo version <5 otherwise you can't compile gcc 4.6
38. install ils

Install gcc 4.6

39. install gcc 4.6 with gcc-4.6-compiled# ../gcc-4.6/configure CC=/opt/gcc-4/bin/gcc CXX=/opt/gcc-4/bin/g++ --enable-languages=c,c++ --prefix=/opt/gcc-4.6 --enable-shared --enable-__cxa_atexit --with-system-zlib --enable-nls --enable-clocale=gnu --enable-debug --with-cpu=v7 --enable-objc-gc sparc-linux --with-system-zlib=/usr/local  --with-mpc=/usr/local  --with-mpfr=/usr/local --with-gmp=/usr/local --with-isl=/usr/local/

Compile kernel modules

1. Download last firmware from [Netgear](https://kb.netgear.com/2649/NETGEAR-Open-Source-Code-for-Programmers-GPL) ReadyNAS devices running RAIDiator 4.1 (NV / NV+ / 1100 / Duo) GPL Bundle, RAIDiator 4.1.16

### Issues

<br><https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81579> sanitizer_platform_limits_linux.cc:37:15: error: conflicting declaration ‘typedef __gid_t__kernel_gid_t’ </br>
<br><https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81451> - missing futex check - libgo/runtime/thread-linux.c:12:0 futex.h:13:12: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘long’</br>
<br><https://gcc.gnu.org/bugzilla/show_bug.cgi?id=56827> Building Go support for gcc 4.8.0 fails on Linux: undefined type ‘SockFilter’ </br>
<https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81449> - runtime.inc:782:28: error: field ‘__sem_lock’ has incomplete type
</br>
<https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82043> - error: redefinition of ...
</br>
<https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82208> - exec_linux.go:197:27: error: reference to undefined name 'SYS_UNSHARE'
</br>
<https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82348> - math.lo.dep bytes.gox dependency dropped
</br>
<https://gcc.gnu.org/bugzilla/show_bug.cgi?id=87013> -gcc8
</br>
<https://gcc.gnu.org/bugzilla/show_bug.cgi?id=88060> - [Bug go/88060] ../../../gcc-8.2.0/libgo/go/syscall/libcall_linux_utimesnano.go:17:18: error: reference to undefined name ‘_AT_FDCWD’
</br>
<https://gcc.gnu.org/bugzilla/show_bug.cgi?id=88135> - Bug 88135 - error: reference to undefined identifier ‘syscall.WEXITED’
</br>
<https://gcc.gnu.org/bugzilla/show_bug.cgi?id=90527> - gcc9.1 alloc.c:72:7: error: implicit declaration of function ‘posix_memalign’

#### init

```
apt-get update
mkdir /c/opt
mkdir /c/usr
mkdir /c/usr/local
mv /opt/* /c/opt/
rm /opt/ -Rf
ln -s /c/opt/ /opt
mv /usr/local/* /c/usr/local/
rm /usr/local/ -R
ln -s /c/usr/local/ /usr/local
apt-get install grep --reinstall
apt-get install nano -y
apt-get install less -y
useradd -s /bin/false man
apt-get install man-db -y
apt-get install less -y
ln -s /usr/bin/less /usr/bin/sensible-pager
apt-get install screen -y
apt-get install gcc g++ -y

```

## About Readynas duo

Since the page <http://wiki.dietpc.org/index.php/DIET-PC_on_SPARC_ReadyNAS> is down, I used the timemachine to go back in time and "save" the content of the "dietpc" page in this markdown file.

### Introduction

Well, I never thought that I'd have an opportunity to put my 32-bit SPARC port of DIET-PC to actual use, but then this Netgear ReadyNAS Duo hardware fell in my lap! Very popular in its day, but a bit of an underperforming relic nowadays. Let's see if we can put it to slightly better use with more modern software (for the most part, at least - I am limited by the development environments that I use as far as glibc and Xorg baselines are concerned, so in these respects I can at best upgrade the ReadyNAS from a Sarge-like machine (glibc 2.3.2, no udev) to an Etch-like machine (glibc 2.3.6, with udev)). The 2.6.17 kernel is a pretty elderly, but it's good enough for inotify, udev and GPT.

### The Hardware

ReadyNASDuo.jpg

It's a strange little beast, based on a custom Infrant IT3107 ASIC with a 280 MHz SPARC (32-bit) CPU, quite unlike anything else I've seen in the NAS market. It has a PCI bus, but the only thing on it are the Via USB chipsets; everything else is on proprietary platform busses. The platform is named "Padre".

The ergonomic design of this unit is rather nice, although how often you are going to replace hard disks in a two-disk unit? Do we really need hot-swap drive bays? The variable speed 60mm fan is unusual and much appreciated, as it keeps the noise down fairly well.

| Type  | MAke/Model  | Properties  |
|---|---|---|
| CPU| Infrant IT3107 (sparcv8) |280 MHz, XOR offload engine, DES crypto engine|
|RAM| Unigen DDR400 SODIMM |256 MiB|
|NIC| Padre GMac (custom) |Gigabit ethernet|
|Storage| Hynix NAND MTD |64 GiB|
|Storage |Controller Unknown (custom) |2x SATA (<= 1.5 Gbit/s) presenting as IDE|
|USB Controller |Via VT82xxxxx 1.1 / Via 2.0 |2x UHCI (1.1) ports, 1x EHCI (2.0) port|
|Serial |Padre serial (custom) |3.3V @ 9600 8n1, pins only, behind sticker on rear|
|Cooling | Generic |60mm fan |

### Official Firmware

The ReadyNAS RAIDiator 4.1.x firmware is a 32-bit SPARC Debian derivative mated to a Linux 2.6.17 kernel with numerous proprietary drivers. Netgear have done the right thing by GPL and provided them as external modules; with a couple of minor tweaks, the provided kernel code does compile from the source provided (with some caveats), and the configuration does seems to match their kernel. The userspace appears to be a derivative of Debian 3.1 (Sarge), with GLibC 2.3.2 and an old MAKEDEV-style /dev.

Hard disks are formatted as a software RAID device containing an ext3 filesystem with a non-standard 16k block size (the maximum size for most platforms - including x86 and x86_64 - is 4k; this can make data recovery from a failed ReadyNAS rather difficult). Netgear use a modified version of Linux md RAID called X-RAID, which appears to have some kind of DMA engine offload capability. It's format-compatible with ordinary md RAID, but you have to use Infrant's "mdconfig" tool rather than mdadm.

The kernel, ext2 initrd, and installation tarball for the Debian userspace - all encrypted - reside in /dev/mtd1, which is all of the available NAND flash minus the 1 MiB "iboot" boot loader (unencrypted, in /dev/mtd0). There is a simple container format, (poorly) documented here; I'll talk more about this later. The boot loader decrypts the kernel and initrd into RAM and then executes the kernel; on first run the initrd will initialise a RAID device and ext3 filesystem, and then install the third file (root.tgz) onto it; otherwise it will just pivot_root into the hard disk userspace.

### Official Firmware

The ReadyNAS RAIDiator 4.1.x firmware is a 32-bit SPARC Debian derivative mated to a Linux 2.6.17 kernel with numerous proprietary drivers. Netgear have done the right thing by GPL and provided them as external modules; with a couple of minor tweaks, the provided kernel code does compile from the source provided (with some caveats), and the configuration does seems to match their kernel. The userspace appears to be a derivative of Debian 3.1 (Sarge), with GLibC 2.3.2 and an old MAKEDEV-style /dev.

Hard disks are formatted as a software RAID device containing an ext3 filesystem with a non-standard 16k block size (the maximum size for most platforms - including x86 and x86_64 - is 4k; this can make data recovery from a failed ReadyNAS rather difficult). Netgear use a modified version of Linux md RAID called X-RAID, which appears to have some kind of DMA engine offload capability. It's format-compatible with ordinary md RAID, but you have to use Infrant's "mdconfig" tool rather than mdadm.

The kernel, ext2 initrd, and installation tarball for the Debian userspace - all encrypted - reside in /dev/mtd1, which is all of the available NAND flash minus the 1 MiB "iboot" boot loader (unencrypted, in /dev/mtd0). There is a simple container format, (poorly) documented here; I'll talk more about this later. The boot loader decrypts the kernel and initrd into RAM and then executes the kernel; on first run the initrd will initialise a RAID device and ext3 filesystem, and then install the third file (root.tgz) onto it; otherwise it will just pivot_root into the hard disk userspace.

### OEM kernel modules

Any custom software for the ReadyNas Duo will have to include at least some of the binary-only non-GPL kernel modules that come with the official firmware. Earlier official firmware has modules for 2.6.17.8, later firmware has modules for 2.6.17.14; those are your only kernel options.

Here's what I know about the modules:

| Name  | Purpose  |
|---|---|
|miniuhci.ko| Provides raw access to a USB device via /dev/miniuhci (char 58,0); used by official firmware during installation a stand-in for uhci_hcd + usb_storage|
|padre_i2c_hwmon.ko |LM75 sensor (not used on Duo)|
|padre_io.ko |SATA and X_RAID; instantiates a generic IDE controller (requires CONFIG_IDE_GENERIC=y) - essential|
|padre_wb83782d.ko| Winbond 83782d sensor (not used on Duo)|
|padre_des.ko |Hardware cryptography (DES) driver|
|padre_i2c.ko| I2C bus driver - essential|
|padre_lcd.ko |LCD panel driver (not used on Duo)|
|padre_gmac.ko |Gigabit ethernet driver - essential|
|padre_i2c_rtc.ko| Real-Time Clock driver - essential|
|padre_p0_led_button.ko |LED driver / button sensor - needed to stop LEDs blinking!|

### Own Code Compilation

I encountered a great many problems getting my own kernel and glibc builds to work on this box.

Why do any ReadyNAS-specific code compilation when I already have a working OEM kernel and 32-bit SPARC DIET-PC port, you ask? Because:

My DIET-PC build of GlibC 2.3.6 didn't work on ReadyNAS, for some I reasons I found out later, and the 2.3.2 GlibC provided with the official kernel is too old for the rest of my userspace binaries, which have symbol dependencies on at least GLibC 2.3.4 and possibly later.
The official firmware's kernel has a hard-coded command line that I needed to change. In particular, "init=/linuxrc" and "rw" are a problem - for DIET-PC, I need "init=/sbin/init" (the default) and "ro").
The official firmware's kernel has a default maximum initrd size of 16k, which is too small for the ambitious userspace I wanted. You can override this default on the command line, but see above regarding compiled-in command line!
The official firmware's kernel lacks compiled in support for NAND flash and SquashFS or JFFS2, which would be very handy for creating a "real" (non-initrd) root filesystem with integral compression.
The NAND partitioning is hard-coded into the NAND driver, and I'd need to change this to add a /dev/mtd2 to put SquashFS or (preferably) JFFS2 on. Root-on-JFFS2 also needs a special command line parameter (rootfstype=jffs2).

### Gotchas

Long story short, these are the things you need to watch out for:

The ReadyNAS' CPU uses an unusual instruction set (apparently a sparcv8 variant, although glibc must be compiled with -mcpu=v7) that requires a special glibc patch. If you don't apply this, then ld-linux.so.2 will die with an "Illegal Instruction" and you will get nowhere. The patch is provided in the GPL tarball, under glibc-2.3.2.ds1/debian/patches/infrant.dpatch. I've updated the patch for glibc 2.3.6 and made it available here. I am trying to forward-port the patch to a later version of glibc, but this is very difficult due to widespread abandonment of any 32-bit SPARC ABI other than sparcv8plus, which requires a sparcv9 CPU.
The kernel must be compiled with gcc 3.3, and if you use anything other than gcc 3.3.5 as provided for Debian Sarge (you can find the debs on archive.debian.org and install them as a downgrade on Etch) you will encounter additional problems with kernel modules containing ".eh_frame" sections with R_SPARC_UA32 symbols that are not understood by the loader and cause "Unknown relocation: 17" errors.
If you do encounter "Unknown relocation: 17" errors, you can run "strip --strip-unneeded -R .eh_frame" on the *.ko files to make the problem go away.
Certain kernel features cannot be altered without rendering the essential binary-only OEM kernel modules (in particular padre_gmac.ko, the gigabit NIC driver) inoperable. For safety, you should leave CONFIG_MODVERSIONS enabled so that you can see when you have strayed from the path. Non-obvious requirements include CONFIG_OPROFILE, CONFIG_SCHEDSTATS, CONFIG_QUOTA and CONFIG_ATALK. You must not turn CONFIG_NETCONSOLE on (even as a module).
For unknown reasons, using an initramfs (gzip-compressed cpio archive) as your initrd doesn't work. You will have to use an actual initrd with a supported filesystem (e.g. ext2 or ext3)
