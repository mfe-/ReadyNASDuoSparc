# DIET for the ReadyNAS NV+ v1 (SPARC)

A small, modern userland for the **ReadyNAS NV+ v1** (RAIDiator 4.1.x, IT3107 "padre" SPARC, kernel 2.6.17).
It is installed as a normal RAIDiator add-on, boots **instead of RAIDiator**, and keeps RAIDiator on disk as
an automatic fallback. **The NAND flash is never written.**

| | RAIDiator 4.1.16 | DIET 2.9 |
|---|---|---|
| Boot time | minutes | ~25 s |
| RAM used | ~45 MB | ~26 MB |
| SSH | OpenSSH 4.3p2 (legacy KEX/ciphers only) | dropbear 2024.86 (ed25519, modern KEX) |
| SMB | Samba 3.5.22, SMB1 | Samba 3.6.25, **SMB2.02** |
| rsync | 3.0.9 | 3.4.1 |
| NFS | NFSv3, kernel nfsd | NFSv3, kernel nfsd (helpers taken from RAIDiator) |
| Web UI | Frontview, HTTPS with TLS 1.0 only | small UI on HTTP port 80, password protected |

What else is in it: fan control (PWM curve from board and SMART disk temperatures, emergency shutdown),
disk spindown, LCD (hostname, temperature, IP, backlight timeout), power button
(short press = display on/off, hold 3 s = clean shutdown), green disk LEDs, disk failure alarm (LED blinks).

All binaries are built for **SPARC V7** – the IT3107 has a hardware bug in signed division (`sdiv`),
see [`tools/sdiv-test.c`](tools/sdiv-test.c) and [`toolchain/`](toolchain/).
Infrant knew about it: their kernel has `CONFIG_PADRE_DIV_BUG` ("bug 940 (divide) fix") with workarounds in
`arch/padre/lib/sdiv.S` and `rem.S`, and their glibc carries matching patches.

The NETGEAR GPL archive for RAIDiator 4.1.x (`RNR4_RND4_RND2_4.1.6_WW_src.zip`) contains the full
kernel source `linux-2.6.17.8` with the `arch/padre` platform code and the register map
`include/asm-padre/padre0.h`, plus `glibc-2.3.2.ds1` with the Infrant patches. The drivers for SATA/RAID
(`padre_io`), Ethernet (`padre_gmac`), fan/button, LEDs and LCD are binary-only modules and not included.

## Install

1. Frontview → **System → Update → Local** → select `DIET_2.9.bin` → **Upload and verify image**.
   RAIDiator warns that the add-on is not signed by NETGEAR – that is expected. Then **Perform System Update**.
2. Wait. The NAS reboots, RAIDiator installs the add-on during that boot, and about 2 minutes later it
   reboots once more by itself. From then on it boots DIET (~5 minutes in total).
3. Open `http://<nas-ip>/` (user `admin`, password = your RAIDiator admin password) or `ssh root@<nas-ip>`.

On a **fresh install** the installer takes over from RAIDiator: hostname, network (static or DHCP),
time zone, users and their Samba passwords (`smbpasswd` file), shares (`Shares.conf`) and the admin
password (root for SSH, `admin` for the web UI). If NFS was enabled in RAIDiator, its exports are taken
over as `/c/<share>`, but only for the local subnet (RAIDiator exports to `*`). The rsync daemon stays off
until you create `/etc/rsyncd.conf`; NFS stays off as long as `/etc/exports` is empty.
On an **update** (installing a newer `DIET_x.y.bin` the same way) the existing DIET configuration is kept,
the previous version stays in `/diet.old`.

Install log (seen from RAIDiator): `/var/log/diet-install.log`. In DIET the RAIDiator root is mounted at
`/mnt/root`, so the log is `/mnt/root/var/log/diet-install.log`.

## Throughput

The CPU is the limit, not the disks or the network. Measured from a Linux client over Wi-Fi with `dd` (300 MB):

| | write | read |
|---|---|---|
| local on the NAS (RAID5, ext3) | 15 MB/s | 21 MB/s |
| raw TCP (`nc`) | – | ~20 MB/s |
| Samba 3.6 (SMB2) | 5–9 MB/s | 5–9 MB/s |
| NFSv3 (kernel nfsd) | ~7 MB/s | ~10 MB/s |

