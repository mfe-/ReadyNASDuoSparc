# git overview for sparc readynas duo

## Installing

1. Download zip file and place it on the readynas
2. unzip *-master.zip 
3. cd to extracted dir
4. cat git-2.21.0_2.21.0-1_sparc.parta* > git-2.21.0_2.21.0-1_sparc.deb
5. dpkg --force-overwrite -i openssl-1.0.2r.deb
6. dpkg --force-overwrite -i curl-7.64.1_7.deb
7. dpkg --force-overwrite -i git-2.21.0_2.2.deb
8. git config --global http.sslVerify false

## Building
1. openssl:
2. ./config enable-shared enable-egd
3. curl:
4. LDFLAGS="-L/usr/local/ssl/ -L/usr/local/ssl/lib/ -Wl,-rpath,/usr/local/ssl/,-rpath,/usr/local/ssl/lib/" LIBS="-ldl" ./configure --with-ssl=/usr/local/ssl/ --with-libssl-prefix=/usr/local/ssl/ --disable-ldap --enable-libcurl-option
5. check config.log if correct openssl 1.0.2r version is used. (Backup your old openssl files, remove them and copy from new openssl installation /usr/local/ssl/include/ header files to the old install dir /usr/include/openssl/ 
6. make
6. test curl with `curl https://orf.at/  -k`
7. git:
8. nano Makefile +2533
9. replace "$(QUIET_MSGFMT)mkdir -p $(dir $@) && $(MSGFMT) -o $@ $<" with "$(QUIET_MSGFMT)mkdir -p $(dir $@) && touch $@"
10. LDFLAGS="-L/usr/local/ssl/ -L/usr/local/ -L/usr/local/bin/ -Wl,-rpath,/usr/local/ssl/,-rpath,/usr/local/lib/" LIBS="-ldl" ./configure --with-curl=/usr/local/ --with-openssl=/usr/local/ssl/
11. NO_TCLTK=1 make    
12. git config --global core.editor "nano" (if you have installed nano)
13. git config --global http.sslVerify false 
