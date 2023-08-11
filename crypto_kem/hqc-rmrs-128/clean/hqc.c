#include "code.h"
#include "gf2x.h"
#include "hqc.h"
#include "parameters.h"
#include "parsing.h"
#include "shake_prng.h"
#include "vector.h"
#include <stdint.h>
/**
 * @file hqc.c
 * @brief Implementation of hqc.h
 */



/**
 * @brief Keygen of the HQC_PKE IND_CPA scheme
 *
 * The public key is composed of the syndrome <b>s</b> as well as the <b>seed</b> used to generate the vector <b>h</b>.
 *
 * The secret key is composed of the <b>seed</b> used to generate vectors <b>x</b> and  <b>y</b>.
 * As a technicality, the public key is appended to the secret key in order to respect NIST API.
 *
 * @param[out] pk String containing the public key
 * @param[out] sk String containing the secret key
 */
void PQCLEAN_HQCRMRS128_CLEAN_hqc_pke_keygen(unsigned char *pk, unsigned char *sk) {
    seedexpander_state sk_seedexpander;
    seedexpander_state pk_seedexpander;
    uint8_t sk_seed[SEED_BYTES] = {0};
    uint8_t pk_seed[SEED_BYTES] = {0};
    uint64_t x[VEC_N_SIZE_64] = {0};
    uint64_t y[VEC_N_SIZE_64] = {0};
    uint64_t h[VEC_N_SIZE_64] = {0};
    uint64_t s[VEC_N_SIZE_64] = {0};

    // Create seed_expanders for public key and secret key
    PQCLEAN_HQCRMRS128_CLEAN_shake_prng(sk_seed, SEED_BYTES);
    PQCLEAN_HQCRMRS128_CLEAN_seedexpander_init(&sk_seedexpander, sk_seed, SEED_BYTES);

    PQCLEAN_HQCRMRS128_CLEAN_shake_prng(pk_seed, SEED_BYTES);
    PQCLEAN_HQCRMRS128_CLEAN_seedexpander_init(&pk_seedexpander, pk_seed, SEED_BYTES);

    // Compute secret key
    PQCLEAN_HQCRMRS128_CLEAN_vect_set_random_fixed_weight(&sk_seedexpander, x, PARAM_OMEGA);
    PQCLEAN_HQCRMRS128_CLEAN_vect_set_random_fixed_weight(&sk_seedexpander, y, PARAM_OMEGA);

    // Compute public key
    PQCLEAN_HQCRMRS128_CLEAN_vect_set_random(&pk_seedexpander, h);
    PQCLEAN_HQCRMRS128_CLEAN_vect_mul(s, y, h);
    PQCLEAN_HQCRMRS128_CLEAN_vect_add(s, x, s, VEC_N_SIZE_64);

    // Parse keys to string
    PQCLEAN_HQCRMRS128_CLEAN_hqc_public_key_to_string(pk, pk_seed, s);
    PQCLEAN_HQCRMRS128_CLEAN_hqc_secret_key_to_string(sk, sk_seed, pk);

}



/**
 * @brief Encryption of the HQC_PKE IND_CPA scheme
 *
 * The cihertext is composed of vectors <b>u</b> and <b>v</b>.
 *
 * @param[out] u Vector u (first part of the ciphertext)
 * @param[out] v Vector v (second part of the ciphertext)
 * @param[in] m Vector representing the message to encrypt
 * @param[in] theta Seed used to derive randomness required for encryption
 * @param[in] pk String containing the public key
 */
