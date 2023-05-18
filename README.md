# IntStr

## Index

- [Index](#index);
- [About](#about);
- [Examples](#examples);
- [Building](#building);
- [Installation](#installation);
- [Documentation](#documentation).

## About

This is a small C99 library for integer parsing and formatting.
Parsing and fomratting functions work in stream-mode, i.e. they
accept `read` and `write` callback functions as arguments and hence
can work with any kind of character streams such as files and strings.

Out of the box there are special versions of parse and format
functions with `_file`, `_str` and `_str_n` suffixes which handle
files, strings and strings of specified size respectively.

## Examples

__Code:__

```c
#include <stdio.h>

#include <fominmv/intstr/all.h>

int main() {
    mint_fmt_file(2498, stdout, NULL);

    putchar('\n');

    struct mint_fmt_opts opts = MINT_FMT_OPTS_DEFAULT;

    opts.group_sep  = "_";
    opts.group_size = 3;
    opts.plus       = MINT_PLUS_SIGN;

    mint_fmt_file(2498000, stdout, &opts);

    putchar('\n');
}
```

__Output:__

```console
2498
+2_498_000
```

## Building

For building and installing a library you must have [CMake](https://cmake.org/) installed.

First, configure a project running the following command in terminal:

```console
cmake -B build -S .
```

Then if you want to build it as a shared library run the following command:

```console
cmake -DBUILD_SHARED_LIBS=ON build
```

And finally build a library with the following command:

```console
cmake --build build
```

## Installation

Before installing you must first [build](#building) a library.

If library is already built go to the project's root folder and run the following command in terminal:

```console
cmake --install build
```

## Documentation

You can wether use [online documentation](https://docs.intstr.fominmv.ru) or build it locally.

To build documentation locally you must have [Doxygen](https://www.doxygen.nl/) installed.

When it's installed go to the project's root folder and run the following command in the terminal:

```console
doxygen
```

After this you will have a documentaion build in the `/docs` folder.
