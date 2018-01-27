# Install

1. iSCSItarget_1.4.20.2-readynas-1.0.5.bin install with frontview administraion webinterface
2. `mkdir /c/iscsi`
3. `chown admin: /c/iscsi`
4. `dd if=/dev/zero of=/c/iscsi/test_0 bs=1M count=4096`
2. create or modify `nano /etc/iet/ietd.conf` to
3. `Target iqn.2010-01.local.foo.us:readyduo.iscsi.target0
     Lun 0 Path=/c/iscsi/test_0,Type=fileio
`

Contributes to: 
- https://rnxtras.com/addons/iscsi-target-readynas-4-sparc
- https://translate.google.com/translate?hl=de&sl=fr&tl=en&u=https%3A%2F%2Fwww.thierry-jaouen.fr%2Fdokuwiki%2Fdoku.php%3Fid%3Dmateriel_readynas&anno=2
- http://mpsharp.com/blog/2010/10/29/jumbo-frames-iscsi-and-disabling-nagle/
- http://www.markwilson.co.uk/blog/2009/09/creating-an-iscsi-target-on-a-netgear-readynas.htm
