#include "plus.h"

#include <assert.h>

const char *mint_plus_name(enum mint_plus plus) {
    assert(mint_plus_valid(plus));
    
    switch (plus) {
        case MINT_PLUS_NONE:
            return "MINT_PLUS_NONE";

        case MINT_PLUS_SPACE:
            return "MINT_PLUS_SPACE";

        case MINT_PLUS_SIGN:
            return "MINT_PLUS_SIGN";

        default:
            return "";
    }
}

const char *mint_plus_sname(enum mint_plus plus) {
    assert(mint_plus_valid(plus));
    
    switch (plus) {
        case MINT_PLUS_NONE:
            return "none";

        case MINT_PLUS_SPACE:
            return "space";

        case MINT_PLUS_SIGN:
            return "sign";

        default:
            return "";
    }
}

bool mint_plus_valid(enum mint_plus plus) {
    return plus < MINT_PLUS_COUNT;
}