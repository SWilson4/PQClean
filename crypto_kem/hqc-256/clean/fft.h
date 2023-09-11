#ifndef PQCLEAN_HQC256_CLEANFFT_H
#define PQCLEAN_HQC256_CLEANFFT_H

/**
 * @file fft.h
 * @brief Header file of fft.c
 */

#include <stddef.h>
#include <stdint.h>

void PQCLEAN_HQC256_CLEANfft(uint16_t *w, const uint16_t *f, size_t f_coeffs);

void PQCLEAN_HQC256_CLEANfft_retrieve_error_poly(uint8_t *error, const uint16_t *w);

#endif
