#ifndef FOMINMV_INTSTR_PLUS_H
#define FOMINMV_INTSTR_PLUS_H

#include <stdbool.h>

enum mint_plus {
    MINT_PLUS_NONE,
    MINT_PLUS_SPACE,
    MINT_PLUS_SIGN,
    MINT_PLUS_COUNT
};

const char *mint_plus_name(enum mint_plus plus);
const char *mint_plus_sname(enum mint_plus plus);
bool mint_plus_valid(enum mint_plus plus);

#endif