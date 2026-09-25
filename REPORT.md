# REPORT.md — Operating Systems Programming Assignment 01
**Name:** Ashmal
**Roll No:** BSDSF24M033
**Repository:** https://github.com/Ashmal2323/BSDSF24M033-OS-A01

---

## Part 1: Project Scaffolding and Version Control

Set up the repository `BSDSF24M033-OS-A01` with the required folder structure
(`src/`, `include/`, `lib/`, `bin/`, `obj/`, `REPORT.md`). Used `.gitkeep`
placeholder files in empty folders since Git does not track empty directories.
Configured Git identity and authenticated using a GitHub Personal Access Token,
since GitHub no longer accepts plain password authentication for Git operations.

---

## Part 2: Multi-file Project using Make Utility

### Report Questions

**Q1: Explain the linking rule in this part's Makefile: `$(TARGET): $(OBJECTS)`.
How does it differ from a Makefile rule that links against a library?**

The rule `$(TARGET): $(OBJECTS)` states that the executable `bin/client` depends
on all three object files (`mystrfunctions.o`, `myfilefunctions.o`, `main.o`).
Its recipe passes all three object files directly to `gcc`, which links them
together into one executable — the linker resolves function calls (like
`main.c` calling `mystrlen()`) by matching them directly against the
definitions found in the other listed object files.

This differs from the rule used for `bin/client_static` in Part 3:
`$(STATIC_TARGET): $(OBJDIR)/main.o $(STATIC_LIB)`. Here, only `main.o` is
listed explicitly — the other two object files are not mentioned directly at
all. Instead, they are bundled inside `libmyutils.a`, and the recipe passes
that archive file directly to `gcc`. The linker searches inside the archive
only for the specific symbols it needs, rather than every object file being
explicitly listed. This makes the build command shorter and lets the library
be reused across multiple programs without repeating object file paths.

**Q2: What is a git tag and why is it useful in a project? What is the
difference between a simple tag and an annotated tag?**

A git tag marks a specific commit as significant — typically a stable release
point — so it can be referenced by a memorable name (e.g., `v0.2.1-static`)
instead of a long commit hash. This is useful for marking exactly which
version of the code corresponds to each submitted milestone or GitHub Release.

A lightweight tag is just a named pointer to a commit, with no additional
metadata. An annotated tag (created with `git tag -a`, used throughout this
project) is a full Git object storing a message, the tagger's name, email,
and date — similar to a commit. I used annotated tags for all four versions
(`v0.1.1-multifile`, `v0.2.1-static`, `v0.3.1-dynamic`, `v0.4.1-final`), which
is best practice for marking real releases.

**Q3: What is the purpose of creating a "Release" on GitHub? What is the
significance of attaching binaries to it?**

A GitHub Release packages a specific tagged version of the project as an
official, downloadable milestone, with a title, description, and optionally
compiled binary assets. Attaching binaries (e.g., `bin/client`,
`lib/libmyutils.a`) allows anyone to download and use the compiled program
directly, without needing to clone the repository and build it from source —
useful for distributing a working library/tool to users without a build
toolchain set up.

---

## Part 3: Static Library

### Report Questions

**Q1: Compare the Makefile from Part 2 and Part 3. Key differences?**

Part 2's Makefile links `bin/client` directly from all three object files
using `$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)`. Part 3 introduces a new
`$(STATIC_LIB)` target that runs `ar rcs $(STATIC_LIB) $(LIB_OBJECTS)` to
bundle two of the object files (excluding `main.o`) into `libmyutils.a`. It
then links `bin/client_static` using
`$(CC) $(CFLAGS) $(OBJDIR)/main.o $(STATIC_LIB) -o $(STATIC_TARGET)` — passing
the library file directly rather than listing individual object files. The
key new variable is `LIB_OBJECTS`, which explicitly excludes `main.o` from
the library, since a library should only contain reusable functions, not the
driver program.

**Q2: What is the purpose of the `ar` command? Why is `ranlib` often used
immediately after it?**

`ar` (archiver) bundles multiple object files into a single static library
archive (`.a` file) — a specialized container format for object files, read
directly by the linker. `ranlib` generates or refreshes a symbol index inside
the archive, letting the linker quickly locate which object file defines a
given function, rather than scanning every object file sequentially. I used
the modern combined flag `ar rcs` — the `s` flag performs the same indexing
job as `ranlib`, so a separate `ranlib` step was not required. I confirmed the
archive's contents with `ar -t lib/libmyutils.a`, which listed exactly
`mystrfunctions.o` and `myfilefunctions.o`.

**Q3: When you run `nm` on your `client_static` executable, are the symbols
for functions like `mystrlen` present? What does this tell you about how
static linking works?**

