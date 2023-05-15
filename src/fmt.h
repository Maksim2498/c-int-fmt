/**
 * @file
 * @brief Contains integer formatting functions and formatting options structure
 */

#ifndef FOMINMV_INTSTR_FMT_H
#define FOMINMV_INTSTR_FMT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <inttypes.h>

#include "case.h"
#include "radix.h"
#include "plus.h"

/**
 * @brief Write-character callback type
 * 
 * First argument is character to write.
 * Second argument is optional and may be a pointer to anything.
 * Return value indicates wether character was written or not.
 */
typedef bool (*mint_fmt_write_t)(char, void *);

/// Fomratting options
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

/// Default formatting options
static const struct mint_fmt_opts MINT_FMT_OPTS_DEFAULT = {
    .group_sep         = NULL,
    .group_size        = 0,

    .min_digits        = 0,
    .digit_case        = MINT_CASE_UPPER,

    .plus              = MINT_PLUS_NONE,

    .radix             = 10,
    .radix_prefix_case = MINT_CASE_LOWER,
    .show_radix_prefix = true
};

/**
 * @brief Formats passed value and writes result to specified string
 *
 * If string is NULL then it only returns a number of characters it would write.
 * If formatting options are NULL then pointer to MINT_FMT_OPTS_DEFAULT will be used in place of them.
 * 
 * @param val      Value
 * @param str[out] String
 * @param opts     Formatting options

 * @return Number of characters written
 */
size_t mint_fmt_str(intmax_t val, char *str, const struct mint_fmt_opts *opts);

/**
 * @brief Formats passed value and writes result to specified string
 *
 * If string is NULL then it only returns a number of characters it would write.
 * If formatting options are NULL then pointer to MINT_FMT_OPTS_DEFAULT will be used in place of them.
 * 
 * @param val      Value
 * @param str[out] String
 * @param opts     Formatting options

 * @return Number of characters written
 */
size_t muint_fmt_str(uintmax_t val, char *str, const struct mint_fmt_opts *opts);

/**
 * @brief Formats passed value and writes result to specified string
 *
 * If string is NULL then it only returns a number of characters it would write.
 * If formatting options are NULL then pointer to MINT_FMT_OPTS_DEFAULT will be used in place of them.
 * 
 * @param val      Value
 * @param str[out] String
 * @param len      String length
 * @param opts     Formatting options

 * @return Number of characters written
 */
size_t mint_fmt_str_n(intmax_t val, char *str, size_t len, const struct mint_fmt_opts *opts);

/**
 * @brief Formats passed value and writes result to specified string
 *
 * If string is NULL then it only returns a number of characters it would write.
 * If formatting options are NULL then pointer to MINT_FMT_OPTS_DEFAULT will be used in place of them.
 * 
 * @param val      Value
 * @param str[out] String
 * @param len      String length
 * @param opts     Formatting options

 * @return Number of characters written
 */
size_t muint_fmt_str_n(uintmax_t val, char *str, size_t len, const struct mint_fmt_opts *opts);

/**
 * @brief Formats passed value and writes result to specified file
 *
 * If file is NULL then it only returns a number of characters it would write.
 * If formatting options are NULL then pointer to MINT_FMT_OPTS_DEFAULT will be used in place of them.
 * 
 * @param val  Value
 * @param file File
 * @param opts Formatting options

 * @return Number of characters written
 */
size_t mint_fmt_file(intmax_t val, FILE *file, const struct mint_fmt_opts *opts);

/**
 * @brief Formats passed value and writes result to specified file
 * 
 * If file is NULL then it only returns a number of characters it would write.
 * If formatting options are NULL then pointer to MINT_FMT_OPTS_DEFAULT will be used in place of them.
 * 
 * @param val  Value
 * @param file File
 * @param opts Formatting options

 * @return Number of characters written
 */
size_t muint_fmt_file(uintmax_t val, FILE *file, const struct mint_fmt_opts *opts);

/**
 * @brief Formats passed value and writes result with write callback
 * 
 * If formatting options are NULL then pointer to MINT_FMT_OPTS_DEFAULT will be used in place of them.
 * 
 * @param val       Value
 * @param write     Write callback
 * @param write_arg Argument for write callback
 * @param opts      Formatting options

 * @return Number of characters written
 */
size_t mint_fmt(intmax_t val, mint_fmt_write_t write, void *write_arg, const struct mint_fmt_opts *opts);

/**
 * @brief Formats passed value and writes result with write callback
 * 
 * If formatting options are NULL then pointer to MINT_FMT_OPTS_DEFAULT will be used in place of them.
 * 
 * @param val       Value
 * @param write     Write callback
 * @param write_arg Argument for write callback
 * @param opts      Formatting options

 * @return Number of characters written
 */
size_t muint_fmt(uintmax_t val, mint_fmt_write_t write, void *write_arg, const struct mint_fmt_opts *opts);

/**
 * @brief Checks if formatting options are valid
 * 
 * @param opts Formatting options

 * @return Boolean indicating wether formatting options are valid
 */
bool mint_fmt_opts_valid(const struct mint_fmt_opts *opts);

#endif