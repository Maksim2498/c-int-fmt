#include "radix.h"

#include <assert.h>
#include <stddef.h>

const char *mint_radix_prefix(mint_radix_t radix, enum mint_case c) {
    assert(mint_radix_valid(radix) && mint_case_valid(c));

    switch (radix) {
        case 2:
            return mint_case_lower(c) ? "0b" : "0B";

        case 8:
            return mint_case_lower(c) ? "0o" : "0O";

        case 16:
            return mint_case_lower(c) ? "0x" : "0X";

        default:
            return NULL;
    }
}

bool mint_radix_valid(mint_radix_t radix) {
    return MINT_RADIX_AUTO == radix
        || MINT_RADIX_MIN  <= radix
        && MINT_RADIX_MAX  >= radix;
}