Yes — running `nm bin/client_static | grep mystrlen` (and the other five
function names) showed all of them marked with `T`, meaning they are defined
directly within the executable's own code section. This confirms static
linking physically copies the compiled machine code of library functions into
the final executable, rather than just referencing them, making the
executable fully self-contained at runtime. I verified this further with
`ldd bin/client_static`, which showed no dependency on `libmyutils.so` at all,
once I corrected my Makefile to link the `.a` file directly by path instead
of using `-lmyutils` (which had initially caused gcc to default to linking
the `.so` version instead, since both existed in the same search directory).

---

## Part 4: Dynamic Library

### Report Questions

**Q1: What is Position-Independent Code (`-fPIC`) and why is it a fundamental
requirement for creating shared libraries?**

`-fPIC` tells the compiler to generate machine code that does not rely on
fixed, absolute memory addresses, using relative offsets instead. This is
essential for shared libraries because the same `.so` file can be loaded into
many different programs, and even at different memory addresses across
different runs of the same program (especially with address space layout
randomization). Position-independent code lets one compiled `.so` file work
correctly regardless of where in memory it is loaded, without needing to be
recompiled for each case. I compiled separate `_pic.o` object files
specifically with this flag, distinct from the regular object files used for
the static library.

**Q2: Explain the difference in file size between your static and dynamic
clients. Why does this difference exist?**

After correcting my Makefile to properly force static linking (both
`client_static` and `client_dynamic` had initially, and accidentally, linked
against the `.so` file, since gcc's linker defaults to preferring shared
libraries when both `.a` and `.so` exist in the same search path), I measured
the exact byte sizes: `client_static` was 16,736 bytes, and `client_dynamic`
was 16,448 bytes — a difference of 288 bytes. This exists because
`client_static` contains the actual compiled machine code for all six library
functions embedded directly in the executable, while `client_dynamic` only
contains small stub references, with the real code living separately in
`libmyutils.so`, loaded into memory at runtime. The absolute difference is
modest here because the library only has 6 small functions; with a larger
library, this gap would be significantly more pronounced.

**Q3: What is the `LD_LIBRARY_PATH` environment variable? Why was it
necessary to set it, and what does this tell you about the responsibilities
of the OS's dynamic loader?**

`LD_LIBRARY_PATH` is an environment variable that tells the dynamic loader
additional directories to search for shared libraries, beyond its default
system locations. When I first tried running `./bin/client_dynamic` without
setting it, I got: `error while loading shared libraries: libmyutils.so:
cannot open shared object file: No such file or directory` — because
`libmyutils.so` lives in the project's own `lib/` folder, which is not a
default search location. After running
`export LD_LIBRARY_PATH=$(pwd)/lib:$LD_LIBRARY_PATH`, the program ran
successfully. This demonstrates that the dynamic loader is responsible for
locating and loading shared libraries at runtime — a responsibility entirely
separate from compiling and linking, which only check that symbols can
theoretically be resolved, not that the library file will actually be found
when the program executes.

---

## Part 5: Man Pages and Installation

Created six section-3 man pages (`man/man3/*.3`) documenting all library
functions (`mystrlen`, `mystrcpy`, `mystrncpy`, `mystrcat`, `wordCount`,
`mygrep`), each with `.TH`, `.SH NAME`, `.SH SYNOPSIS`, `.SH DESCRIPTION`,
`.SH RETURN VALUE`, and `.SH AUTHOR` sections, formatted using groff macros.
Previewed each locally with `man -l man/man3/<name>.3` before installing.

Added an `install` target to the Makefile using the `install` utility (with
`-d` for directories and `-m` for permissions) to copy `client_dynamic` to
`/usr/local/bin/client`, `libmyutils.so` to `/usr/local/lib`, and all man
pages to `/usr/local/man/man3`. Ran `ldconfig` afterward to refresh the
system's shared library cache, since the dynamic loader relies on a cached
index rather than scanning directories on every program launch.

Verified installation by running `sudo make install`, then confirming
`client` runs successfully from any directory (proving `/usr/local/bin` is on
the system `PATH`), and `man mystrlen` (and other functions) display
correctly system-wide (proving `/usr/local/man` is a recognized `man` search
path) — without needing `LD_LIBRARY_PATH` or `man -l` anymore.

---

## Part 6: Final Submission

All feature branches (`multifile-build`, `static-build`, `dynamic-build`,
`man-pages`) were developed independently, committed with descriptive
messages, tagged with annotated tags, merged into `main`, and pushed to
GitHub along with their corresponding Releases:

- `v0.1.1-multifile` — Version 0.1.0: Multi-file Build
- `v0.2.1-static` — Version 0.2.1: Static Library Build
- `v0.3.1-dynamic` — Version 0.3.1: Dynamic Library Build
- `v0.4.1-final` — Version 0.4.1: Final Build

`main` reflects the complete, integrated final state of the project,
including multi-file compilation, static and dynamic libraries, man pages,
and installation support.
