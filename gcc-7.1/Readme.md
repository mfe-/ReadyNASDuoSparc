# Install

1. Copy this folder (gcc-7.1) to /c/opt/
2. Create a symlink from /opt/gcc-7.1 -> /c/opt/gcc-7.1 
3. decompress /opt/gcc-7.1/libexec/gcc/sparc-unknown-linux-gnu/7.1.0/cc1plus.tar.gz (this file was compressed dueo file size limit on github)
4. Add folder to LD_LIBRARY with "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/gcc-7.1/lib/"
5. Set CC and CXX param when compiling stuff e.g. ./configure CC=/opt/gcc-7.1/bin/gcc CXX=/opt/gcc-7.1/bin/g++
