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

## Create remote git repository on readynas

Sign on to SSH as root: ssh root@your_nas_ip
Create the folder for your repository: mkdir /c/git/what_ever && cd /c/git/what_ever
Initialise the repository: git – bare init
Exit SSH (exit)

### /etc/frontview/apache/addons/GITSCM.conf

```bash
SetEnv GIT_PROJECT_ROOT /c/git
SetEnv GIT_HTTP_EXPORT_ALL
#  ScriptAlias /git/ /opt/git-2.21.0/libexec/git-core/git-http-backend/  


RewriteCond %{QUERY_STRING} service=git-receive-pack [OR]
RewriteCond %{REQUEST_URI} /git-receive-pack$
RewriteRule ^/gitweb/ - [E=AUTHREQUIRED:yes]

AliasMatch ^/gitweb/(.*/objects/[0-9a-f]{2}/[0-9a-f]{38})$          /c/git/$1
AliasMatch ^/gitweb/(.*/objects/pack/pack-[0-9a-f]{40}.(pack|idx))$ /c/git/$1
ScriptAliasMatch \
	"(?x)^/gitweb/(.*/(HEAD | \
			info/refs | \
			objects/info/[^/]+ | \
			git-(upload|receive)-pack))$" \
	/opt/git-2.21.0/libexec/git-core/git-http-backend/$1

<LocationMatch "^/gitweb/">
	Order Deny,Allow
	Deny from env=AUTHREQUIRED
	AuthType Basic
	AuthName "Git Access"
	#Require group committers
	Satisfy Any
</LocationMatch>


Alias /GITSCM /c/var/www/GITSCM
<Location /GITSCM>
  Order deny,allow
  Options ExecCGI
#  AuthType Basic
#  Require valid-user
  Allow from all
</Location>

ScriptAlias /gitweb /c/var/www/GITSCM/gitweb/gitweb.cgi
<Directory "/c/var/www/GITSCM/gitweb">
        Options Indexes FollowSymlinks ExecCGI
	AllowOverride None
	Order allow,deny
        Allow from all
</Directory>


```


