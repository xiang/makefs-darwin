PROG=   makefs
CC=     clang

# Darwin compat
CFLAGS+= -arch x86_64 -arch arm64
CFLAGS+= -Isrc/compat
CFLAGS+= -include src/compat/darwin_compat.h

CFLAGS+= -Isrc/usr.sbin/makefs
CFLAGS+= -Isrc/usr.sbin/makefs/ffs
CFLAGS+= -Isrc/lib/libnetbsd
CFLAGS+= -Isrc/lib/libutil
CFLAGS+= -Isrc/contrib/mtree
CFLAGS+= -Isrc/contrib/mknod
CFLAGS+= -Isrc/sys/ufs/ffs
CFLAGS+= -Isrc/sys/ufs/ufs
CFLAGS+= -Isrc/sys/fs/cd9660
CFLAGS+= -Isrc/sys/fs/msdosfs
CFLAGS+= -Isrc/sys
CFLAGS+= -Isrc/sbin/newfs_msdos

# FreeBSD stubs, lower priority than system headers
CFLAGS+= -isystem src/compat/freebsd

CFLAGS+= -DHAVE_STRUCT_STAT_ST_FLAGS=1
CFLAGS+= -D_DARWIN_C_SOURCE
CFLAGS+= -D_WANT_MSDOSFS_INTERNALS
CFLAGS+= -D_WANT_ISO_MNT
CFLAGS+= -DMAKEFS

SRCS=   src/usr.sbin/makefs/makefs.c \
        src/usr.sbin/makefs/walk.c \
        src/usr.sbin/makefs/mtree.c \
        src/usr.sbin/makefs/ffs.c \
        src/usr.sbin/makefs/cd9660.c \
        src/usr.sbin/makefs/msdos.c

SRCS+=  $(wildcard src/usr.sbin/makefs/msdos/*.c)
SRCS+=  $(wildcard src/usr.sbin/makefs/ffs/*.c)
SRCS+=  $(wildcard src/usr.sbin/makefs/cd9660/*.c)

SRCS+=  src/sbin/newfs_msdos/mkfs_msdos.c

SRCS+=  src/sys/ufs/ffs/ffs_tables.c

SRCS+=  src/contrib/mtree/getid.c \
        src/contrib/mtree/misc.c \
        src/contrib/mtree/spec.c \
        src/contrib/mknod/pack_dev.c

SRCS+=  src/compat/pwcache.c

SRCS+=  src/lib/libutil/humanize_number.c \
        src/lib/libutil/expand_number.c \
        src/lib/libnetbsd/strsuftoll.c \
        src/lib/libnetbsd/util.c \
        src/lib/libnetbsd/efun.c \
        src/sys/kern/subr_sbuf.c

OBJS=   $(SRCS:.c=.o)

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PROG) $(OBJS)

.PHONY: all clean
