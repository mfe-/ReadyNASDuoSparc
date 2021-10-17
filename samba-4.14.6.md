 CC=/opt/gcc-7.1/bin/gcc CXX=/opt/gcc-7.1/bin/g++ LDFLAGS="-L/usr/local/ssl/ -L/usr/local/ssl/lib/ -Wl,-rpath,/usr/local/ssl/,-rpath,/usr/local/ssl/lib/" LIBS="-ldl" ./configure      
 
 GPGME support not found. Try installing libgpgme11-dev or gpgme-devel and python-gpgme. Otherwise, use --without-gpgme to build without GPGME support or --without-ad-dc to build without the Samba AD DC.
 GPGME support is required for the GPG encrypted password sync feature   
