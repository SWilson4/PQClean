#ifndef PQCLEAN_HQCRMRS256_CLEAN_FFT_H
#define PQCLEAN_HQCRMRS256_CLEAN_FFT_H

/**
 * @file fft.h
 * @brief Header file of fft.c
 */

#include <stddef.h>
#include <stdint.h>

void PQCLEAN_HQCRMRS256_CLEAN_fft(uint16_t *w, const uint16_t *f, size_t f_coeffs);

void PQCLEAN_HQCRMRS256_CLEAN_fft_retrieve_error_poly(uint8_t *error, const uint16_t *w);

#endif
