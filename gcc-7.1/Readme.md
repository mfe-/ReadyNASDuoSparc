# Install
1. change into extracted directory `cd /ReadyNASDuoSparc`
2. `mkdir /c/opt` create an empty directory for storing applications
1. Copy this folder (gcc-7.1) to /c/opt/ with ` cp gcc-7.1/ /c/opt/ -Rf`
2. `cd /opt/`
2. Create a symlink from /opt/gcc-7.1 -> /c/opt/gcc-7.1 with `ln -s /c/opt/gcc-7.1/ gcc-7.1`
3. ` tar xvfz /opt/gcc-7.1/libexec/gcc/sparc-unknown-linux-gnu/7.1.0/cc1plus.tar.gz` (this file was compressed dueo file size limit on github)
4. Remove `rm /opt/gcc-7.1/libexec/gcc/sparc-unknown-linux-gnu/7.1.0/cc1plus.tar.gz`
5. Add folder to LD_LIBRARY with `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/gcc-7.1/lib/`
6. To make the above persistent after relogin execute `nano ~/.bashrc` and add the export command to the end of the file `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/gcc-7.1/lib/`. o apply the changes immediately, source the ~/.bashrc file: `source ~/.bashrc`
7. `chmod +x /opt/gcc-7.1/bin/*`
8. Check if gcc is working with `/opt/gcc-7.1/bin/gcc --version`
  9. if its fails with `/opt/gcc-7.1/bin/gcc: error while loading shared libraries: libiconv.so.2: cannot open shared object file: No such file or directory` install the required software for example with: `dpkg -i --force-overwrite libiconv-1.15_1.15-1_sparc.deb`.
  10. check again if gcc is working with `/opt/gcc-7.1/bin/gcc --version`
  11. if its fails with ` error while loading shared libraries: libisl.so.15: cannot open shared object file: No such file or directory` install the required software with `dpkg -i --force-overwrite isl-0.18_0.18-1_sparc.deb`
  12. if it fails with `cc1: error while loading shared libraries: libmpc.so.3: cannot open shared object file: No such file or directory` install the missing software with `dpkg -i --force-overwrite mpc-1.0.3_1.0.3-1_sparc.deb`
  13. if it fails with `cc1: error while loading shared libraries: libmpfr.so.4: cannot open shared object file: No such file or directory` install the missing software with  `dpkg -i --force-overwrite mpfr-3.1.5_3.1.5-1_sparc.deb`
  14. if it fails with `: error while loading shared libraries: libgmp.so.10: cannot open shared object file: No such file or directory` install the missing software with `dpkg -i --force-overwrite gmp-6.1.2_6.1.2-1_sparc.deb`
15. Compile a test program with
16. ```echo '#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}' | /opt/gcc-7.1/bin/gcc -I/usr/include -x c -o test -```
17. Set CC and CXX param when compiling stuff e.g. ./configure CC=/opt/gcc-7.1/bin/gcc CXX=/opt/gcc-7.1/bin/g++

# Requirements:

When installing the packages and you encounter an error while processing the deb packages try for example ` dpkg -i --force-overwrite ../mpc-1.0.3_1.0.3-1_sparc.deb     `

1. libisl
2. mpc
3. gmp
4. mpfr
 autoconf-2.69_1.5.3-1_sparc.deb 
 automake-1.15.1_1.15.1-1_sparc.deb 
 bison-3.0.4_3.0.4-1_sparc.deb 
 flex-2.6.4_1.5.3-1_sparc.deb 
 gettext-0.19.8.1_0.19.8.1-1_sparc.deb 
 libtool-2.4.6_2.4.6-1_sparc.deb 
 m4-1.4.18_1.4.18-1_sparc.deb 
 make-4.2.1_1.5.3-1_sparc.deb 
