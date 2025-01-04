#include "Stdafx.h"
#include "LibC.h"

LPWSTR LibC_wcscpy( LPWSTR dst, LPCWSTR src )
{
	WCHAR *p = dst;
	while ((*p++ = *src++));
	return dst;
}

SIZE_T LibC_wcslen( LPCWSTR str )
{
	const WCHAR *s = str;
	while (*s) s++;
	return s - str;
}

LPWSTR LibC_wcscat( LPWSTR dst, LPCWSTR src )
{
	LibC_wcscpy( dst + wcslen(dst), src );
	return dst;
}

void LibC_memcpy(PVOID dest, PVOID src, SIZE_T size)
{
	volatile BYTE *destPtr = NULL, *srcPtr = NULL;
	for (destPtr = (volatile BYTE*)dest, srcPtr = (volatile BYTE*)src; size; size--) {
		*destPtr++ = *srcPtr++;
	}
}

int LibC_memcmp(PVOID ptr1, PVOID ptr2, SIZE_T n)
{
    unsigned char* p1 = NULL, * p2 = NULL;

    for (p1 = (unsigned char*)ptr1, p2 = (unsigned char*)ptr2; n; n--, p1++, p2++)
    {
        if (*p1 < *p2) return -1;
        if (*p1 > *p2) return 1;
    }
    return 0;
}

void LibC_memset(PVOID dest, LONG value, SIZE_T size)
{
	volatile BYTE* destPtr = NULL;
	for (destPtr = (volatile BYTE*)dest; size; size--) {
		*destPtr++ = (BYTE)value;
	}
}

void LibC_ltow(LONG value, WCHAR* buffer)
{
	LONG length = 0;
	LONG i = 0;

	if (value < 0) {
		*buffer++ = L'-';
		value = -value;
	}

	for (i = value; i; i /= 10) {
		length++;
	}

	for (i = 0; i < length; i++) {
		buffer[length - i - 1] = L'0' + value % 10;
		value /= 10;
	}

	buffer[length] = L'\0';
}

ULONG LibC_strhash(const CHAR* str)
{
	ULONG hash = 0;

	while (*str) {
		hash = ROTR(hash, 13) + *str++;
	}

	return hash;
}
