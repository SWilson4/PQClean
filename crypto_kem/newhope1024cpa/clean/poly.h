#ifndef POLY_H
#define POLY_H

#include "params.h"
#include <stdint.h>

/*
 * Elements of R_q = Z_q[X]/(X^n + 1). Represents polynomial
 * coeffs[0] + X*coeffs[1] + X^2*xoeffs[2] + ... + X^{n-1}*coeffs[n-1]
 */
typedef struct {
    uint16_t coeffs[NEWHOPE_N];
} poly;

void PQCLEAN_NEWHOPE1024CPA_CLEAN_poly_uniform(poly *a, const unsigned char *seed);
void PQCLEAN_NEWHOPE1024CPA_CLEAN_poly_sample(poly *r, const unsigned char *seed, unsigned char nonce);
void PQCLEAN_NEWHOPE1024CPA_CLEAN_poly_add(poly *r, const poly *a, const poly *b);

void PQCLEAN_NEWHOPE1024CPA_CLEAN_poly_ntt(poly *r);
void PQCLEAN_NEWHOPE1024CPA_CLEAN_poly_invntt(poly *r);
void PQCLEAN_NEWHOPE1024CPA_CLEAN_poly_mul_pointwise(poly *r, const poly *a, const poly *b);

void PQCLEAN_NEWHOPE1024CPA_CLEAN_poly_frombytes(poly *r, const unsigned char *a);
void PQCLEAN_NEWHOPE1024CPA_CLEAN_poly_tobytes(unsigned char *r, const poly *p);
void PQCLEAN_NEWHOPE1024CPA_CLEAN_poly_compress(unsigned char *r, const poly *p);
void PQCLEAN_NEWHOPE1024CPA_CLEAN_poly_decompress(poly *r, const unsigned char *a);

void PQCLEAN_NEWHOPE1024CPA_CLEAN_poly_frommsg(poly *r, const unsigned char *msg);
void PQCLEAN_NEWHOPE1024CPA_CLEAN_poly_tomsg(unsigned char *msg, const poly *x);
void PQCLEAN_NEWHOPE1024CPA_CLEAN_poly_sub(poly *r, const poly *a, const poly *b);

#endif
