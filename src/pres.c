#include "pres.h"

#include <assert.h>

const char *mint_pres_name(enum mint_pres pres) {
    assert(mint_pres_valid(pres));

    switch (pres) {
        case MINT_PRES_NO:
            return "MINT_PRES_NO";

        case MINT_PRES_OPT:
            return "MINT_PRES_OPT";

        case MINT_PRES_REQ:
            return "MINT_PRES_REQ";

        default:
            return "";
    }
}

const char *mint_pres_sname(enum mint_pres pres) {
    assert(mint_pres_valid(pres));

    switch (pres) {
        case MINT_PRES_NO:
            return "no";

        case MINT_PRES_OPT:
            return "optional";

        case MINT_PRES_REQ:
            return "required";

        default:
            return "";
    }
}

bool mint_pres_valid(enum mint_pres pres) {
    return pres < MINT_PRES_COUNT;
}