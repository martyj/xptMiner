#include"global.h"

#define SHA3_INITAL_BLOCK_SIZE 80

void maxcoin_process(minerMaxcoinBlock_t* block)
{
	sph_keccak512_context	 ctx_keccak;
	sph_shavite512_context	 ctx_shavite;
	sph_metis512_context	 ctx_metis;
	static unsigned char pblank[1];
	block->nonce = 0;

	uint32 target = *(uint32*)(block->targetShare+28);

	// since only the nonce changes we can calculate the first keccak round in advance
	unsigned char sha3out[64];
	minerMetiscoinBlock_t* indata = (minerMetiscoinBlock_t*)malloc(SHA3_INITAL_BLOCK_SIZE); // size of 80 as we don't care about full block

	for(uint32 n = 0; n < 0x10000; n++)
	{
		if(block->height != monitorCurrentBlockHeight)
		{
			break;
		}

		memcpy(indata, block, SHA3_INITAL_BLOCK_SIZE);

		sha3((unsigned char*)block, SHA3_INITAL_BLOCK_SIZE, sha3out, SHA3_512);
		sha3(sha3out, 64, sha3out, SHA3_512);

		if(*(uint32*)((uint8*)sha3out+28) <= target)
		{
			totalShareCount++;
			//block->nonce = rawBlock.nonce;
			xptMiner_submitShare(block);
		}

		block->nonce++;

		totalCollisionCount += 1; // count in steps of 0x8000
	}
}