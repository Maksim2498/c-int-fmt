#ifndef FOMINMV_INTSTR_RADIX_H
#define FOMINMV_INTSTR_RADIX_H

#include <stdbool.h>

#include "case.h"

typedef unsigned char mint_radix_t;

#define MINT_RADIX_AUTO 0

#define MINT_RADIX_MIN  2
#define MINT_RADIX_MAX  36

const char *mint_radix_prefix(mint_radix_t radix, enum mint_case c);
bool mint_radix_valid(mint_radix_t radix);

#endif