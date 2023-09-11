#ifndef PQCLEAN_HQC128_CLEANSHAKE_PRNG_H
#define PQCLEAN_HQC128_CLEANSHAKE_PRNG_H

/**
 * @file shake_prng.h
 * @brief Header file of shake_prng.c
 */

#include "fips202.h"
#include <stdint.h>

typedef shake256incctx seedexpander_state;

void PQCLEAN_HQC128_CLEANshake_prng_init(const uint8_t *entropy_input, const uint8_t *personalization_string, size_t enlen, size_t perlen);

void PQCLEAN_HQC128_CLEANshake_prng(uint8_t *output, size_t outlen);

void PQCLEAN_HQC128_CLEANshake_prng_release(void);

void PQCLEAN_HQC128_CLEANseedexpander_init(seedexpander_state *state, const uint8_t *seed, size_t seedlen);

void PQCLEAN_HQC128_CLEANseedexpander(seedexpander_state *state, uint8_t *output, size_t outlen);

void PQCLEAN_HQC128_CLEANseedexpander_release(seedexpander_state *state);

#endif
