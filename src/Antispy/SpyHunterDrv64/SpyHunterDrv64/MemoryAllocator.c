#include "Stdafx.h"
#include "Utility.h"
#include "LibC.h"
#include "MemoryAllocator.h"

PVOID MemoryAllocator_ZeroedAlloc(POOL_TYPE PoolType, SIZE_T Size)
{
	const PVOID Buffer = ExAllocatePoolWithTag(PoolType, Size, SHD_POOL_TAG);
	if (Buffer)
	{
		LibC_memset(Buffer, 0, Size);
	}

	return Buffer;
}

void MemoryAllocator_Free(PVOID Buffer)
{
	if (Buffer)
	{
		ExFreePoolWithTag(Buffer, SHD_POOL_TAG);
		Buffer = NULL;
	}
}
