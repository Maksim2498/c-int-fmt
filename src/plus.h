/**
 * @file
 * @brief Contains mint_plus enumeration and it's corresponsing functions
 */

#ifndef FOMINMV_INTSTR_PLUS_H
#define FOMINMV_INTSTR_PLUS_H

#include <stdbool.h>

/// Plus modes
enum mint_plus {
    MINT_PLUS_NONE,  ///< Hide plus
    MINT_PLUS_SPACE, ///< Show plus as space
    MINT_PLUS_SIGN,  ///< Show plus as sign (+)
    MINT_PLUS_COUNT  ///< Number of elements in enumeration
};

/**
 * @brief Returns plus mode name as enumuration member name
 * 
 * @param plus Plus mode
 * 
 * @return Plus mode name
 */
const char *mint_plus_name(enum mint_plus plus);

/**
 * @brief Returns short plus mode name ("none", "space", or "sign")
 * 
 * @param plus Plus mode
 * 
 * @return Short plus mode name
 */
const char *mint_plus_sname(enum mint_plus plus);

/**
 * @brief Checks if plus mode is valid
 * 
 * @param plus Plus mode
 * 
 * @return Boolean indicating wether plus mode is valid
 */
bool mint_plus_valid(enum mint_plus plus);

#endif