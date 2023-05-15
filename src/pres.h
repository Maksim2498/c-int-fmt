#ifndef FOMINMV_INTSTR_PRES_H
#define FOMINMV_INTSTR_PRES_H

#include <stdbool.h>

enum mint_pres {
    MINT_PRES_NO,
    MINT_PRES_OPT,
    MINT_PRES_REQ,
    MINT_PRES_COUNT
};

const char *mint_pres_name(enum mint_pres pres);
const char *mint_pres_sname(enum mint_pres pres);
bool mint_pres_valid(enum mint_pres pres);

#endif