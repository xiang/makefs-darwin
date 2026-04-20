# makefs-darwin

A native Darwin port of FreeBSD's `makefs` utility, supporting both Intel (x86_64) and Apple Silicon (arm64).

`makefs` creates filesystem images from a directory tree without requiring root privileges. This port implements the **ffs**, **msdos**, and **cd9660** backends.

## Features
- **Darwin-Centric Compat:** Lightweight compatibility layer for BSD kernel structures.
- **Universal Binary:** Builds for Intel and Apple Silicon by default.
- **Full mtree(5) Support:** Includes shims for user/group mapping and spec parsing.

## Getting Started

### Build
```bash
make
```

### Usage
Refer to the `makefs(8)` manpage for standard usage.

## License
Original FreeBSD code remains under its respective BSD licenses. Porting shims are provided under the BSD-2-Clause license.