While writing via NFS the CPU has 0 % idle: about half goes to nfsd, ~20 % to the RAID5 parity
(`md2_raid5`), the rest to ext3 journalling and network interrupts. Smaller NFS block sizes and Ethernet pause
frames did not help. Use NFS for Linux clients and Samba for Windows/Android.

## Back to RAIDiator / uninstall

- Web UI → **RAIDiator starten**, or `zu-raidiator` via SSH: boots RAIDiator **once**.
- If DIET does not come up (no SSH after boot), the next power cycle boots RAIDiator automatically.
- To remove DIET completely: boot RAIDiator, install `DIET_remove_2.9.bin` the same way. It restores the
  original `/sbin/init` and deletes `/diet`.

## How it works

- **Boot switch:** `/sbin/init` on the system volume (md0) is replaced by a small script
  ([`init-weiche`](src/rootfs/sbin/init-weiche)), the original is kept as `/sbin/init.real`.
  It starts DIET with `chroot /diet /sbin/init` (busybox init) unless
  - `/.raidiator_once` exists (requested once),
  - the last DIET boot did not finish (`/.diet_pending` is only removed when sshd is up), or
  - an add-on installation is waiting in `/tmp/addons/*/install.sh` (so RAIDiator can install it).
  `/sbin/init` exists at every moment of the installation – `linuxrc` resets the system if it is missing.
- The kernel modules are already loaded by `linuxrc`, so DIET only needs userland. DIET mounts the data
  volume `/c` (LVM on md2, ext3) itself.

### RAIDiator 4.1 add-on format (sparc)

Worked out from Frontview and `linuxrc`, confirmed on real hardware:

- 512-byte header: `addon::name=NAME,version=V,time=EPOCH,size=N,md5sum=MD5\n`, zero padded.
  Bytes 384–511 hold NETGEAR's RSA signature (empty → "not signed" warning, installation still works).
- Followed by a tar archive with `install.sh`. `md5sum` is the MD5 of everything after the first 512 bytes.
- **NETGEAR add-ons are 3DES encrypted** (key `-k0` of Henrik Nordström's `readynas_crypto`, i.e. the
  `hwcp` hardware key). Add **`unencrypted=1`** to the header for a plain tar, otherwise `linuxrc`
  "decrypts" it into garbage and you get an empty `/tmp/addons/NAME`.
- Flow: Frontview checks the MD5, stores the upload as `/tmp/update_file`, writes it to `/.new_addons`
  and reboots → `linuxrc` extracts it to `/tmp/addons/NAME` → `rc3` runs `sh install.sh`.
  `install.sh` should delete its own directory, otherwise `rc3` runs it again on every boot.

### Hardware notes (NV+ v1, `pcbid: 1`)

- Power button: the module calls the hotplug helper with `powersave` (short press) or `powerdown`
  (hold ~3 s). After `powerdown` the kernel cuts the power after **120 s** regardless.
  Requires `echo 1 > /proc/sys/dev/hwmon/POWER_SWITCH`.
- The hotplug path is resolved **inside the chroot** (pid 1 shares its `fs_struct` with the kernel threads).
- Disk LEDs: `/proc/sys/dev/led/disk_N_fault` = `1` means "disk present, LED on" on this board.
- No Wake-on-LAN, no scheduled power-on (Ethernet PHY is unpowered when off).
- `/proc/sys/*` string files only answer reads at offset 0 – shell `read` gets one character, use `cat`.

## Status

Tested on one NV+ v1 (4× 1 TB, RAID5): updates via Frontview, power button, LEDs, fan control,
spindown, Samba (SMB2, Linux cifs client), NFSv3, web UI, fallback to RAIDiator.
**Not yet tested on real hardware:** a fresh install on a box that never had DIET (only in emulation
with a copy of a real RAIDiator root), and `DIET_remove`. Feedback welcome.
Not for the Duo v1 or other models (the installer refuses to run there).
The web UI is German for now.

## Build

```sh
cd src
sh prepare_tree.sh ../DIET_2.9.bin   # binaries from the existing add-on + scripts from rootfs/
sh build_addon.sh                    # writes out/DIET_<version>.bin and out/DIET_remove_<version>.bin
```

Credits: mfe- for this repository, Henrik Nordström for `readynas_crypto`, the DIET-PC author for the idea.
