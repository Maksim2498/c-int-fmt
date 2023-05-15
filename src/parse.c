#include "parse.h"

#include <assert.h>
#include <ctype.h>
#include <string.h>

struct mread_str_arg_ {
    const char *str;
    size_t      pos;
    size_t      len;
};

union mxint_parse_res_ {
    struct mint_parse_res  s;
    struct muint_parse_res u;
};

struct mxint_parse_status_ {
    uintmax_t     val;
    size_t        read_count;
    int           last_read;
    unsigned char radix;
    char          sign;
    bool          valid;
};

static union mxint_parse_res_ mxint_parse_str_n_(bool is_signed, const char *str, size_t str_len, const struct mint_parse_opts *opts);
static int mread_str_(struct mread_str_arg_ *arg);

static union mxint_parse_res_ mxint_parse_file_(bool is_signed, FILE *file, const struct mint_parse_opts *opts);
static int mread_file_(FILE *file);

static union mxint_parse_res_ mxint_parse_(bool is_signed, mint_parse_read_t read, void *read_arg, const struct mint_parse_opts *opts);
static bool mxint_parse_ws_(mint_parse_read_t read, void *read_arg, const struct mint_parse_opts *opts, struct mxint_parse_status_ *status);
static bool mxint_parse_sign_(bool is_signed, mint_parse_read_t read, void *read_arg, const struct mint_parse_opts *opts, struct mxint_parse_status_ *status);
static bool mxint_parse_radix_prefix_(mint_parse_read_t read, void *read_arg, const struct mint_parse_opts *opts, struct mxint_parse_status_ *status);
static bool mxint_parse_digits_(mint_parse_read_t read, void *read_arg, const struct mint_parse_opts *opts, struct mxint_parse_status_ *status);
static bool mxint_parse_matches_str_n_(mint_parse_read_t read, void *read_arg, const char *str, size_t str_len);

struct mint_parse_res mint_parse_str(const char *str, const struct mint_parse_opts *opts) {
    return mint_parse_str_n(str, strlen(str), opts);
}

struct muint_parse_res muint_parse_str(const char *str, const struct mint_parse_opts *opts) {
    return muint_parse_str_n(str, strlen(str), opts);
}

struct mint_parse_res mint_parse_str_n(const char *str, size_t str_len, const struct mint_parse_opts *opts) {
    return mxint_parse_str_n_(true, str, str_len, opts).s;
}

struct muint_parse_res muint_parse_str_n(const char *str, size_t str_len, const struct mint_parse_opts *opts) {
    return mxint_parse_str_n_(false, str, str_len, opts).u;
}

union mxint_parse_res_ mxint_parse_str_n_(bool is_signed, const char *str, size_t str_len, const struct mint_parse_opts *opts) {
    assert(str);

    struct mread_str_arg_ arg = {
        .str = str,
        .pos = 0,
        .len = str_len
    };

    return mxint_parse_(is_signed, (mint_parse_read_t) mread_str_, &arg, opts);
}

int mread_str_(struct mread_str_arg_ *arg) {
    if (arg->pos >= arg->len)
        return MINT_PARSE_READ_INVALID;

    return arg->str[arg->pos++];
}

struct mint_parse_res mint_parse_file(FILE *file, const struct mint_parse_opts *opts) {
    return mxint_parse_file_(true, file, opts).s;
}

struct muint_parse_res muint_parse_file(FILE *file, const struct mint_parse_opts *opts) {
    return mxint_parse_file_(false, file, opts).u;
}

union mxint_parse_res_ mxint_parse_file_(bool is_signed, FILE *file, const struct mint_parse_opts *opts) {
    union mxint_parse_res_ res = mxint_parse_(is_signed, (mint_parse_read_t) mread_file_, file, opts);

    if (res.u.valid && MINT_PARSE_READ_INVALID != res.u.last_read)
        ungetc(res.u.last_read, file);

    return res;
}

int mread_file_(FILE *file) {
    int res = fgetc(file);

    return EOF == res ? MINT_PARSE_READ_INVALID
                      : res;
}

struct mint_parse_res mint_parse(mint_parse_read_t read, void *read_arg, const struct mint_parse_opts *opts) {
    return mxint_parse_(true, read, read_arg, opts).s;
}

struct muint_parse_res muint_parse(mint_parse_read_t read, void *read_arg, const struct mint_parse_opts *opts) {
    return mxint_parse_(false, read, read_arg, opts).u;
}

union mxint_parse_res_ mxint_parse_(bool is_signed, mint_parse_read_t read, void *read_arg, const struct mint_parse_opts *opts) {
    assert(read && mint_parse_opts_valid(opts));

    if (!opts)
        opts = &MINT_PARSE_OPTS_DEFAULT;

    struct mxint_parse_status_ status = {
        .val        = 0,
        .read_count = 0,
        .last_read  = read(read_arg),
        .sign       = '+',
        .radix      = opts->radix,
        .valid      = false
    };

    MINT_PARSE_READ_INVALID != status.last_read
    && mxint_parse_ws_(read, read_arg, opts, &status)
    && mxint_parse_sign_(is_signed, read, read_arg, opts, &status)
    && mxint_parse_ws_(read, read_arg, opts, &status)
    && mxint_parse_radix_prefix_(read, read_arg, opts, &status)
    && mxint_parse_digits_(read, read_arg, opts, &status);

    if ('-' == status.sign)
        status.val = -status.val;

    return (union mxint_parse_res_) {
        .u = {
            .val        = status.val,
            .read_count = status.read_count,
            .last_read  = status.last_read,
            .valid      = status.valid
        }
    };
}

