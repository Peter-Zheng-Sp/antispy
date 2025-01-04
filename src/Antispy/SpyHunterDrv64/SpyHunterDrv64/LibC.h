#ifndef _H_LIBC_
#define _H_LIBC_

LPWSTR   LibC_wcscpy( LPWSTR dst, LPCWSTR src );

SIZE_T   LibC_wcslen( LPCWSTR str );

LPWSTR   LibC_wcscat( LPWSTR dst, LPCWSTR src );

void     LibC_memcpy(PVOID dest, PVOID src, SIZE_T size);

void     LibC_wmemcpy(PVOID dest, PVOID src, SIZE_T size);

void     LibC_memset(PVOID dest, LONG value, SIZE_T size);

void     LibC_ltow(LONG value, wchar_t* buffer);

ULONG    LibC_strhash(const CHAR* str);

#endif // _H_LIBC_
