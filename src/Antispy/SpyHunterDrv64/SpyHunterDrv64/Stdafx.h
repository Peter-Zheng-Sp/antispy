#ifndef _H_STDAFX_
#define _H_STDAFX_

#ifndef __cplusplus
#include <conio.h>
#include <wchar.h>
#endif // __cplusplus

#include <ntifs.h>

#include <ntddk.h>
#include <ntdef.h>

#include <assert.h>
#include <ctype.h>
#include <mmintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <ntddndis.h>
#include <ntimage.h>
#include <ntintsafe.h>
#include <ntstrsafe.h>
#include <sal.h>
#include <sddl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wdmsec.h>
#include <windef.h>

#if !defined(DBG) && defined(_USE_VMPROTECT)

#define VCRYPT(__XXX__) VMProtectDecryptStringA(__XXX__)
#define VCRYPTW(__XXX__) VMProtectDecryptStringW(__XXX__)
#define VMPROTECT_BEGIN() VMProtectBeginUltra(__FUNCTION__)
#define VMPROTECT_VIRTUAL_BEGIN() VMProtectBeginVirtualization(__FUNCTION__)
#define VMPROTECT_MUTATION_BEGIN() VMProtectBeginMutation(__FUNCTION__)
#define VMPROTECT_BEGIN_EX(_A) VMProtectBeginUltra(_A)
#define VMPROTECT_VIRTUAL_BEGIN_EX(_A) VMProtectBeginVirtualization(_A)
#define VMPROTECT_MUTATION_BEGIN_EX(_A) VMProtectBeginMutation(_A)
#define VMPROTECT_END() VMProtectEnd()

#else

#define VCRYPT(__XXX__) __XXX__
#define VCRYPTW(__XXX__) __XXX__
#define VMPROTECT_BEGIN()
#define VMPROTECT_VIRTUAL_BEGIN()
#define VMPROTECT_MUTATION_BEGIN()
#define VMPROTECT_BEGIN_EX(_A)
#define VMPROTECT_VIRTUAL_BEGIN_EX(_A)
#define VMPROTECT_MUTATION_BEGIN_EX(_A)
#define VMPROTECT_END()

#endif

/*
 * Others
 */
#define shd_assert(__XX__) NT_ASSERT((__XX__))
#define SHD_POOL_TAG 'SPTG'

#define shd_assert_static(__XX__) _STATIC_ASSERT((__XX__))

/////////

#ifndef PAGE_SIZE
#define PAGE_SIZE 0x1000
#endif

/////////

#define SE_TRY_BEGIN __try {
#define SE_TRY_CATCH \
    }                \
    __except (EXCEPTION_EXECUTE_HANDLER) {
#define SE_TRY_CATCH_EX(_x_) \
    }                        \
    __except (_x_) {
#define SE_TRY_END }
#define SE_LEAVE __leave;

/////////

#define AUTO_TRY_BEGIN SE_TRY_BEGIN
#define AUTO_TRY_CATCH SE_TRY_CATCH
#define AUTO_TRY_CATCH_EX(_x_) SE_TRY_CATCH_EX(_x_)
#define AUTO_TRY_END SE_TRY_END
#define AUTO_LEAVE SE_LEAVE

/////////

#ifndef va_copy
#define va_copy(dest, src) (dest = src)
#endif

#define stringify(a) stringify_(a)
#define stringify_(a) #a

#define MAKE_PTR(cast, ptr, addVal) (cast)((SIZE_T)ptr + (SIZE_T)addVal)

#define PTR_ADD_OFFSET(Pointer, Offset) ((PVOID)((ULONG_PTR)(Pointer) + (ULONG_PTR)(Offset)))
#define PTR_SUB_OFFSET(Pointer, Offset) ((PVOID)((ULONG_PTR)(Pointer) - (ULONG_PTR)(Offset)))

/*
 * Returns TRUE, if the bitness of the current process is equal to bits.
 */
#define BITNESS(bits) (sizeof(LPVOID) * 8 == (bits))

/*
 * Returns either if32 or if64 depending on the bitness of the current process.
 */
#define COALESCE_BITNESS(if32, if64) (sizeof(LPVOID) == 4 ? (if32) : (if64))

/*
 * Rotates a value right by a defined number of bits.
 */
#define ROTR(value, bits) ((DWORD)(value) >> (bits) | (DWORD)(value) << (32 - (bits)))

// calculate field at the offset of the structure
#ifdef _WIN64
#define OFFSETOF(s, m) ((SIZE_T)((ULONG_PTR) & (((s *)0)->m)))
#else
#define OFFSETOF(s, m) ((SIZE_T) & (((s *)0)->m))
#endif

#define MAKE_PTR(cast, ptr, addVal) (cast)((SIZE_T)ptr + (SIZE_T)addVal)

#ifdef __cplusplus
#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END }
#define EXTERN_C extern "C"
#else
#define EXTERN_C_BEGIN
#define EXTERN_C_END
#define EXTERN_C extern
#endif  // __cplusplus

#ifndef NonPagedPoolNx
#define NonPagedPoolNx 512
#endif

// This macro returns the address of a field given the type of the structure, pointer to
// the base of the structure and the name of the field whose address is to be computed.
// This returns the same value as &Base->Member
//

#ifndef EX_FIELD_ADDRESS
#define EX_FIELD_ADDRESS(Type, Base, Member) ((PUCHAR)Base + FIELD_OFFSET(Type, Member))
#endif

//
// This macro is used like a C for loop and iterates over all the entries in the list.
//
// _Type - Name of the data type for each element in the list
// _Link - Name of the field of type LIST_ENTRY used to link the elements.
// _Head - Pointer to the head of the list.
// _Current - Points to the iterated element.
//
// Example:     EX_FOR_EACH_IN_LIST(SYSTEM_FIRMWARE_TABLE_HANDLER_NODE,
//                                  FirmwareTableProviderList,
//                                  &ExpFirmwareTableProviderListHead,
//                                  HandlerListCurrent) {
//
//                  /* Do something with Current */
//
//              }
//

#ifndef EX_FOR_EACH_IN_LIST
#define EX_FOR_EACH_IN_LIST(_Type, _Link, _Head, _Current)                 \
    for ((_Current) = CONTAINING_RECORD((_Head)->Flink, _Type, _Link);     \
         (_Head) != (PLIST_ENTRY)EX_FIELD_ADDRESS(_Type, _Current, _Link); \
         (_Current) = CONTAINING_RECORD(((PLIST_ENTRY)EX_FIELD_ADDRESS(_Type, _Current, _Link))->Flink, _Type, _Link))
#endif // EX_FOR_EACH_IN_LIST

#endif // _H_STDAFX_
