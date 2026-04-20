#!/bin/bash
set -e

BRANCH="main"
REPO_URL="https://git.freebsd.org/src.git"
TEMP_DIR=$(mktemp -d /tmp/makefs-bootstrap.XXXXXX)

echo "Fetching makefs sources from FreeBSD ${BRANCH}..."

git clone --depth 1 --filter=blob:none --sparse "${REPO_URL}" "${TEMP_DIR}/repo"

cd "${TEMP_DIR}/repo"

git sparse-checkout set \
    usr.sbin/makefs \
    contrib/mtree \
    contrib/mknod \
    lib/libnetbsd \
    lib/libutil \
    sys/ufs/ffs \
    sys/ufs/ufs \
    sys/fs/msdosfs \
    sys/fs/cd9660 \
    sys/sys \
    sys/kern \
    sbin/newfs_msdos

cd - > /dev/null
mkdir -p src

cp -R "${TEMP_DIR}/repo/usr.sbin" src/
cp -R "${TEMP_DIR}/repo/contrib" src/
cp -R "${TEMP_DIR}/repo/lib" src/
cp -R "${TEMP_DIR}/repo/sys" src/
cp -R "${TEMP_DIR}/repo/sbin" src/

# Remove libnetbsd shadow headers that conflict with Darwin system headers
rm -rf src/lib/libnetbsd/sys
rm -f src/lib/libnetbsd/stdlib.h src/lib/libnetbsd/pthread.h src/lib/libnetbsd/math.h src/lib/libnetbsd/glob.h
rm -f src/lib/libnetbsd/netinet/in.h

# Relocate headers needed from sys/sys before removing that directory tree;
# sys/sys shadows Darwin system headers if left in place under -Isrc/sys.
mkdir -p src/compat/sys
cp src/sys/sys/sbuf.h src/compat/sys/
cp src/sys/sys/tree.h src/compat/sys/
cp src/sys/sys/queue.h src/compat/sys/
rm -rf src/sys/sys

rm -rf "${TEMP_DIR}"

echo "Done. Upstream sources in ./src"
