/**
 * @file
 * @brief Contains mint_case enumeration and it's corresponsing functions
 */

#ifndef FOMINMV_INTSTR_CASE_H
#define FOMINMV_INTSTR_CASE_H

#include <stdbool.h>

/// Character cases
enum mint_case {
    MINT_CASE_UPPER, ///< Upper case
    MINT_CASE_LOWER, ///< Lower case
    MINT_CASE_ANY,   ///< Upper or lower case
    MINT_CASE_COUNT  ///< Number of elements in enumeration
};

/**
 * @brief Returns case name as enumuration member name
 * 
 * @param c Case
 * 
 * @return Case name
 */
const char *mint_case_name(enum mint_case c);

/**
 * @brief Returns short case name ("lower", "upper", or "any")
 * 
 * @param c Case
 * 
 * @return Short case name
 */
const char *mint_case_sname(enum mint_case c);

/**
 * @brief Checks if passed chararcter is of specified case
 * 
 * @param c  Case
 * @param ch Character
 * 
 * @return bool indicating whether passed character is of specified case
 */
bool mint_case_match(enum mint_case c, char ch);

/**
 * @brief Check if two cases are equal. Any case is equal to all cases
 * 
 * @param lhs First case
 * @param rhs Second case
 * 
 * @return bool indicating wheter two cases are equal
 */
bool mint_case_equal(enum mint_case lhs, enum mint_case rhs);

/**
 * @brief Checks if passed case is upper or any
 * 
 * @param c Case
 * 
 * @return bool indicating whether passed case is upper or any
 */
bool mint_case_upper(enum mint_case c);

/**
 * @brief Checks if passed case is lower or any
 * 
 * @param c Case
 * 
 * @return bool indicating whether passed case is lower or any
 */
bool mint_case_lower(enum mint_case c);

/**
 * @brief Checks if passed case is valid
 * 
 * @param c Case
 * 
 * @return Boolean indicating whether passed case is valid
 */
bool mint_case_valid(enum mint_case c);

#endif