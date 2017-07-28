<h1>ReadyNASDuoSparc</h1>

This repository contains information, binaries, scripts regarding the readynas duo v1 sparc machine from netgear.</p>
"The ReadyNAS RAIDiator 4.1.x firmware is a 32-bit SPARC Debian derivative mated to a Linux 2.6.17 kernel with numerous proprietary drivers"
For more information check: http://wiki.dietpc.org/index.php/DIET-PC_on_SPARC_ReadyNAS

<h2>Init</h2>
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
37. install texinfo version <5 otherwise you can compile gcc 4.6
38. install ils

Install gcc 4.6

39. install gcc 4.6 with gcc-4.6-compiled# ../gcc-4.6/configure CC=/opt/gcc-4/bin/gcc CXX=/opt/gcc-4/bin/g++ --enable-languages=c,c++ --prefix=/opt/gcc-4.6 --enable-shared --enable-__cxa_atexit --with-system-zlib --enable-nls --enable-clocale=gnu --enable-debug --with-cpu=v7 --enable-objc-gc sparc-linux --with-system-zlib=/usr/local  --with-mpc=/usr/local  --with-mpfr=/usr/local --with-gmp=/usr/local --with-isl=/usr/local/




