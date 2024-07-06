# curl-8.8.0

depends on:
- openssl-3.2.1_3.2.1-1_sparc.deb

`./configure --with-openssl --disable-docs`


configure: Configured to build curl/libcurl:

```
  Host setup:       sparc-unknown-linux-gnu
  Install prefix:   /usr/local
  Compiler:         gcc -std=gnu99
   CFLAGS:          -O2 -pthread
   CPPFLAGS:        -isystem /usr/local/include
   LDFLAGS:         -L/usr/local/lib
   LIBS:            -lssl -lcrypto -lssl -lcrypto -lldap -lz -lrt

  curl version:     8.8.0
  SSL:              enabled (OpenSSL v3+)
  SSH:              no      (--with-{libssh,libssh2})
  zlib:             enabled
  brotli:           no      (--with-brotli)
  zstd:             no      (--with-zstd)
  GSS-API:          no      (--with-gssapi)
  GSASL:            no      (libgsasl not found)
  TLS-SRP:          enabled
  resolver:         POSIX threaded
  IPv6:             enabled
  Unix sockets:     enabled
  IDN:              no      (--with-{libidn2,winidn})
  Build docs:       disabled (--disable-docs)
  Build libcurl:    Shared=yes, Static=yes
  Built-in manual:  enabled
  --libcurl option: enabled (--disable-libcurl-option)
  Verbose errors:   enabled (--disable-verbose)
  Code coverage:    disabled
  SSPI:             no      (--enable-sspi)
  ca cert bundle:   no
  ca cert path:     no
  ca fallback:      no
  LDAP:             enabled (ancient OpenLDAP)
  LDAPS:            enabled
  RTSP:             enabled
  RTMP:             no      (--with-librtmp)
  PSL:              no      (--with-libpsl)
  Alt-svc:          enabled (--disable-alt-svc)
  Headers API:      enabled (--disable-headers-api)
  HSTS:             enabled (--disable-hsts)
  HTTP1:            enabled (internal)
  HTTP2:            no      (--with-nghttp2)
  HTTP3:            no      (--with-ngtcp2 --with-nghttp3, --with-quiche, --with-openssl-quic, --with-msh3)
  ECH:              no      (--enable-ech)
  WebSockets:       no      (--enable-websockets)
  Protocols:        DICT FILE FTP FTPS GOPHER GOPHERS HTTP HTTPS IMAP IMAPS IPFS IPNS LDAP LDAPS MQTT POP3 POP3S RTSP SMB SMBS SMTP SMTPS TELNET TFTP
  Features:         AsynchDNS HSTS HTTPS-proxy IPv6 Largefile NTLM SSL TLS-SRP UnixSockets alt-svc libz threadsafe
```
