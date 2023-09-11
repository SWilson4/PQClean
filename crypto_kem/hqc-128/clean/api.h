#ifndef PQCLEAN_HQC128_CLEANAPI_H
#define PQCLEAN_HQC128_CLEANAPI_H

/**
 * @file api.h
 * @brief NIST KEM API used by the HQC_KEM IND-CCA2 scheme
 */

#include <stdint.h>

#define PQCLEAN_HQC128_CLEANCRYPTO_ALGNAME                      "HQC-128"

#define PQCLEAN_HQC128_CLEANCRYPTO_SECRETKEYBYTES               2289
#define PQCLEAN_HQC128_CLEANCRYPTO_PUBLICKEYBYTES               2249
#define PQCLEAN_HQC128_CLEANCRYPTO_BYTES                        64
#define PQCLEAN_HQC128_CLEANCRYPTO_CIPHERTEXTBYTES              4497

// As a technicality, the public key is appended to the secret key in order to respect the NIST API.
// Without this constraint, PQCLEAN_HQC128_CLEANCRYPTO_SECRETKEYBYTES would be defined as 32

int PQCLEAN_HQC128_CLEANcrypto_kem_keypair(uint8_t *pk, uint8_t *sk);

int PQCLEAN_HQC128_CLEANcrypto_kem_enc(uint8_t *ct, uint8_t *ss, const uint8_t *pk);

int PQCLEAN_HQC128_CLEANcrypto_kem_dec(uint8_t *ss, const uint8_t *ct, const uint8_t *sk);

#endif