bool mxint_parse_ws_(mint_parse_read_t read, void *read_arg, const struct mint_parse_opts *opts, struct mxint_parse_status_ *status) {
    if (opts->skip_ws)
        while (isspace(status->last_read)) {
            ++status->read_count;

            status->last_read = read(read_arg);

            if (MINT_PARSE_READ_INVALID == status->last_read)
                return false;
        }

    return true;
}

bool mxint_parse_sign_(bool is_signed, mint_parse_read_t read, void *read_arg, const struct mint_parse_opts *opts, struct mxint_parse_status_ *status) {
    switch (opts->sign_pres) {
        case MINT_PRES_OPT:
        case MINT_PRES_REQ:
            switch (status->last_read) {
                case '-':
                    if (!is_signed)
                        return false;

                case '+':
                    ++status->read_count;

                    status->sign      = status->last_read;
                    status->last_read = read(read_arg);

                    return MINT_PARSE_READ_INVALID != status->last_read;

                default:
                    return opts->sign_pres == MINT_PRES_OPT;
            }

        default:
            return true;
    }
}

bool mxint_parse_radix_prefix_(mint_parse_read_t read, void *read_arg, const struct mint_parse_opts *opts, struct mxint_parse_status_ *status) {
    enum mint_pres pres = opts->radix_prefix_pres;

    switch (opts->radix) {
        case MINT_RADIX_AUTO:
        case 2:
        case 8:
        case 16:
            break;

        default:
            return true;
    }

    switch (opts->radix_prefix_pres) {
        case MINT_PRES_OPT:
        case MINT_PRES_REQ:
            break;

        default:
            return true;
    }

    bool opt = MINT_PRES_OPT == opts->radix_prefix_pres;

    if (status->last_read != '0')
        return opt;

    if (opt) {
        status->valid = true;
        ++status->read_count;
    }

    status->last_read = read(read_arg);

    if (MINT_PARSE_READ_INVALID == status->last_read)
        return false;

    if (MINT_RADIX_AUTO == status->radix) {
        unsigned new_radix;

        switch (status->last_read) {
            case 'B':
            case 'b':
                new_radix = 2;
                break;

            case 'O':
            case 'o':
                new_radix = 8;
                break;

            case 'X':
            case 'x':
                new_radix = 16;
                break;

            default:
                return opt;
        }

        if (!mint_case_match(opts->radix_prefix_case, status->last_read))
            return opt;

        if (opt) {
            status->valid = false;
            ++status->read_count;
        } else
            status->read_count += 2;

        status->radix     = new_radix;
        status->last_read = read(read_arg);

        return MINT_PARSE_READ_INVALID != status->last_read;
    }

    switch (status->last_read) {
        case 'B':
        case 'b':
            if (2 != status->radix)
                return opt;

            break;

        case 'O':
        case 'o':
            if (8 != status->radix)
                return opt;

            break;

        case 'X':
        case 'x':
            if (16 != status->radix)
                return opt;

            break;

        default:
            return opt;
    }

    if (!mint_case_match(opts->radix_prefix_case, status->last_read))
        return opt;

    if (opt) {
        status->valid = false;
        ++status->read_count;
    } else
        status->read_count += 2;

    status->last_read = read(read_arg);

    return MINT_PARSE_READ_INVALID != status->last_read;
}

bool mxint_parse_digits_(mint_parse_read_t read, void *read_arg, const struct mint_parse_opts *opts, struct mxint_parse_status_ *status) {
    unsigned radix          = MINT_RADIX_AUTO != status->radix ? status->radix           : 10;
    size_t   group_sep_len  = opts->group_sep                  ? strlen(opts->group_sep) : 0;
    bool     prev_was_digit = status->valid;

    for (bool first = !prev_was_digit; ; first = false) {
        int cur_read = status->last_read;

        if (prev_was_digit && group_sep_len && *opts->group_sep == cur_read) {
            status->last_read = read(read_arg);

            if (MINT_PARSE_READ_INVALID == status->last_read)
                return false;

            for (size_t i = 1; i < group_sep_len; ++i) {
                if (opts->group_sep[i] != status->last_read)
                    return false;

                status->last_read = read(read_arg);

                if (MINT_PARSE_READ_INVALID == status->last_read)
                    return false;
            }

            prev_was_digit = false;

            continue;
        }

        unsigned       val = UINT_MAX;
        enum mint_case digit_case;

        if (isdigit(cur_read)) {
            val        = cur_read - '0';
            digit_case = MINT_CASE_ANY;
        } else if (isupper(cur_read)) {
            val        = cur_read - 'A' + 10;
            digit_case = MINT_CASE_UPPER;
        } else if (islower(cur_read)) {
            val        = cur_read - 'a' + 10;
            digit_case = MINT_CASE_LOWER;
        }

        if (val >= radix || !mint_case_equal(digit_case, opts->digit_case))
            return false;

        ++status->read_count;

        if (!first && !prev_was_digit)
            status->read_count += group_sep_len;

        status->val *= radix;
        status->val += val;

        status->valid     = true;
        status->last_read = read(read_arg);

        if (MINT_PARSE_READ_INVALID == status->last_read)
            return false;

        prev_was_digit = true;
    }
}

bool mint_parse_opts_valid(const struct mint_parse_opts *opts) {
    return !opts
        || mint_pres_valid(opts->sign_pres)
        && mint_radix_valid(opts->radix)
        && mint_case_valid(opts->radix_prefix_case)
        && mint_case_valid(opts->digit_case)
        && mint_pres_valid(opts->radix_prefix_pres);
}