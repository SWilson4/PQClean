#ifndef PQCLEAN_HQC192_CLEANGF2X_H
#define PQCLEAN_HQC192_CLEANGF2X_H

/**
 * @file gf2x.h
 * @brief Header file for gf2x.c
 */

#include <stdint.h>

void PQCLEAN_HQC192_CLEANvect_mul(uint64_t *o, const uint64_t *v1, const uint64_t *v2);

#endif
