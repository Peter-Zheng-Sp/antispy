#ifndef _H_MEMORYALLOCATOR_
#define _H_MEMORYALLOCATOR_

#include <ntifs.h>

PVOID MemoryAllocator_ZeroedAlloc(POOL_TYPE PoolType, SIZE_T Size);
void  MemoryAllocator_Free(PVOID Buffer);

#endif // _H_MEMORYALLOCATOR_
