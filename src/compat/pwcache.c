/*
 * Darwin compat: pwcache(3) — BSD function for swapping in custom
 * group/user database backends.  macOS libutil does not provide these.
 * We implement trivial pass-through versions that just store the
 * caller-supplied lookup functions (or fall back to the POSIX defaults).
 */

#include <grp.h>
#include <pwd.h>

static struct group  *(*_getgrnam)(const char *) = getgrnam;
static struct group  *(*_getgrgid)(gid_t)        = getgrgid;
static struct passwd *(*_getpwnam)(const char *)  = getpwnam;
static struct passwd *(*_getpwuid)(uid_t)         = getpwuid;

int
gid_from_group(const char *name, gid_t *gid)
{
	struct group *gr = _getgrnam(name);
	if (gr == NULL)
		return (-1);
	*gid = gr->gr_gid;
	return (0);
}

int
uid_from_user(const char *name, uid_t *uid)
{
	struct passwd *pw = _getpwnam(name);
	if (pw == NULL)
		return (-1);
	*uid = pw->pw_uid;
	return (0);
}

int
pwcache_groupdb(int (*setent)(int), void (*endent)(void),
    struct group *(*getnam)(const char *), struct group *(*getgid)(gid_t))
{
	if (setent)  setent(1);
	_getgrnam = getnam ? getnam : getgrnam;
	_getgrgid = getgid ? getgid : getgrgid;
	return (0);
}

int
pwcache_userdb(int (*setent)(int), void (*endent)(void),
    struct passwd *(*getnam)(const char *), struct passwd *(*getuid)(uid_t))
{
	if (setent)  setent(1);
	_getpwnam = getnam ? getnam : getpwnam;
	_getpwuid = getuid ? getuid : getpwuid;
	return (0);
}
