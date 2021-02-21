# ReadyNASDuoSparc

This repository contains information, binaries, scripts regarding the readynas duo v1 sparc machine from netgear.</p>
"The ReadyNAS RAIDiator 4.1.x firmware is a 32-bit SPARC Debian derivative mated to a Linux 2.6.17 kernel with numerous proprietary drivers"
For more information check: http://wiki.dietpc.org/index.php/DIET-PC_on_SPARC_ReadyNAS

Qemu image of readynas https://community.netgear.com/t5/Community-Add-ons/Sparc-platform-development-envrionment-using-Qemu/td-p/720841 (dev version)

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

3. apt-get install grep --reinstall (rly important this was related to https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81421)
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

<br>https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81579 sanitizer_platform_limits_linux.cc:37:15: error: conflicting declaration ‘typedef __gid_t __kernel_gid_t’ </br>
<br>https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81451 - missing futex check - libgo/runtime/thread-linux.c:12:0 futex.h:13:12: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘long’</br>
<br>https://gcc.gnu.org/bugzilla/show_bug.cgi?id=56827 Building Go support for gcc 4.8.0 fails on Linux: undefined type ‘SockFilter’ </br>
https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81449 - runtime.inc:782:28: error: field ‘__sem_lock’ has incomplete type
</br>
https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82043 - error: redefinition of ... 
</br>
https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82208 - exec_linux.go:197:27: error: reference to undefined name 'SYS_UNSHARE'
</br>
https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82348 - math.lo.dep bytes.gox dependency dropped
</br>
https://gcc.gnu.org/bugzilla/show_bug.cgi?id=87013 -gcc8
</br>
https://gcc.gnu.org/bugzilla/show_bug.cgi?id=88060 - [Bug go/88060] ../../../gcc-8.2.0/libgo/go/syscall/libcall_linux_utimesnano.go:17:18: error: reference to undefined name ‘_AT_FDCWD’
</br>
https://gcc.gnu.org/bugzilla/show_bug.cgi?id=88135 - Bug 88135 - error: reference to undefined identifier ‘syscall.WEXITED’ 
</br>
https://gcc.gnu.org/bugzilla/show_bug.cgi?id=90527 - gcc9.1 alloc.c:72:7: error: implicit declaration of function ‘posix_memalign’

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
