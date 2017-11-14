/**********************************************************************
 * Copyright (c) 2014 Pieter Wuille                                   *
 * Distributed under the MIT software license, see the accompanying   *
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.*
 **********************************************************************/

#ifndef SECP256K1_SCALAR_H
#define SECP256K1_SCALAR_H

#include <stdint.h>
#include <secp256k1_num.h>

/** A scalar modulo the group order of the secp256k1 curve. */
typedef struct {
    uint64_t d[4];
} secp256k1_scalar;

#define SECP256K1_SCALAR_CONST(d7, d6, d5, d4, d3, d2, d1, d0) {{((uint64_t)(d1)) << 32 | (d0), ((uint64_t)(d3)) << 32 | (d2), ((uint64_t)(d5)) << 32 | (d4), ((uint64_t)(d7)) << 32 | (d6)}}

/** Clear a scalar to prevent the leak of sensitive data. */
void secp256k1_scalar_clear(secp256k1_scalar *r);

/** Access bits from a scalar. All requested bits must belong to the same 32-bit limb. */
unsigned int secp256k1_scalar_get_bits(const secp256k1_scalar *a, unsigned int offset, unsigned int count);

/** Access bits from a scalar. Not constant time. */
unsigned int secp256k1_scalar_get_bits_var(const secp256k1_scalar *a, unsigned int offset, unsigned int count);

/** Set a scalar from a big endian byte array. */
void secp256k1_scalar_set_b32(secp256k1_scalar *r, const unsigned char *bin, int *overflow);

/** Set a scalar to an unsigned integer. */
void secp256k1_scalar_set_int(secp256k1_scalar *r, unsigned int v);

/** Convert a scalar to a byte array. */
void secp256k1_scalar_get_b32(unsigned char *bin, const secp256k1_scalar* a);

/** Add two scalars together (modulo the group order). Returns whether it overflowed. */
int secp256k1_scalar_add(secp256k1_scalar *r, const secp256k1_scalar *a, const secp256k1_scalar *b);

/** Conditionally add a power of two to a scalar. The result is not allowed to overflow. */
void secp256k1_scalar_cadd_bit(secp256k1_scalar *r, unsigned int bit, int flag);

/** Multiply two scalars (modulo the group order). */
void secp256k1_scalar_mul(secp256k1_scalar *r, const secp256k1_scalar *a, const secp256k1_scalar *b);

/** Shift a scalar right by some amount strictly between 0 and 16, returning
 *  the low bits that were shifted off */
int secp256k1_scalar_shr_int(secp256k1_scalar *r, int n);

/** Compute the square of a scalar (modulo the group order). */
void secp256k1_scalar_sqr(secp256k1_scalar *r, const secp256k1_scalar *a);

/** Compute the inverse of a scalar (modulo the group order). */
void secp256k1_scalar_inverse(secp256k1_scalar *r, const secp256k1_scalar *a);

/** Compute the inverse of a scalar (modulo the group order), without constant-time guarantee. */
void secp256k1_scalar_inverse_var(secp256k1_scalar *r, const secp256k1_scalar *a);

/** Compute the complement of a scalar (modulo the group order). */
void secp256k1_scalar_negate(secp256k1_scalar *r, const secp256k1_scalar *a);

/** Check whether a scalar equals zero. */
int secp256k1_scalar_is_zero(const secp256k1_scalar *a);

/** Check whether a scalar equals one. */
int secp256k1_scalar_is_one(const secp256k1_scalar *a);

/** Check whether a scalar, considered as an nonnegative integer, is even. */
int secp256k1_scalar_is_even(const secp256k1_scalar *a);

/** Check whether a scalar is higher than the group order divided by 2. */
int secp256k1_scalar_is_high(const secp256k1_scalar *a);

/** Conditionally negate a number, in constant time.
 * Returns -1 if the number was negated, 1 otherwise */
int secp256k1_scalar_cond_negate(secp256k1_scalar *a, int flag);

/** Convert a scalar to a number. */
void secp256k1_scalar_get_num(secp256k1_num *r, const secp256k1_scalar *a);

/** Get the order of the group as a number. */
void secp256k1_scalar_order_get_num(secp256k1_num *r);

/** Compare two scalars. */
int secp256k1_scalar_eq(const secp256k1_scalar *a, const secp256k1_scalar *b);

/** Multiply a and b (without taking the modulus!), divide by 2**shift, and round to the nearest integer. Shift must be at least 256. */
void secp256k1_scalar_mul_shift_var(secp256k1_scalar *r, const secp256k1_scalar *a, const secp256k1_scalar *b, unsigned int shift);

#endif /* SECP256K1_SCALAR_H */
