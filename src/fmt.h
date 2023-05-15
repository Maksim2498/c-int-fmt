#ifndef FOMINMV_INTSTR_FMT_H
#define FOMINMV_INTSTR_FMT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <inttypes.h>

#include "case.h"
#include "radix.h"
#include "plus.h"

typedef bool (*mint_fmt_write_t)(char, void *);

struct mint_fmt_opts {
    const char     *group_sep;
    unsigned char   group_size;

    unsigned char   min_digits;
    enum mint_case  digit_case;

    enum mint_plus  plus;

    mint_radix_t    radix;
    enum mint_case  radix_prefix_case;
    bool            show_radix_prefix;
};

size_t mint_fmt_str(intmax_t val, char *str, const struct mint_fmt_opts *opts);
size_t muint_fmt_str(uintmax_t val, char *str, const struct mint_fmt_opts *opts);
size_t mint_fmt_str_n(intmax_t val, char *str, size_t len, const struct mint_fmt_opts *opts);
size_t muint_fmt_str_n(uintmax_t val, char *str, size_t len, const struct mint_fmt_opts *opts);
size_t mint_fmt_file(intmax_t val, FILE *file, const struct mint_fmt_opts *opts);
size_t muint_fmt_file(uintmax_t val, FILE *file, const struct mint_fmt_opts *opts);
size_t mint_fmt(intmax_t val, mint_fmt_write_t write, void *write_arg, const struct mint_fmt_opts *opts);
size_t muint_fmt(uintmax_t val, mint_fmt_write_t write, void *write_arg, const struct mint_fmt_opts *opts);
bool mint_fmt_opts_valid(const struct mint_fmt_opts *opts);

extern const struct mint_fmt_opts MINT_FMT_OPTS_DEFAULT;

#endif