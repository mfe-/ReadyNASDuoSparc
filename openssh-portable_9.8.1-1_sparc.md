# openssh-portable_9.8.1-1_sparc

depends on:
- openssl-3.2.1_3.2.1-1_sparc.deb
- zlib-1.3.1_1.3.1-1_sparc.deb

## install



## configure
`./configure --with-pam --with-kerberos5 --with-ssl-dir=/usr/local/lib`

```
OpenSSH has been configured with the following options:
                     User binaries: /usr/local/bin
                   System binaries: /usr/local/sbin
               Configuration files: /usr/local/etc
                   Askpass program: /usr/local/libexec/ssh-askpass
                      Manual pages: /usr/local/share/man/manX
                          PID file: /var/run
  Privilege separation chroot path: /var/empty
            sshd default user PATH: /usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin
                    Manpage format: doc
                       PAM support: yes
                   OSF SIA support: no
                 KerberosV support: yes
                   SELinux support: no
                   libedit support: no
                   libldns support: no
  Solaris process contract support: no
           Solaris project support: no
         Solaris privilege support: no
       IP address in $DISPLAY hack: no
           Translate v4 in v6 hack: yes
                  BSD Auth support: no
              Random number source: OpenSSL internal ONLY
             Privsep sandbox style: rlimit
                   PKCS#11 support: yes
                  U2F/FIDO support: yes

              Host: sparc-unknown-linux-gnu
          Compiler: cc -std=gnu99
    Compiler flags: -g -O2 -pipe -Wall -Wpointer-arith -Wuninitialized -Wsign-compare -Wformat-security -Wno-unused-parameter -Wimplicit-fallthrough -fno-strict-aliasing -D_FORTIFY_SOURCE=2 -ftrapv -fno-builtin-memset  
Preprocessor flags: -I/usr/local/lib  -D_XOPEN_SOURCE=600 -D_BSD_SOURCE -D_DEFAULT_SOURCE -D_GNU_SOURCE -DOPENSSL_API_COMPAT=0x10100000L  
      Linker flags: -L/usr/local/lib  -Wl,-z,relro -Wl,-z,now -Wl,-z,noexecstack -Wl,-z,retpolineplt 
         Libraries: -lresolv -lrt -ldl -lutil 
     +for channels: -lcrypto  -lz
         +for sshd: -lcrypt  -lpam

PAM is enabled. You may need to install a PAM control file 
for sshd, otherwise password authentication may fail. 
Example PAM control files can be found in the contrib/ 
subdirectory

```
