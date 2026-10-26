# Cross toolchain used for DIET

All binaries in the add-on were built on x86_64 Linux with a cross compiler that only emits
**SPARC V7** code (no hardware `sdiv`, see `../tools/sdiv-test.c`) and links against the
original Infrant glibc 2.3.2, so they run on the stock RAIDiator 2.6.17 kernel.

| Component | Version / configure |
|---|---|
| binutils | 2.42, `--target=sparc-linux --with-sysroot=$SYSROOT --disable-nls` |
| gcc | 12.4.0, `--target=sparc-linux --with-cpu=v7 --disable-shared --enable-languages=c,c++ --with-sysroot=$SYSROOT --disable-nls --disable-libsanitizer --disable-libquadmath --disable-libgomp` |
| sysroot | `/lib`, `/usr/lib`, `/usr/include` from NETGEAR's QEMU dev image `readynas_compile_environment.qcow` (Infrant `libc6 2.3.2.ds1-22sarge6.infrant1`) |
| kernel headers | replaced by sanitized 2.6.18 headers (`make ARCH=sparc headers_install`) – the raw headers in the image break modern code |

Common flags: `CFLAGS="-O2 -mcpu=v7 -fgnu89-inline -include rncompat.h"`.

Autoconf run-tests work without cross caches if `qemu-sparc-static` is registered with binfmt
and `QEMU_LD_PREFIX` points to the **full** mounted root of the QEMU dev image (the bare sysroot
segfaults).

Built with it (all checked with `objdump -d | grep sdiv` = 0):
busybox 1.36.1, dropbear 2024.86, rsync 3.4.1, Samba 3.6.25 (SMB2.02).
Taken unchanged from NETGEAR's firmware: `lvm` 2.01.04 and `libdevmapper` (initrd), `smartctl` 5.42
and the Infrant glibc/libstdc++ (RAIDiator root). None of the shipped binaries contains an `sdiv`.

Full build scripts for each package will follow in a later PR.
