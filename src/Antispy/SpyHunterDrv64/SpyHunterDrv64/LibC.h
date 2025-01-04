#ifndef _H_LIBC_
#define _H_LIBC_

LPWSTR   LibC_wcscpy( LPWSTR dst, LPCWSTR src );

SIZE_T   LibC_wcslen( LPCWSTR str );

LPWSTR   LibC_wcscat( LPWSTR dst, LPCWSTR src );

void     LibC_memcpy(PVOID dest, PVOID src, SIZE_T size);

int      LibC_memcmp(PVOID ptr1, PVOID ptr2, SIZE_T n);

void     LibC_memset(PVOID dest, LONG value, SIZE_T size);

void     LibC_ltow(LONG value, WCHAR* buffer);

ULONG    LibC_strhash(const CHAR* str);

#endif // _H_LIBC_
