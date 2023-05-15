/**
 * @file
 * @brief Contains integer parsing functions and parsing options structure
 */

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

/**
 * @brief Read-character callback type
 * 
 * The argument is optional and may be a pointer to anything.
 * Return value is read character converted to int type or MINT_PARSE_READE_INVALID indicating that reading failed.
 */
typedef int (*mint_parse_read_t)(void *);

/// Constant indicating that character reading failed
#define MINT_PARSE_READ_INVALID INT_MAX

/// Parsing options
struct mint_parse_opts {
    const char     *group_sep;

    enum mint_pres  sign_pres;

    mint_radix_t    radix;
    enum mint_case  radix_prefix_case;
    enum mint_case  digit_case;
    enum mint_pres  radix_prefix_pres;

    bool            skip_ws;
};

/// Default parsing options
static const struct mint_parse_opts MINT_PARSE_OPTS_DEFAULT = {
    .group_sep         = NULL,

    .sign_pres         = MINT_PRES_OPT,

    .radix             = MINT_RADIX_AUTO,
    .radix_prefix_case = MINT_CASE_ANY,
    .digit_case        = MINT_CASE_ANY,
    .radix_prefix_pres = MINT_PRES_OPT,

    .skip_ws           = true
};

/// Result of integer parsing
struct mint_parse_res {
    intmax_t val;
    size_t   read_count;
    int      last_read;
    bool     valid;
};

/// Result of unsigned integer parsing
struct muint_parse_res {
    uintmax_t val;
    size_t    read_count;
    int       last_read;
    bool      valid;
};

/**
 * @brief Parses passed string to integer using specified options
 * 
 * If parsing options are NULL then pointer to MINT_PARSE_OPTS_DEFAULT will be used in place of them.
 * 
 * @param str  String
 * @param opts Parsing options
 * 
 * @return Parsing result
 */
struct mint_parse_res mint_parse_str(const char *str, const struct mint_parse_opts *opts);

/**
 * @brief Parses passed string to unsigned interger using specified options
 * 
 * If parsing options are NULL then pointer to MINT_PARSE_OPTS_DEFAULT will be used in place of them.
 * 
 * @param str  String
 * @param opts Parsing options
 * 
 * @return Parsing result
 */
struct muint_parse_res muint_parse_str(const char *str, const struct mint_parse_opts *opts);

/**
 * @brief Parses passed string to integer using specified options
 * 
 * If parsing options are NULL then pointer to MINT_PARSE_OPTS_DEFAULT will be used in place of them.
 * 
 * @param str     String
 * @param str_len String length
 * @param opts    Parsing options
 * 
 * @return Parsing result
 */
struct mint_parse_res mint_parse_str_n(const char *str, size_t str_len, const struct mint_parse_opts *opts);

/**
 * @brief Parses passed string to unsigend integer using specified options
 * 
 * If parsing options are NULL then pointer to MINT_PARSE_OPTS_DEFAULT will be used in place of them.
 * 
 * @param str     String
 * @param str_len String length
 * @param opts    Parsing options
 * 
 * @return Parsing result
 */
struct muint_parse_res muint_parse_str_n(const char *str, size_t str_len, const struct mint_parse_opts *opts);

/**
 * @brief Parses passed file to integer using specified options
 * 
 * If parsing options are NULL then pointer to MINT_PARSE_OPTS_DEFAULT will be used in place of them.
 * 
 * @param file File
 * @param opts Parsing options
 * 
 * @return Parsing result
 */
struct mint_parse_res mint_parse_file(FILE *file, const struct mint_parse_opts *opts);

/**
 * @brief Parses passed file to unsigend integer using specified options
 * 
 * If parsing options are NULL then pointer to MINT_PARSE_OPTS_DEFAULT will be used in place of them.
 * 
 * @param file File
 * @param opts Parsing options
 * 
 * @return Parsing result
 */
struct muint_parse_res muint_parse_file(FILE *file, const struct mint_parse_opts *opts);

/**
 * @brief Parses character stream to integer using specified options
 * 
 * If parsing options are NULL then pointer to MINT_PARSE_OPTS_DEFAULT will be used in place of them.
 * 
 * @param read     Read callback
 * @param read_arg Argument for read callback
 * @param opts     Parsing options
 * 
 * @return Parsing result
 */
struct mint_parse_res mint_parse(mint_parse_read_t read, void *read_arg, const struct mint_parse_opts *opts);

/**
 * @brief Parses character stream to unsigned integer using specified options
 * 
 * If parsing options are NULL then pointer to MINT_PARSE_OPTS_DEFAULT will be used in place of them.
 * 
 * @param read     Read callback
 * @param read_arg Argument for read callback
 * @param opts     Parsing options
 * 
 * @return Parsing result
 */
struct muint_parse_res muint_parse(mint_parse_read_t read, void *read_arg, const struct mint_parse_opts *opts);

/**
 * @brief Checks if parsing options are valid
 * 
 * If parsing options are NULL then pointer to MINT_PARSE_OPTS_DEFAULT will be used in place of them.
 * 
 * @param opts Parsing options
 * 
 * @return Boolean indicating wether parsing options are valid
 */
bool mint_parse_opts_valid(const struct mint_parse_opts *opts);

#endif