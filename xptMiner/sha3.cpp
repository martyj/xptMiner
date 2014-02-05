// keccak.c
// 19-Nov-11  Markku-Juhani O. Saarinen <mjos@iki.fi>
// A baseline Keccak (3rd round) implementation.
// Modified by Marty Joosten <martyj@gamingheavens.com>

#include "sha3.h"

const uint64_t sha3f_rndc[24] = 
{
    0x0000000000000001, 0x0000000000008082, 0x800000000000808a,
    0x8000000080008000, 0x000000000000808b, 0x0000000080000001,
    0x8000000080008081, 0x8000000000008009, 0x000000000000008a,
    0x0000000000000088, 0x0000000080008009, 0x000000008000000a,
    0x000000008000808b, 0x800000000000008b, 0x8000000000008089,
    0x8000000000008003, 0x8000000000008002, 0x8000000000000080, 
    0x000000000000800a, 0x800000008000000a, 0x8000000080008081,
    0x8000000000008080, 0x0000000080000001, 0x8000000080008008
};

// update the state with given number of rounds
void sha3_f(uint64_t st[25], int rounds)
{
    int i, j, round;
    uint64_t t, bc[5];

    for(round = 0; round < rounds; round++)
	{
        bc[0] = st[0] ^ st[5] ^ st[10] ^ st[15] ^ st[20];
        bc[1] = st[1] ^ st[6] ^ st[11] ^ st[16] ^ st[21];
        bc[2] = st[2] ^ st[7] ^ st[12] ^ st[17] ^ st[22];
        bc[3] = st[3] ^ st[8] ^ st[13] ^ st[18] ^ st[23];
        bc[4] = st[4] ^ st[9] ^ st[14] ^ st[19] ^ st[24];
		
        t = bc[4] ^ ((bc[1] << 1) | (bc[1] >> (63)));
        st[0] ^= t;
        st[5] ^= t;
        st[10] ^= t;
        st[15] ^= t;
        st[20] ^= t;

        t = bc[0] ^ ((bc[2] << 1) | (bc[2] >> 63));
        st[1] ^= t;
        st[6] ^= t;
        st[11] ^= t;
        st[16] ^= t;
        st[21] ^= t;

        t = bc[1] ^ ((bc[3] << 1) | (bc[3] >> 63));
        st[2] ^= t;
        st[7] ^= t;
        st[12] ^= t;
        st[17] ^= t;
        st[22] ^= t;

        t = bc[2] ^ ((bc[4] << 1) | (bc[4] >> 63));
        st[3] ^= t;
        st[8] ^= t;
        st[13] ^= t;
        st[18] ^= t;
        st[23] ^= t;

        t = bc[3] ^ ((bc[0] << 1) | (bc[0] >> 63));
        st[4] ^= t;
        st[9] ^= t;
        st[14] ^= t;
        st[19] ^= t;
        st[24] ^= t;


        // Rho Pi
        t = st[1];

        bc[0] = st[10];
        st[10] = ((t << 1) | (t >> 63));
        t = bc[0];

        bc[0] = st[7];
        st[7] = ((t << 3) | (t >> 61));
        t = bc[0];

        bc[0] = st[11];
        st[11] = ((t << 6) | (t >> 58));
        t = bc[0];

        bc[0] = st[17];
        st[17] = ((t << 10) | (t >> 54));
        t = bc[0];

        bc[0] = st[18];
        st[18] = ((t << 15) | (t >> 49));
        t = bc[0];

        bc[0] = st[3];
        st[3] = ((t << 21) | (t >> 43));
        t = bc[0];

        bc[0] = st[5];
        st[5] = ((t << 28) | (t >> 36));
        t = bc[0];
		
        bc[0] = st[16];
        st[16] = ((t << 36) | (t >> 28));
        t = bc[0];

        bc[0] = st[8];
        st[8] = ((t << 45) | (t >> 19));
        t = bc[0];

        bc[0] = st[21];
        st[21] = ((t << 55) | (t >> 9));
        t = bc[0];
		
        bc[0] = st[24];
        st[24] = ((t << 2) | (t >> 62));
        t = bc[0];

        bc[0] = st[4];
        st[4] = ((t << 14) | (t >> 50));
        t = bc[0];

        bc[0] = st[15];
        st[15] = ((t << 27) | (t >> 37));
        t = bc[0];
		
        bc[0] = st[23];
        st[23] = ((t << 41) | (t >> 23));
        t = bc[0];

        bc[0] = st[19];
        st[19] = ((t << 56) | (t >> 8));
        t = bc[0];

        bc[0] = st[13];
        st[13] = ((t << 8) | (t >> 56));
        t = bc[0];
		
        bc[0] = st[12];
        st[12] = ((t << 25) | (t >> 39));
        t = bc[0];

        bc[0] = st[2];
        st[2] = ((t << 43) | (t >> 21));
        t = bc[0];

        bc[0] = st[20];
        st[20] = ((t << 62) | (t >> 2));
        t = bc[0];

        bc[0] = st[14];
        st[14] = ((t << 18) | (t >> 46));
        t = bc[0];
		
        bc[0] = st[22];
        st[22] = ((t << 39) | (t >> 25));
        t = bc[0];

        bc[0] = st[9];
        st[9] = ((t << 61) | (t >> 3));
        t = bc[0];

        bc[0] = st[6];
        st[6] = ((t << 20) | (t >> 44));
        t = bc[0];

        bc[0] = st[1];
        st[1] = ((t << 44) | (t >> 20));
        t = bc[0];

        bc[0] = st[0];
        bc[1] = st[1];
        bc[2] = st[2];
        bc[3] = st[3];
        bc[4] = st[4];
			
        st[0] ^= (~bc[1]) & bc[2];
        st[1] ^= (~bc[2]) & bc[3];
        st[2] ^= (~bc[3]) & bc[4];
        st[3] ^= (~bc[4]) & bc[0];
        st[4] ^= (~bc[0]) & bc[1];
		
        bc[0] = st[5];
        bc[1] = st[6];
        bc[2] = st[7];
        bc[3] = st[8];
        bc[4] = st[9];
			
        st[5] ^= (~bc[1]) & bc[2];
        st[6] ^= (~bc[2]) & bc[3];
        st[7] ^= (~bc[3]) & bc[4];
        st[8] ^= (~bc[4]) & bc[0];
        st[9] ^= (~bc[0]) & bc[1];
		
        bc[0] = st[10];
        bc[1] = st[11];
        bc[2] = st[12];
        bc[3] = st[13];
        bc[4] = st[14];
			
        st[10] ^= (~bc[1]) & bc[2];
        st[11] ^= (~bc[2]) & bc[3];
        st[12] ^= (~bc[3]) & bc[4];
        st[13] ^= (~bc[4]) & bc[0];
        st[14] ^= (~bc[0]) & bc[1];
		
        bc[0] = st[15];
        bc[1] = st[16];
        bc[2] = st[17];
        bc[3] = st[18];
        bc[4] = st[19];
			
        st[15] ^= (~bc[1]) & bc[2];
        st[16] ^= (~bc[2]) & bc[3];
        st[17] ^= (~bc[3]) & bc[4];
        st[18] ^= (~bc[4]) & bc[0];
        st[19] ^= (~bc[0]) & bc[1];
		
        bc[0] = st[20];
        bc[1] = st[21];
        bc[2] = st[22];
        bc[3] = st[23];
        bc[4] = st[24];
			
        st[20] ^= (~bc[1]) & bc[2];
        st[21] ^= (~bc[2]) & bc[3];
        st[22] ^= (~bc[3]) & bc[4];
        st[23] ^= (~bc[4]) & bc[0];
        st[24] ^= (~bc[0]) & bc[1];

        //  Iota
        st[0] ^= sha3f_rndc[round];
    }
}

// compute a keccak hash (md) of given byte length from "in"
int sha3(const uint8_t *in, int inlen, uint8_t *md, int mdlen)
{
    uint64_t st[25];    
    uint8_t temp[144];
    int i, rsiz, rsizw;

    rsiz = 200 - 2 * mdlen;
    rsizw = rsiz/8;
    
    memset(st, 0, sizeof(st));

    for(; inlen >= rsiz; inlen -= rsiz, in += rsiz)
	{
        for(i = 0; i < rsizw; i++)
		{
            st[i] ^= ((uint64_t *) in)[i];
		}

        sha3_f(st, SHA3_KECCAK_ROUNDS);
    }
    
    // last block and padding
    memcpy(temp, in, inlen);
    temp[inlen++] = 1;
    memset(temp + inlen, 0, rsiz - inlen);
    temp[rsiz - 1] |= 0x80;

    for(i = 0; i < rsizw; i++)
	{
        st[i] ^= ((uint64_t *) temp)[i];
	}

    sha3_f(st, SHA3_KECCAK_ROUNDS);
    memcpy(md, st, mdlen);

    return 0;
}

