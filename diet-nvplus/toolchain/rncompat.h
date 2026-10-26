/* rncompat.h - compatibility shims for building current software against
 * the Infrant glibc 2.3.2 (RAIDiator 4.1.x, SPARC) with sanitized 2.6.18
 * kernel headers. Include with: CFLAGS="-include rncompat.h -fgnu89-inline"
 */
#ifndef RNCOMPAT_H
#define RNCOMPAT_H
#ifndef __ASSEMBLER__
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>

#ifndef O_CLOEXEC
#define O_CLOEXEC 0            /* not supported by 2.6.17, ignored */
#endif
#ifndef SCHED_BATCH
#define SCHED_BATCH 3
#endif
#ifndef AT_FDCWD
#define AT_FDCWD -100
#endif
#ifndef AT_SYMLINK_NOFOLLOW
#define AT_SYMLINK_NOFOLLOW 0x100
#endif
#ifndef IFLA_NET_NS_PID
#define IFLA_NET_NS_PID 19
#endif
#ifndef IFA_F_DADFAILED
#define IFA_F_DADFAILED 0x08
#endif

/* utimensat/futimens via utimes/futimes (microsecond resolution) */
struct timespec;
static inline int rn_ts2tv(const struct timespec *ts, struct timeval *tv)
{
    if (!ts) return 0;
    tv[0].tv_sec = ts[0].tv_sec; tv[0].tv_usec = ts[0].tv_nsec / 1000;
    tv[1].tv_sec = ts[1].tv_sec; tv[1].tv_usec = ts[1].tv_nsec / 1000;
    return 1;
}
static inline int rn_utimensat(int dirfd, const char *path, const struct timespec *ts, int flags)
{
    struct timeval tv[2];
    (void)dirfd; (void)flags;          /* only AT_FDCWD is supported */
    return utimes(path, rn_ts2tv(ts, tv) ? tv : 0);
}
static inline int rn_futimens(int fd, const struct timespec *ts)
{
    struct timeval tv[2];
    return futimes(fd, rn_ts2tv(ts, tv) ? tv : 0);
}
static inline int rn_syncfs(int fd) { (void)fd; sync(); return 0; }
#define utimensat rn_utimensat
#define futimens  rn_futimens
#define syncfs    rn_syncfs
#endif /* __ASSEMBLER__ */
#endif
