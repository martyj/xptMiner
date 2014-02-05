// keccak.h
// 19-Nov-11  Markku-Juhani O. Saarinen <mjos@iki.fi>

#ifndef SHA3_KECCAK_H
#define SHA3_KECCAK_H

#include <stdint.h>
#include <string.h>

#ifndef SHA3_KECCAK_ROUNDS
#define SHA3_KECCAK_ROUNDS 24
#endif

#define SHA3_224 28
#define SHA3_256 32
#define SHA3_384 48
#define SHA3_512 64

// compute a keccak hash (md) of given byte length from "in"
int sha3(const uint8_t *in, int inlen, uint8_t *md, int mdlen);

// update the state
void sha3_f(uint64_t st[25], int norounds);

#endif