void PQCLEAN_HQCRMRS128_CLEAN_hqc_pke_encrypt(uint64_t *u, uint64_t *v, uint8_t *m, unsigned char *theta, const unsigned char *pk) {
    seedexpander_state seedexpander;
    uint64_t h[VEC_N_SIZE_64] = {0};
    uint64_t s[VEC_N_SIZE_64] = {0};
    uint64_t r1[VEC_N_SIZE_64] = {0};
    uint64_t r2[VEC_N_SIZE_64] = {0};
    uint64_t e[VEC_N_SIZE_64] = {0};
    uint64_t tmp1[VEC_N_SIZE_64] = {0};
    uint64_t tmp2[VEC_N_SIZE_64] = {0};

    // Create seed_expander from theta
    PQCLEAN_HQCRMRS128_CLEAN_seedexpander_init(&seedexpander, theta, SEED_BYTES);

    // Retrieve h and s from public key
    PQCLEAN_HQCRMRS128_CLEAN_hqc_public_key_from_string(h, s, pk);

    // Generate r1, r2 and e
    PQCLEAN_HQCRMRS128_CLEAN_vect_set_random_fixed_weight(&seedexpander, r1, PARAM_OMEGA_R);
    PQCLEAN_HQCRMRS128_CLEAN_vect_set_random_fixed_weight(&seedexpander, r2, PARAM_OMEGA_R);
    PQCLEAN_HQCRMRS128_CLEAN_vect_set_random_fixed_weight(&seedexpander, e, PARAM_OMEGA_E);

    // Compute u = r1 + r2.h
    PQCLEAN_HQCRMRS128_CLEAN_vect_mul(u, r2, h);
    PQCLEAN_HQCRMRS128_CLEAN_vect_add(u, r1, u, VEC_N_SIZE_64);

    // Compute v = m.G by encoding the message
    PQCLEAN_HQCRMRS128_CLEAN_code_encode((uint8_t *)v, m);
    PQCLEAN_HQCRMRS128_CLEAN_load8_arr(v, VEC_N1N2_SIZE_64, (uint8_t *)v, VEC_N1N2_SIZE_BYTES);
    PQCLEAN_HQCRMRS128_CLEAN_vect_resize(tmp1, PARAM_N, v, PARAM_N1N2);

    // Compute v = m.G + s.r2 + e
    PQCLEAN_HQCRMRS128_CLEAN_vect_mul(tmp2, r2, s);
    PQCLEAN_HQCRMRS128_CLEAN_vect_add(tmp2, e, tmp2, VEC_N_SIZE_64);
    PQCLEAN_HQCRMRS128_CLEAN_vect_add(tmp2, tmp1, tmp2, VEC_N_SIZE_64);
    PQCLEAN_HQCRMRS128_CLEAN_vect_resize(v, PARAM_N1N2, tmp2, PARAM_N);

}



/**
 * @brief Decryption of the HQC_PKE IND_CPA scheme
 *
 * @param[out] m Vector representing the decrypted message
 * @param[in] u Vector u (first part of the ciphertext)
 * @param[in] v Vector v (second part of the ciphertext)
 * @param[in] sk String containing the secret key
 */
void PQCLEAN_HQCRMRS128_CLEAN_hqc_pke_decrypt(uint8_t *m, const uint64_t *u, const uint64_t *v, const unsigned char *sk) {
    uint64_t x[VEC_N_SIZE_64] = {0};
    uint64_t y[VEC_N_SIZE_64] = {0};
    uint8_t pk[PUBLIC_KEY_BYTES] = {0};
    uint64_t tmp1[VEC_N_SIZE_64] = {0};
    uint64_t tmp2[VEC_N_SIZE_64] = {0};

    // Retrieve x, y, pk from secret key
    PQCLEAN_HQCRMRS128_CLEAN_hqc_secret_key_from_string(x, y, pk, sk);

    // Compute v - u.y
    PQCLEAN_HQCRMRS128_CLEAN_vect_resize(tmp1, PARAM_N, v, PARAM_N1N2);
    PQCLEAN_HQCRMRS128_CLEAN_vect_mul(tmp2, y, u);
    PQCLEAN_HQCRMRS128_CLEAN_vect_add(tmp2, tmp1, tmp2, VEC_N_SIZE_64);


    // Compute m by decoding v - u.y
    PQCLEAN_HQCRMRS128_CLEAN_store8_arr((uint8_t *)tmp1, VEC_N_SIZE_BYTES, tmp2, VEC_N_SIZE_64);
    PQCLEAN_HQCRMRS128_CLEAN_code_decode(m, (uint8_t *)tmp1);
}
