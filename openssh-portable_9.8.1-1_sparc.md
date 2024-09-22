# openssh-portable_9.8.1-1_sparc

depends on:
- [openssl-3.2.1_3.2.1-1_sparc.deb](https://github.com/mfe-/ReadyNASDuoSparc/blob/master/openssl-3.2.1_3.2.1-1_sparc.deb)
- [zlib-1.3.1_1.3.1-1_sparc.deb](https://github.com/mfe-/ReadyNASDuoSparc/blob/master/zlib-1.3.1_1.3.1-1_sparc.deb)

To enable SSH login on the ReadyNAS Duo v1, you need to install the "Enable Root SSH Access" add-on, which can be found on the [Add-ons for RAIDiator 4.1.3+ (Sparc)](https://kb.netgear.com/24546/Add-ons-for-RAIDiator-4-1-3-Sparc?article=24546) page.

After installing the add-on via the web interface, SSH login becomes possible. The ReadyNAS Duo v1 is shipped with an OpenSSH server version `1:4.3p2-5~bpo.1.netgear1`, which is quite old.

Since this old version uses outdated cryptographic libraries, connecting from a modern system will certainly fail with the following error message:

```bash
ssh root@readynas.duo.v1
Unable to negotiate with [NASIP] port 22: no matching key exchange method found. Their offer: diffie-hellman-group-exchange-sha1,diffie-hellman-group14-sha1,diffie-hellman-group1-sha1
```

Someone might ask how we can upgrade the OpenSSH service if it is itself required during the upgrade process. The solution is quite simple. The original Netgear SSH executable is located in `/usr/sbin/sshd`. This executable will be started during bootup by an init script located in `/etc/init.d/ssh`. The configuration is located in `/etc/ssh/sshd_config`, which also specifies the default port `22` on which the SSH service is listening.

To upgrade the SSH version, we can install the new version into the location `/usr/local/`, specifically `/usr/local/bin/ssh`, which will use the config file from `/etc/ssh/opensshd_config` and set the port to something other than `22`. This way, two SSH services can run in parallel. The next step is testing whether one can log in to the new SSH service with a reboot of the NAS. If everything works, we can exchange the port numbers from the old and new services so that the new service uses the default port. After a reboot and verifying that login still works, we can finally disable the old SSH service.



## Remarks

Readynas installed openssh

```bash
dpkg -l | grep  openssh
ii  openssh-client                    1:4.3p2-5~bpo.1.netgear1    Secure shell client, an rlogin/rsh/rcp repla
ii  openssh-server                    1:4.3p2-5~bpo.1.netgear1    Secure shell server, an rshd replacement
```

The original startup script is located in `cat /etc/init.d/ssh`
which will start `/usr/sbin/sshd`



## install

0. Create a backup of the folder `/etc/*` and store it somewhere.
1.  Install the package: `dpkg -i --force-overwrite openssh-portable_9.8.1-1_sparc.deb`.
2. This will install OpenSSH to `/usr/local/`. (See also `dpkg-deb --contents openssh-portable_9.8.1-1_sparc.deb`).
3. Execute `/usr/local/bin/ssh --version`.
   - If you get `/usr/local/bin/ssh: error while loading shared libraries: libcrypto.so.3: cannot open shared object file: No such file or directory`, install the missing library OpenSSL with `dpkg -i --force-overwrite openssl-3.2.1_3.2.1-1_sparc.deb`. Execute again `/usr/local/bin/ssh --version`.
   - If the error still occurs, check if the output of `echo $LD_LIBRARY_PATH` contains `/usr/local/lib`.
     - If the output is missing `/usr/local/lib`, execute `nano ~/.bashrc`. Add at the bottom of the file the line `export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH`. Hit `CTRL+X`. It asks to save changes, press `Y` and hit `Enter`.
     - Execute `source ~/.bashrc` so that the changes take effect.
     - Now `echo $LD_LIBRARY_PATH` should output `/usr/local/lib`.
4. Generate the RSA key: `/usr/local/bin/ssh-keygen -t rsa -f /etc/ssh/openssh_host_rsa_key -N ''`. Notice: Do not use `ssh-keygen` otherwise it will use the outdated tool located in `/usr/bin/`.
5. Create the necessary directory: `mkdir -p /var/empty && chmod 755 /var/empty`.
6. Create the new config file with `nano /etc/ssh/opensshd_config` and copy the underneath content into it. Hit CTRL+X and Y to save the changes:
```bash
# Package generated configuration file
# See the sshd(8) manpage for details

# What ports, IPs and protocols we listen for
Port 2222
# Use these options to restrict which interfaces/protocols sshd will bind to
#ListenAddress ::
#ListenAddress 0.0.0.0
Protocol 2
# HostKeys for protocol version 2
HostKey /etc/ssh/openssh_host_rsa_key
#HostKey /etc/ssh/ssh_host_dsa_key
#Privilege Separation is turned on for security
#UsePrivilegeSeparation yes

# Lifetime and size of ephemeral version 1 server key
#KeyRegenerationInterval 3600
#ServerKeyBits 768

# Logging
SyslogFacility AUTH
LogLevel INFO

# Authentication:
LoginGraceTime 120
PermitRootLogin yes
StrictModes yes

RSAAuthentication yes
PubkeyAuthentication yes
#AuthorizedKeysFile	%h/.ssh/authorized_keys

# Don't read the user's ~/.rhosts and ~/.shosts files
IgnoreRhosts yes
# For this to work you will also need host keys in /etc/ssh_known_hosts
#RhostsRSAAuthentication no
# similar for protocol version 2
HostbasedAuthentication no
# Uncomment if you don't trust ~/.ssh/known_hosts for RhostsRSAAuthentication
#IgnoreUserKnownHosts yes

# To enable empty passwords, change to yes (NOT RECOMMENDED)
PermitEmptyPasswords no

# Change to yes to enable challenge-response passwords (beware issues with
# some PAM modules and threads)
ChallengeResponseAuthentication no

# Change to no to disable tunnelled clear text passwords
PasswordAuthentication yes

# Kerberos options
#KerberosAuthentication no
#KerberosGetAFSToken no
#KerberosOrLocalPasswd yes
#KerberosTicketCleanup yes

# GSSAPI options
#GSSAPIAuthentication no
#GSSAPICleanupCredentials yes

X11Forwarding yes
X11DisplayOffset 10
PrintMotd no
PrintLastLog yes
TCPKeepAlive yes
#UseLogin no

#MaxStartups 10:30:60
#Banner /etc/issue.net

# Allow client to pass locale environment variables
AcceptEnv LANG LC_*

Subsystem sftp /usr/lib/openssh/sftp-server

#UsePAM yes
```

7. Review the config file `cat /etc/ssh/opensshd_config`
   - Make sure the port is set to `2222`. This is our temporary port number.
   - Ensure the `HostKey` points to the correct file which was previously created: `HostKey /etc/ssh/openssh_host_rsa_key`.
   - `PasswordAuthentication yes` is set to true. You might want to disable this later. For testing purposes, we enable it.
   - PAM should be disabled by commenting it out: `#UsePAM yes`.
8. Start the service: `/usr/local/sbin/sshd -f /etc/ssh/opensshd_config`.
9. Verify that the service is running with `ps aux | grep sshd | grep -v grep`. This should print 3 entries:
   - `0:00 /usr/sbin/sshd`
   - `sshd: root@pts/0`
   - `sshd: /usr/local/sbin/sshd -f /etc/ssh/opensshd_config`
   The first and second outputs show that the old SSH service is running, including the current SSH session. The last output shows our new OpenSSH service running.
10. Switch to your desktop machine and try to connect to the new SSH service by specifying the port `2222` with `ssh -p 2222 root@[your.nas.ip]`. You will probably see something like this:

```
The authenticity of host '[your.nas.ip]:2222 ([your.nas.ip]:2222)' can't be established.
RSA key fingerprint is SHA256:deiSB7JlVz7Y/NxJJRIJF9gP3FrcW6NfavcEmb1Q.
This key is not known by any other names.
Are you sure you want to continue connecting (yes/no/[fingerprint])? y
Please type 'yes', 'no' or the fingerprint: yes
```

11. If you can successfully log in to the new SSH server instance, reboot your NAS to ensure that you didn't break any configurations of the legacy SSH server.
12. After the reboot, create the init script.
13. Open the file with `nano /etc/init.d/opensshd` and add the following content, then save the file.

```bash
#!/bin/sh
### BEGIN INIT INFO
# Provides:          opensshd
# Required-Start:    $remote_fs $syslog
# Required-Stop:     $remote_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Start daemon at boot time
# Description:       Enable service provided by daemon.
### END INIT INFO

# Add /usr/local/bin/ to PATH
export PATH=/usr/local/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

case "$1" in
  start)
    echo "Starting opensshd"
    /usr/local/sbin/sshd -f /etc/ssh/opensshd_config > /tmp/sshd_output 2>&1 &
  ;;
  stop)
    echo "Stopping opensshd"
    PID=$(ps aux | grep '/usr/local/sbin/sshd -f /etc/ssh/opensshd_config' | grep -v grep | awk '{print $2}')
    if [ -n "$PID" ]; then
        kill $PID
    fi
  ;;
  status)
    if ps aux | grep '/usr/local/sbin/sshd -f /etc/ssh/opensshd_config' | grep -v grep > /dev/null
    then
        echo "opensshd is running"
    else
        echo "opensshd is not running"
    fi
  ;;
  *)
    echo "Usage: /etc/init.d/opensshd {start|stop|status}"
    exit 1
  ;;
esac

exit 0
```

14. Make the script executable: `chmod +x /etc/init.d/opensshd`
15. Register the script to run at startup: `update-rc.d opensshd defaults`
16. Start the service: `/etc/init.d/opensshd start`
17. Verify that the SSH server `/usr/local/sbin/sshd -f` is running with `ps aux | grep sshd | grep -v grep`
18. If the service is up and running, try logging in from your desktop machine with `ssh -p 2222 root@[your.nas.ip]`
19. If you can log in, reboot your NAS. The new SSH instance should start automatically.
20. Again, try to log in via SSH with `ssh -p 2222 root@[your.nas.ip]` and `ssh -p 22 root@[your.nas.ip]`.
21. Now that we have confirmed both SSH server instances can be accessed, we can switch the ports:
    1. Change the value `Port 2222` in `/etc/ssh/opensshd_config` to `Port 22`
    2. Change the value `Port 22` in `/etc/ssh/sshd_config` to `Port 2222`
22. Reboot the NAS. After the reboot, the new OpenSSH instance will be using the default port `22` and can be accessed with `ssh root@[your.nas.ip]`.
    1. For the first login, you will probably get the following warning because the host key is stored with the associated machine name AND port (which we previously switched):
     ```bash
     ssh root@[your.nas.ip]
     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
     @    WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!     @
     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
     IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY!
     Someone could be eavesdropping on you right now (man-in-the-middle attack)!
     It is also possible that a host key has just been changed.
     The fingerprint for the RSA key sent by the remote host is
     SHA256:deiSB7JlVz7Y/NBsHxJJRIJ3FrcW6NfavcEmb1Q.
     Please contact your system administrator.
     Add correct host key in /home/[yourProfileName]/.ssh/known_hosts to get rid of this message.
     Offending RSA key in /home/[yourProfileName]/.ssh/known_hosts:23
     remove with:
     ssh-keygen -f "/home/[yourProfileName]/.ssh/known_hosts" -R "[your.nas.ip]"
     Host key for [your.nas.ip] has changed and you have requested strict checking.
     Host key verification failed.
     ```
    2. Execute the suggested command `ssh-keygen -f "/home/[yourProfileName]/.ssh/known_hosts" -R "[your.nas.ip]"`.
    3. Try again to log in with `ssh root@[your.nas.ip]`.
    4. Add the fingerprint to the known hosts.
23. If you can log in successfully to the new SSH instance, you can disable the old SSH login.
24. First, stop the old instance with `/etc/init.d/ssh stop`.
25. Make sure you can still log in via SSH.
26. Remove the startup of the old SSH service by executing `update-rc.d -f ssh remove`.

## Remarks

The SSH login to the new OpenSSH instance takes a little bit longer compared to the old one, probably because the cryptographic requirements are higher than 20 years ago.

When using the NAS as a jump server to other machines using SSH, make sure that you are using the binary at `/usr/local/bin/ssh`. To ensure this, you could update the `$PATH` variable or rename the old `/usr/bin/ssh` and create a symlink that points to `/usr/local/bin/ssh`.


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
