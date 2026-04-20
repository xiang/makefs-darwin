#ifndef _DARWIN_COMPAT_H_
#define _DARWIN_COMPAT_H_

/* Standard Darwin system headers first */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/mount.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>
#include <time.h>
#include <stdarg.h>
#include <grp.h>
#include <pwd.h>

/* Map FreeBSD stat time field names to Darwin equivalents */
#define st_atim st_atimespec
#define st_mtim st_mtimespec
#define st_ctim st_ctimespec
#ifndef st_birthtim
#define st_birthtim st_birthtimespec
#endif

/* FreeBSD source annotation macros */
#ifndef __FBSDID
#define __FBSDID(s) /* empty */
#endif

#ifndef __unused
#define __unused __attribute__((unused))
#endif

#ifndef __dead2
#define __dead2 __attribute__((noreturn))
#endif

#ifndef __pure2
#define __pure2 __attribute__((const))
#endif

#ifndef __packed
#define __packed __attribute__((__packed__))
#endif

#ifndef __aligned
#define __aligned(x) __attribute__((__aligned__(x)))
#endif

#ifndef __nonstring
#define __nonstring __attribute__((__nonstring__))
#endif

/* Standard BSD arithmetic macros */
#ifndef roundup2
#define roundup2(x, y)  (((x)+((y)-1))&(~((y)-1)))
#endif

#ifndef rounddown2
#define rounddown2(x, y) ((x)&(~((y)-1)))
#endif

#ifndef __predict_true
#define __predict_true(exp)     __builtin_expect((exp), 1)
#endif

#ifndef __predict_false
#define __predict_false(exp)    __builtin_expect((exp), 0)
#endif

#ifndef nitems
#define nitems(x)       (sizeof((x)) / sizeof((x)[0]))
#endif

#ifndef __offsetof
#define __offsetof(type, field) offsetof(type, field)
#endif

/*
 * FreeBSD uses __ prefixed aliases for POSIX types internally (e.g. in
 * libutil.h).  Darwin's sys/_types.h defines these too, but re-declaring
 * them here as compatible typedefs ensures they're visible regardless of
 * include order or which feature macros were active.
 */
typedef gid_t   __gid_t;
typedef mode_t  __mode_t;
typedef pid_t   __pid_t;
typedef size_t  __size_t;
typedef uid_t   __uid_t;
typedef va_list __va_list;

typedef int8_t    __int8_t;
typedef uint8_t   __uint8_t;
typedef int16_t   __int16_t;
typedef uint16_t  __uint16_t;
typedef int32_t   __int32_t;
typedef uint32_t  __uint32_t;
typedef int64_t   __int64_t;
typedef uint64_t  __uint64_t;
typedef uintptr_t __uintptr_t;
typedef intptr_t  __intptr_t;
typedef off_t     __off_t;
typedef time_t    __time_t;
typedef ssize_t   __ssize_t;

/* Types not in Darwin's sys/types.h regardless of feature macros */
typedef uint64_t u_quad_t;
typedef int64_t  quad_t;

/* FreeBSD kernel types used by filesystem headers */
typedef uint32_t critical_t;
typedef uint32_t fflags_t;
typedef int32_t  segsz_t;
typedef uint64_t vm_paddr_t;
typedef uint64_t vm_ooffset_t;
typedef uint64_t vm_pindex_t;
typedef uint32_t cpumask_t;

/*
 * Prevent FreeBSD's sys/cdefs.h and related headers from being loaded
 * via -isystem src/compat/freebsd.  Darwin's versions are already included
 * above; the FreeBSD stubs would conflict.
 */
#define _SYS_CDEFS_H_
#define _SYS_STDINT_H_
#define _SYS__STDINT_H_
#define _SYS__TYPES_H_

/* Function prototypes for libnetbsd shims */
long long strsuftoll(const char *, const char *, long long, long long);
long long strsuftollx(const char *, const char *, long long, long long, char *, size_t);

/* Provided by contrib/mtree/getid.c; not in any macOS system header */
int gid_from_group(const char *, gid_t *);
int uid_from_user(const char *, uid_t *);

/* pwcache(3) — not in macOS libutil; provided by src/compat/pwcache.c */
int pwcache_groupdb(int (*)(int), void (*)(void),
    struct group * (*)(const char *), struct group * (*)(gid_t));
int pwcache_userdb(int (*)(int), void (*)(void),
    struct passwd * (*)(const char *), struct passwd * (*)(uid_t));

#ifndef _PATH_MTREE_SPEC
#define _PATH_MTREE_SPEC "/etc/mtree"
#endif

#endif /* _DARWIN_COMPAT_H_ */
