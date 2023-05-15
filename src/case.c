#include "case.h"

#include <assert.h>
#include <ctype.h>

const char *mint_case_name(enum mint_case c) {
    assert(mint_case_valid(c));

    switch (c) {
        case MINT_CASE_LOWER:
            return "MINT_CASE_LOWER";

        case MINT_CASE_UPPER:
            return "MINT_CASE_UPPER";

        case MINT_CASE_ANY:
            return "MINT_CASE_ANY";

        default:
            return "";
    }
}

const char *mint_case_sname(enum mint_case c) {
    assert(mint_case_valid(c));

    switch (c) {
        case MINT_CASE_LOWER:
            return "lower";

        case MINT_CASE_UPPER:
            return "upper";

        case MINT_CASE_ANY:
            return "any";

        default:
            return "";
    }
}

bool mint_case_match(enum mint_case c, char ch) {
    assert(mint_case_valid(c));

    switch (c) {
        case MINT_CASE_LOWER:
            return islower(ch);

        case MINT_CASE_UPPER:
            return isupper(ch);

        default:
            return true;
    }
}

bool mint_case_equal(enum mint_case lhs, enum mint_case rhs) {
    assert(mint_case_valid(lhs) && mint_case_valid(rhs));

    return MINT_CASE_ANY == lhs
        || MINT_CASE_ANY == rhs
        ||           lhs == rhs;
}

bool mint_case_upper(enum mint_case c) {
    assert(mint_case_valid(c));
    return MINT_CASE_LOWER != c;
}

bool mint_case_lower(enum mint_case c) {
    assert(mint_case_valid(c));
    return MINT_CASE_UPPER != c;
}

bool mint_case_valid(enum mint_case c) {
    return c < MINT_CASE_COUNT;
}