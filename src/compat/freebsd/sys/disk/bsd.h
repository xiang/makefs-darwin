/*
 * Darwin compat stub: FreeBSD sys/disk/bsd.h
 *
 * Only the fields used by makefs (via mkfs_msdos.c) are defined here.
 * getdiskbyname(3) and floppy-specific fields are excluded; they are
 * guarded by #ifndef MAKEFS in the upstream source.
 */
#ifndef _SYS_DISK_BSD_H_
#define _SYS_DISK_BSD_H_

#include <stdint.h>

struct disklabel {
	uint32_t d_secsize;    /* bytes per sector */
	uint32_t d_nsectors;   /* sectors per track */
	uint32_t d_ntracks;    /* tracks per cylinder (heads) */
	uint32_t d_secperunit; /* sectors per unit */
};

#endif /* _SYS_DISK_BSD_H_ */
