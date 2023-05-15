/**
 * @file
 * @brief Contains mint_pres enumeration and it's corresponsing functions
 */

#ifndef FOMINMV_INTSTR_PRES_H
#define FOMINMV_INTSTR_PRES_H

#include <stdbool.h>

/// Presence modes
enum mint_pres {
    MINT_PRES_NO,   ///< Presence is forbidden
    MINT_PRES_OPT,  ///< Presence is opitonal
    MINT_PRES_REQ,  ///< Presence is required
    MINT_PRES_COUNT ///< Number of elements in enumeration
};

/**
 * @brief Returns presence mode name as enumuration member name
 * 
 * @param pres Presence mode
 * 
 * @return Presence mode name
 */
const char *mint_pres_name(enum mint_pres pres);

/**
 * @brief Returns short presence mode name ("no", "optinal", or "required")
 * 
 * @param pres Presence mode
 * 
 * @return Short precense mode name
 */
const char *mint_pres_sname(enum mint_pres pres);

/**
 * @brief Checks if precense mode is valid
 * 
 * @param pres Presence mode
 * 
 * @return Boolean indicating wether presence mode is valid
 */
bool mint_pres_valid(enum mint_pres pres);

#endif