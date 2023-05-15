/**
 * @file
 * @brief Contains mint_radix_t type and it's corresponsing functions and constants
 */

#ifndef FOMINMV_INTSTR_RADIX_H
#define FOMINMV_INTSTR_RADIX_H

#include <stdbool.h>

#include "case.h"

/// Radix type
typedef unsigned char mint_radix_t;

#define MINT_RADIX_AUTO 0  ///< Specifies that radix will be determined automatically

#define MINT_RADIX_MIN  2  ///< Minumum exact radix
#define MINT_RADIX_MAX  36 ///< Maximum exact radix

/**
 * @brief Returns prefix of specified case for passed radix
 * 
 * For radixes other than 2, 8, and 16 returns an empty string.
 * For 2 returns "0b" or "0B" if case is upper.
 * For 8 returns "0o" or "0O" if case is upper.
 * For 16 returns "0x" or "0X" if case is upper.
 * 
 * @param radix Radix
 * @param c     Case
 * 
 * @return Radix prefix
 */
const char *mint_radix_prefix(mint_radix_t radix, enum mint_case c);

/**
 * @brief Checks if radix is valid (auto or valid exact)
 * 
 * @param radix Radix
 * 
 * @return Boolean indicating wether radix is valid
 */
bool mint_radix_valid(mint_radix_t radix);

#endif