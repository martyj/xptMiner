
#ifndef JHLIB_CUSTOM_BUFF_H
#define JHLIB_CUSTOM_BUFF_H

#include <stdint.h>

typedef uint32_t uint32;
typedef int32_t sint32;

typedef struct  
{
	void* objects;
	uint32 objectSize;
	uint32 objectCount;
	uint32 objectLimit;
	bool isPreallocated;
}customBuffer_t;

customBuffer_t* customBuffer_create(sint32 initialLimit, uint32 objectSize);
void customBuffer_free(customBuffer_t* customBuffer);
void customBuffer_add(customBuffer_t* customBuffer, void* data);
void customBuffer_add(customBuffer_t* customBuffer, void* data, uint32 count);
void customBuffer_insert(customBuffer_t* customBuffer, sint32 insertIndex, void* data);
void customBuffer_remove(customBuffer_t* customBuffer, uint32 removeIndex);
uint32 customBuffer_generateHash(customBuffer_t* customBuffer);

void* customBuffer_get(customBuffer_t* customBuffer, sint32 index);

customBuffer_t* customBuffer_duplicate(customBuffer_t* customBufferSource);

#endif

