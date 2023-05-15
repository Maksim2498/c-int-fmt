#ifndef FOMINMV_INTSTR_PARSE_H
#define FOMINMV_INTSTR_PARSE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#include "case.h"
#include "pres.h"
#include "radix.h"

typedef int (*mint_parse_read_t)(void *);

#define MINT_PARSE_READ_INVALID INT_MAX

struct mint_parse_opts {
    const char     *group_sep;

    enum mint_pres  sign_pres;

    mint_radix_t    radix;
    enum mint_case  radix_prefix_case;
    enum mint_case  digit_case;
    enum mint_pres  radix_prefix_pres;

    bool            skip_ws;
};

struct mint_parse_res {
    intmax_t val;
    size_t   read_count;
    int      last_read;
    bool     valid;
};

struct muint_parse_res {
    uintmax_t val;
    size_t    read_count;
    int       last_read;
    bool      valid;
};

struct mint_parse_res mint_parse_str(const char *str, const struct mint_parse_opts *opts);
struct muint_parse_res muint_parse_str(const char *str, const struct mint_parse_opts *opts);
struct mint_parse_res mint_parse_str_n(const char *str, size_t str_len, const struct mint_parse_opts *opts);
struct muint_parse_res muint_parse_str_n(const char *str, size_t str_len, const struct mint_parse_opts *opts);
struct mint_parse_res mint_parse_file(FILE *file, const struct mint_parse_opts *opts);
struct muint_parse_res muint_parse_file(FILE *file, const struct mint_parse_opts *opts);
struct mint_parse_res mint_parse(mint_parse_read_t read, void *read_arg, const struct mint_parse_opts *opts);
struct muint_parse_res muint_parse(mint_parse_read_t read, void *read_arg, const struct mint_parse_opts *opts);
bool mint_parse_opts_valid(const struct mint_parse_opts *opts);

extern const struct mint_parse_opts MINT_PARSE_OPTS_DEFAULT;

#endif