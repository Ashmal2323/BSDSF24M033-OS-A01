# libmyutils — Core C Utilities Library

**Operating Systems — Programming Assignment 01**
Roll No: BSDSF24M033

A general-purpose C utility library (`libmyutils`) providing custom string manipulation
and file-processing functions, built and released progressively as a multi-file
executable, a static library, and a dynamic (shared) library — demonstrating the full
C build and release workflow.

## Project Structure

```
BSDSF24M033-OS-A01/
├── src/          # Source code (.c) for the library modules and driver program
├── include/      # Header files (.h)
├── lib/          # Compiled static (libmyutils.a) and dynamic (libmyutils.so) libraries
├── bin/          # Final built executables
├── obj/          # Intermediate object files
├── man/man3/     # Man pages for library functions
└── REPORT.md     # Analysis and answers for each build phase
```

## Modules

- **String Functions** (`mystrfunctions`): `mystrlen`, `mystrcpy`, `mystrncpy`, `mystrcat`
- **File Functions** (`myfilefunctions`): `wordCount`, `mygrep`

## Building

```bash
make            # builds bin/client (all sources linked directly)
make static     # builds lib/libmyutils.a and bin/client_static
make dynamic    # builds lib/libmyutils.so and bin/client_dynamic
sudo make install   # installs client_dynamic, libmyutils.so, and man pages system-wide
```

Running the dynamic build before installing requires:

```bash
export LD_LIBRARY_PATH=$PWD/lib:$LD_LIBRARY_PATH
```

## Usage

```bash
./bin/client            # multi-file build
./bin/client_static      # static library build
./bin/client_dynamic     # dynamic library build (after setting LD_LIBRARY_PATH, or after install)
```

After installing, man pages for each library function are available, e.g.:

```bash
man mystrlen
man mygrep
```

## Releases

| Version | Tag | Description |
|---|---|---|
| v0.1.1 | `v0.1.1-multifile` | Direct multi-file compilation |
| v0.2.1 | `v0.2.1-static` | Static library build |
| v0.3.1 | `v0.3.1-dynamic` | Dynamic library build |
| v0.4.1 | `v0.4.1-final` | Man pages + install target (final) |

See [REPORT.md](REPORT.md) for the full technical analysis and report answers, including
comparisons of static vs. dynamic linking, Makefile design, and the Linux build/release
workflow used in this project.

## Author

Ashmal — BSDSF24M033# BSDSF24M033-OS-A01
OS Programming Assignment 01
