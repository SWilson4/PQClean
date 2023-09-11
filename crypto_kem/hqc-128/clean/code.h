#ifndef PQCLEAN_HQC128_CLEANCODE_H
#define PQCLEAN_HQC128_CLEANCODE_H

/**
 * @file code.h
 * @brief Header file of code.c
 */

#include "parameters.h"
#include <stddef.h>
#include <stdint.h>

void PQCLEAN_HQC128_CLEANcode_encode(uint64_t *em, const uint8_t *message);

void PQCLEAN_HQC128_CLEANcode_decode(uint8_t *m, const uint64_t *em);

#endif
