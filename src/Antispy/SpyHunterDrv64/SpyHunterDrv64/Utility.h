#ifndef _H_UTILITY_
#define _H_UTILITY_

typedef BOOLEAN (*typedef_EnumerateExportsCallback)(PVOID context, ULONG nOrdinal, const PCHAR pszName, PVOID pCode);

void     Utility_InitUnicodeString(PUNICODE_STRING DestinationString, PCWSTR SourceString);

void     Utility_InitEmptyUnicodeString(PUNICODE_STRING DestinationString, PCWSTR Buffer, USHORT BufferSize);

void     Utility_InitAnsiString(PANSI_STRING DestinationString, PCSZ SourceString);

void     Utility_InitEmptyAnsiString(PANSI_STRING DestinationString, PCWSTR Buffer, USHORT BufferSize);

LONG     Utility_CompareUnicodeString(IN PCUNICODE_STRING String1, IN PCUNICODE_STRING String2, IN BOOLEAN CaseInSensitive);

BOOLEAN  Utility_EqualUnicodeString(IN PCUNICODE_STRING String1, IN PCUNICODE_STRING String2, IN BOOLEAN CaseInSensitive);

void     Utility_FreeUnicodeString(IN PUNICODE_STRING pUstr);

PKTHREAD Utility_GetCurrentThread();

PVOID    Utility_GetKiFastCallAddress();

BOOLEAN  Utility_IsAddressInKernel(ULONG_PTR Address);

BOOLEAN  Utility_CheckKernelAddressValid(PVOID VirtualAddress);

BOOLEAN  Utility_CheckAddressValid(PVOID VirtualAddress, ULONG_PTR Length, ULONG alignment, BOOLEAN bIsReadOp);

ULONG    Utility_VirtualAddressToRaw(PIMAGE_NT_HEADERS nh, ULONG address);

BOOLEAN  Utility_EnumeratePEExports(PVOID module_base, BOOLEAN need_convert_file_align, const PCHAR module_name, typedef_EnumerateExportsCallback callback, PVOID context);

PVOID    Utility_GetPEHeaderViaMemoryAddress(char *module_name, void *address);

NTSTATUS Utility_VerifyPECheckSum(ULONG_PTR nOldBase, ULONG_PTR nMapedBase);

BOOLEAN  Utility_IsUnicodeStringValid(PUNICODE_STRING SourceString);

#endif // _H_UTILITY_
