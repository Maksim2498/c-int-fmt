#include "fmt.h"

#include <assert.h>
#include <limits.h>

const struct mint_fmt_opts MINT_FMT_OPTS_DEFAULT = {
    .group_sep         = NULL,
    .group_size        = 0,

    .min_digits        = 0,
    .digit_case        = MINT_CASE_UPPER,

    .plus              = MINT_PLUS_NONE,

    .radix             = 10,
    .radix_prefix_case = MINT_CASE_LOWER,
    .show_radix_prefix = true
};

struct mwrite_str_arg_ {
    char   *str;
    size_t  pos;
    size_t  len;
};

static bool mwrite_str_(char c, struct mwrite_str_arg_ *arg);
static bool mwrite_file_(char c, FILE *file);
static size_t mxint_fmt_(uintmax_t val, bool is_signed, mint_fmt_write_t write, void *write_arg, const struct mint_fmt_opts *opts);
static size_t mxint_fmt_write_str_(const char *str, mint_fmt_write_t write, void *write_arg);

size_t mint_fmt_str(intmax_t val, char *str, size_t len, const struct mint_fmt_opts *opts) {
    struct mwrite_str_arg_ arg = {
        .str = str,
        .pos = 0,
        .len = len
    };

    return mint_fmt(val, (mint_fmt_write_t) mwrite_str_, &arg, opts);
}

size_t muint_fmt_str(uintmax_t val, char *str, size_t len, const struct mint_fmt_opts *opts) {
    struct mwrite_str_arg_ arg = {
        .str = str,
        .pos = 0, 
        .len = len
    };

    return muint_fmt(val, (mint_fmt_write_t) mwrite_str_, &arg, opts);
}

bool mwrite_str_(char c, struct mwrite_str_arg_ *arg) {
    bool write = arg->pos < arg->len;

    if (write) {
        if (arg->str)
            arg->str[arg->pos] = c;

        ++arg->pos;
    }

    return write;
}

size_t mint_fmt_file(intmax_t val, FILE *file, const struct mint_fmt_opts *opts) {
    return mint_fmt(val, (mint_fmt_write_t) mwrite_file_, file, opts);
}

size_t muint_fmt_file(uintmax_t val, FILE *file, const struct mint_fmt_opts *opts) {
    return muint_fmt(val, (mint_fmt_write_t) mwrite_file_, file, opts);
}

bool mwrite_file_(char c, FILE *file) {
    return file ? fputc(c, file) != EOF
                : true;
}

size_t mint_fmt(intmax_t val, mint_fmt_write_t write, void *write_arg, const struct mint_fmt_opts *opts) {
    return mxint_fmt_(val, true, write, write_arg, opts);
}

size_t muint_fmt(uintmax_t val, mint_fmt_write_t write, void *write_arg, const struct mint_fmt_opts *opts) {
    return mxint_fmt_(val, false, write, write_arg, opts);
}

size_t mxint_fmt_(uintmax_t val, bool is_signed, mint_fmt_write_t write, void *write_arg, const struct mint_fmt_opts *opts) {
    assert(write && mint_fmt_opts_valid(opts));

    if (!opts)
        opts = &MINT_FMT_OPTS_DEFAULT;

    size_t written = 0;

    // Write sign and negate val if it's negative:

    if (is_signed && (intmax_t) val < 0) {
        written += write('-', write_arg);
        val      = -val;
    } else {
        char c;

        switch (opts->plus) {
            case MINT_PLUS_SIGN:
                c = '+';
                break;

            case MINT_PLUS_SPACE:
                c = ' ';
                break;

            default:
                c = 0;
        }

        if (c)
            written += write(c, write_arg);
    }

    // Write radix prefix:

    mint_radix_t radix = MINT_RADIX_AUTO == opts->radix ? 10 : opts->radix;

    if (opts->show_radix_prefix) {
        const char *radix_prefix = mint_radix_prefix(radix, opts->radix_prefix_case);

        written += mxint_fmt_write_str_(radix_prefix, write, write_arg);
    }

    // Maximum length of binary
    static const unsigned MAX_DIGIT_COUNT = sizeof(uintmax_t) * CHAR_BIT;

    // Convert val to digits:

    char     digits[MAX_DIGIT_COUNT];
    unsigned digit_count = 0;
    bool     digit_upper = mint_case_upper(opts->digit_case);

    do {
        char rem         = val % radix;
        char digit_base  = rem < 10 ? '0'
                                    : digit_upper ? 'A' - 10
                                                  : 'a' - 10;
        char digit       = digit_base + rem;

        digits[digit_count++] = digit;

        val /= radix;
   } while (val);

    // Write digits with separators and leading zeroes:

    size_t leading_count;
    size_t effective_digit_count;

    if (digit_count >= opts->min_digits) {
        leading_count         = 0;
        effective_digit_count = digit_count;
    } else {
        leading_count         = opts->min_digits - digit_count;
        effective_digit_count = opts->min_digits;
    }

    for (size_t i = 1; ; ++i) {
        char digit = i <= leading_count ? '0'
                                        : digits[digit_count + leading_count - i];

        written += write(digit, write_arg);

        if (i >= effective_digit_count)
            break;

        if (opts->group_size && (effective_digit_count - i) % opts->group_size == 0)
            written += mxint_fmt_write_str_(opts->group_sep, write, write_arg);
    }

    return written;
}

size_t mxint_fmt_write_str_(const char *str, mint_fmt_write_t write, void *write_arg) {
    size_t written = 0;

    if (str)
        while (*str)
            written += write(*str++, write_arg);

    return written;
}

bool mint_fmt_opts_valid(const struct mint_fmt_opts *opts) {
    return !opts
        || mint_radix_valid(opts->radix)
        && mint_case_valid(opts->digit_case)
        && mint_plus_valid(opts->plus)
        && mint_case_valid(opts->radix_prefix_case);
}