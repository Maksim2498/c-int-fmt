#ifndef FOMINMV_INTSTR_CASE_H
#define FOMINMV_INTSTR_CASE_H

#include <stdbool.h>

enum mint_case {
    MINT_CASE_UPPER,
    MINT_CASE_LOWER,
    MINT_CASE_ANY,
    MINT_CASE_COUNT
};

const char *mint_case_name(enum mint_case c);
const char *mint_case_sname(enum mint_case c);
bool mint_case_match(enum mint_case c, char ch);
bool mint_case_equal(enum mint_case lhs, enum mint_case rhs);
bool mint_case_upper(enum mint_case c);
bool mint_case_lower(enum mint_case c);
bool mint_case_valid(enum mint_case c);

#endif