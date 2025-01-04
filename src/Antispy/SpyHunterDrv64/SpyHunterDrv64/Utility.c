#include "Stdafx.h"
#include "Utility.h"
#include "SystemDefine.h"
#include "LibC.h"
#include "Logger.h"

void Utility_InitUnicodeString(PUNICODE_STRING DestinationString, PCWSTR SourceString)
{
    size_t Length = wcslen(SourceString) * sizeof(WCHAR);

    NT_ASSERT(Length < MAX_USTRING);

    if (Length >= MAX_USTRING)
    {
        Length = MAX_USTRING - sizeof(UNICODE_NULL);
    }

    DestinationString->Length = (USHORT)Length;
    DestinationString->MaximumLength = DestinationString->Length + sizeof(UNICODE_NULL);
    DestinationString->Buffer = (PWSTR)SourceString;
}

void Utility_InitEmptyUnicodeString(PUNICODE_STRING DestinationString, PCWSTR Buffer, USHORT BufferSize)
{
    LibC_memset(DestinationString, 0, sizeof(*DestinationString));
    DestinationString->MaximumLength = BufferSize;
    DestinationString->Buffer = (PWSTR)Buffer;
}

void Utility_InitAnsiString(PANSI_STRING DestinationString, PCSZ SourceString)
{
    size_t Length = strlen(SourceString) * sizeof(CHAR);

    NT_ASSERT(Length < MAXUSHORT);

    if (Length >= MAXUSHORT)
    {
        Length = MAXUSHORT - sizeof(ANSI_NULL);
    }

    DestinationString->Length = (USHORT)Length;
    DestinationString->MaximumLength = DestinationString->Length + sizeof(ANSI_NULL);
    DestinationString->Buffer = (PCHAR)SourceString;
}

void Utility_InitEmptyAnsiString(PANSI_STRING DestinationString, PCWSTR Buffer, USHORT BufferSize)
{
    LibC_memset(DestinationString, 0, sizeof(*DestinationString));
    DestinationString->MaximumLength = BufferSize;
    DestinationString->Buffer = (PCHAR)Buffer;
}

LONG Utility_CompareUnicodeString(IN PCUNICODE_STRING String1, IN PCUNICODE_STRING String2, IN BOOLEAN CaseInSensitive)
/*++

Routine Description:

The RtlCompareUnicodeString function compares two counted strings.  The
return value indicates if the strings are equal or String1 is less than
String2 or String1 is greater than String2.

The CaseInSensitive parameter specifies if case is to be ignored when
doing the comparison.

Arguments:

String1 - Pointer to the first string.

String2 - Pointer to the second string.

CaseInsensitive - TRUE if case should be ignored when doing the
    comparison.

Return Value:

Signed value that gives the results of the comparison:

    Zero - String1 equals String2

    < Zero - String1 less than String2

    > Zero - String1 greater than String2


--*/
{
    PCWSTR s1, s2, Limit;
    LONG n1, n2;
    ULONG c1, c2;

    ASSERT_WELL_FORMED_UNICODE_STRING_IN(String1);
    ASSERT_WELL_FORMED_UNICODE_STRING_IN(String2);

    s1 = String1->Buffer;
    s2 = String2->Buffer;
    n1 = String1->Length;
    n2 = String2->Length;

    NT_ASSERT(!(((((ULONG_PTR)s1 & 1) != 0) || (((ULONG_PTR)s2 & 1) != 0)) && (n1 != 0) && (n2 != 0)));

    Limit = (PWCHAR)((PCHAR)s1 + (n1 <= n2 ? n1 : n2));
    if (CaseInSensitive)
    {
        while (s1 < Limit)
        {
            c1 = *s1;
            c2 = *s2;
            if (c1 != c2)
            {
                //
                // Note that this needs to reference the translation table!
                //

                c1 = RtlUpcaseUnicodeChar((WCHAR)c1);
                c2 = RtlUpcaseUnicodeChar((WCHAR)c2);
                if (c1 != c2)
                {
                    return (LONG)(c1) - (LONG)(c2);
                }
            }

            s1 += 1;
            s2 += 1;
        }
    }
    else
    {
        while (s1 < Limit)
        {
            c1 = *s1;
            c2 = *s2;
            if (c1 != c2)
            {
                return (LONG)(c1) - (LONG)(c2);
            }

            s1 += 1;
            s2 += 1;
        }
    }

    return n1 - n2;
}

BOOLEAN Utility_EqualUnicodeString(IN PCUNICODE_STRING String1, IN PCUNICODE_STRING String2, IN BOOLEAN CaseInSensitive)
{
	return (0 == Utility_CompareUnicodeString(String1, String2, CaseInSensitive));
}

void Utility_FreeUnicodeString(IN PUNICODE_STRING pUstr)
{
	if (pUstr->Buffer)
	{
		ExFreePool(pUstr->Buffer);
		LibC_memset(pUstr, 0, sizeof(*pUstr));
	}
}

PKTHREAD Utility_GetCurrentThread()
{
#if defined(_M_AMD64) || defined(_WIN64)
    return (PKTHREAD)__readgsqword(0x188);
#else
    return (PKTHREAD)__readfsdword(0x124);
#endif
}

PVOID Utility_GetKiFastCallAddress()
{
#if defined(_M_AMD64) || defined(_WIN64)
	return (void *)__readmsr(0x0C0000082);
#else
	return (void *)__readmsr(0x176);
#endif
}

BOOLEAN Utility_IsAddressInKernel(ULONG_PTR Address)
{
	if (Address >= (ULONG_PTR)MmSystemRangeStart)
	{
		return TRUE;
	}

	return FALSE;
}

BOOLEAN Utility_CheckKernelAddressValid(PVOID VirtualAddress) {
	const ULONG_PTR StartAddress = (ULONG_PTR)VirtualAddress;
	UINT_PTR kernelbase = 0x7fffffffffffffffULL;
	PHYSICAL_ADDRESS physical = {0};

	// cannonical check. Bits 48 to 63 must match bit 47
	UINT_PTR toppart = (StartAddress >> 47);

	if (!StartAddress) {
		return FALSE;
	}

	if (toppart & 1) {
		// toppart must be 0x1ffff
		if (toppart != 0x1ffff)
			return FALSE;
	} else {
		// toppart must be 0
		if (toppart != 0)
			return FALSE;
	}

	if (StartAddress < kernelbase) {
		return TRUE;
	} else {
		physical.QuadPart = 0;
		physical = MmGetPhysicalAddress(VirtualAddress);
		return (physical.QuadPart != 0);
	}
}

BOOLEAN Utility_CheckAddressValid(PVOID VirtualAddress, ULONG_PTR Length, ULONG alignment,
                                            BOOLEAN bIsReadOp) {
    BOOLEAN res = FALSE;
    PVOID addr = VirtualAddress;
    ULONG len = 0;

    if (VirtualAddress == NULL) {
        return FALSE;
    }

    SE_TRY_BEGIN

	if ((ULONG_PTR)addr >= MmUserProbeAddress) {
		while (addr) {
			if (!Utility_CheckKernelAddressValid(addr)) {
				SE_LEAVE
			}

			len += PAGE_SIZE;
			if (len >= Length) {
				if ((((ULONG_PTR)VirtualAddress + Length) & ~(PAGE_SIZE - 1)) == ((ULONG_PTR)addr & ~(PAGE_SIZE - 1)) ||
					len - Length >= PAGE_SIZE) {
						break;
				}
			}

			addr = MAKE_PTR(PVOID, addr, PAGE_SIZE);
		}
	} else {
		if (bIsReadOp) {
			ProbeForRead(VirtualAddress, Length, alignment);
		} else {
			ProbeForWrite(VirtualAddress, Length, alignment);
		}
	}

    res = TRUE;

    SE_TRY_CATCH
    res = FALSE;
    SE_TRY_END

    return res;
}

/*
 * fully loaded dlls are mapped into memory section by section
 * a dll file on hard-disk is stored in a more packed format
 * this function converts a mapped/virtual address to the packed/raw address
 */
ULONG Utility_VirtualAddressToRaw(PIMAGE_NT_HEADERS nh, ULONG address) 
{
    PIMAGE_SECTION_HEADER sections = NULL;
    int i1 = 0;

    if (nh->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
        sections = (PIMAGE_SECTION_HEADER)(((ULONG_PTR)&nh->OptionalHeader) + sizeof(IMAGE_OPTIONAL_HEADER64));
    else
        sections = (PIMAGE_SECTION_HEADER)(((ULONG_PTR)&nh->OptionalHeader) + sizeof(IMAGE_OPTIONAL_HEADER32));
    for (i1 = 0; i1 < nh->FileHeader.NumberOfSections; i1++) {
        if ((address >= sections[i1].VirtualAddress) &&
            ((i1 == nh->FileHeader.NumberOfSections - 1) || (address < sections[i1 + 1].VirtualAddress))) {
            // found the image section header which this virtual address is in
            return address - sections[i1].VirtualAddress + sections[i1].PointerToRawData;
        }
    }

    return address;
}

/*
 * If you map or read original file to memory, but not use loader process, you should set 'need_convert_file_align' as
 * TRUE.
 */
BOOLEAN Utility_EnumeratePEExports(PVOID module_base, BOOLEAN need_convert_file_align,
                                   const PCHAR module_name, typedef_EnumerateExportsCallback callback,
                                   PVOID context) {
    BOOLEAN ret = TRUE;
    LONG n = 0, nFunc = 0;
    ULONG nOrdinal = 0;
    BOOLEAN ncfa = need_convert_file_align;

    PVOID pProcAddress = NULL;
    PIMAGE_EXPORT_DIRECTORY pExportDir = NULL;
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNtHeader = NULL;
    PIMAGE_NT_HEADERS32 nh32 = NULL;
    PIMAGE_NT_HEADERS64 nh64 = NULL;

    PBYTE pExportDirEnd = NULL;
    LONG* pdwFunctions = NULL;
    LONG* pdwNames = NULL;
    PUSHORT pwOrdinals = NULL;
    PCHAR pDllName = NULL;
    ULONG exportRVA = 0;

    if (module_base == NULL) {
        return FALSE;
    }

    SE_TRY_BEGIN

    pDosHeader = (PIMAGE_DOS_HEADER)module_base;
    if (!Utility_CheckAddressValid(pDosHeader, sizeof(IMAGE_DOS_HEADER), 1, TRUE) &&
        pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        return FALSE;
    }

    pNtHeader = MAKE_PTR(PIMAGE_NT_HEADERS, pDosHeader, pDosHeader->e_lfanew);
    if (!Utility_CheckAddressValid(pNtHeader, sizeof(IMAGE_NT_HEADERS), 1, TRUE) ||
        pNtHeader->Signature != IMAGE_NT_SIGNATURE || pNtHeader->FileHeader.SizeOfOptionalHeader == 0) {
        return FALSE;
    }

    if (pNtHeader->FileHeader.Machine == IMAGE_FILE_MACHINE_I386) {
        // x86
        nh32 = (PIMAGE_NT_HEADERS32)pNtHeader;
        exportRVA = ((PIMAGE_DATA_DIRECTORY)(nh32->OptionalHeader.DataDirectory + IMAGE_DIRECTORY_ENTRY_EXPORT))
                        ->VirtualAddress;

        pExportDir = MAKE_PTR(PIMAGE_EXPORT_DIRECTORY, pDosHeader,
                              ((ncfa) ? Utility_VirtualAddressToRaw(pNtHeader, exportRVA) : exportRVA));

        pExportDirEnd = MAKE_PTR(PBYTE, pExportDir,
            nh32->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size);
        if (!Utility_CheckAddressValid(
                pExportDir, nh32->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size, 1, TRUE)) {
            return FALSE;
        }
    } else {
		// x64
        nh64 = (PIMAGE_NT_HEADERS64)pNtHeader;
        exportRVA = ((PIMAGE_DATA_DIRECTORY)(nh64->OptionalHeader.DataDirectory + IMAGE_DIRECTORY_ENTRY_EXPORT))
                        ->VirtualAddress;

        pExportDir = MAKE_PTR(PIMAGE_EXPORT_DIRECTORY, pDosHeader,
                              ((ncfa) ? Utility_VirtualAddressToRaw(pNtHeader, exportRVA) : exportRVA));

        pExportDirEnd = MAKE_PTR(PBYTE, pExportDir,
            nh64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size);
        if (!Utility_CheckAddressValid(
                pExportDir, nh64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size, 1, TRUE)) {
            return FALSE;
        }
    }

    /*
     * Because windows10 19h1 or later, ntoskrnl.exe has many PE signature, so we should verify the module name with
     * "ntoskrnl".
     */
    if (module_name) {
        pDllName = MAKE_PTR(
            PCHAR, pDosHeader,
            ((ncfa) ? Utility_VirtualAddressToRaw(pNtHeader, pExportDir->Name) : pExportDir->Name));
        if (!Utility_CheckAddressValid(pDllName, (ULONG)strlen(module_name), 1, TRUE)) {
            return FALSE;
        }

        if (0 != strncmp(pDllName, module_name, strlen(module_name))) {
            return FALSE;
        }
    }

    pdwFunctions =
        MAKE_PTR(LONG*, pDosHeader,
                 ((ncfa) ? Utility_VirtualAddressToRaw(pNtHeader, pExportDir->AddressOfFunctions)
                         : pExportDir->AddressOfFunctions));
    if (!Utility_CheckAddressValid(pdwFunctions, pExportDir->NumberOfFunctions * sizeof(LONG), 1, TRUE)) {
        return FALSE;
    }

    pdwNames = MAKE_PTR(LONG*, pDosHeader,
                        ((ncfa) ? Utility_VirtualAddressToRaw(pNtHeader, pExportDir->AddressOfNames)
                                : pExportDir->AddressOfNames));
    if (!Utility_CheckAddressValid(pdwNames, pExportDir->NumberOfNames * sizeof(LONG), 1, TRUE)) {
        return FALSE;
    }

    pwOrdinals =
        MAKE_PTR(PUSHORT, pDosHeader,
                 ((ncfa) ? Utility_VirtualAddressToRaw(pNtHeader, pExportDir->AddressOfNameOrdinals)
                         : pExportDir->AddressOfNameOrdinals));
    if (!Utility_CheckAddressValid(pwOrdinals, pExportDir->NumberOfNames * sizeof(USHORT), 1, TRUE)) {
        return FALSE;
    }

    for (nFunc = 0; nFunc < (LONG)pExportDir->NumberOfFunctions; nFunc++) {
        PBYTE pbCode =
            (pdwFunctions != NULL)
                ? MAKE_PTR(PBYTE, pDosHeader,
                           ((ncfa) ? Utility_VirtualAddressToRaw(pNtHeader, pdwFunctions[nFunc])
                                   : pdwFunctions[nFunc]))
                : NULL;

        PCHAR pszName = NULL;

        // if the pointer is in the export region, then it is a forwarder.
        if (pbCode > (PBYTE)pExportDir && pbCode < pExportDirEnd) {
            pbCode = NULL;
        }

        for (n = 0; n < (LONG)pExportDir->NumberOfNames; n++) {
            if (pwOrdinals[n] == nFunc) {
                pszName = (pdwNames != NULL)
                              ? MAKE_PTR(PCHAR, pDosHeader,
                                         ((ncfa) ? Utility_VirtualAddressToRaw(pNtHeader, pdwNames[n])
                                                 : pdwNames[n]))
                              : NULL;
                break;
            }
        }
        nOrdinal = pExportDir->Base + nFunc;

        if (callback && !callback(context, nOrdinal, pszName, pbCode)) {
            break;
        }
    }

    SE_TRY_CATCH
    ret = FALSE;
    SE_TRY_END

    return ret;
}

PVOID Utility_GetPEHeaderViaMemoryAddress(char *module_name, void *address)
{
	void *ptr_base = NULL;
	size_t spec_func_base = 0, cursor_address = 0;
	size_t spec_func_address = (size_t)address;
	const size_t MIN_USER_ADDRESS = 0x10000;

#if defined(_M_AMD64) || defined(_WIN64)
	// MIN_KERNEL_ADDRESS: Windows XP through 7 value. On newer systems this is a bit higher, but not that much.
	const size_t MIN_KERNEL_ADDRESS = 0xFFFF080000000000;
	const size_t MAX_KERNEL_ADDRESS = 0xFFFFFFFFFFFFFFFF;
	const size_t MAX_USER_ADDRESS = 0x7FFFFFFEFFFF;
#else
	const size_t MIN_KERNEL_ADDRESS = 0x80000000;
	const size_t MAX_KERNEL_ADDRESS = 0xffffffff;
	const size_t MAX_USER_ADDRESS = 0x7ffeffff;
#endif

#ifdef _KERNEL_MODE
	const size_t MAX_ADDRESS = MAX_KERNEL_ADDRESS;
	const size_t MIN_ADDRESS = MIN_KERNEL_ADDRESS;
#else
	const size_t MAX_ADDRESS = MAX_USER_ADDRESS;
	const size_t MIN_ADDRESS = MIN_USER_ADDRESS;
#endif

#if defined(_M_AMD64) || defined(_WIN64)
		spec_func_base = spec_func_address & 0xfffffffffffff000;
#else
		spec_func_base = spec_func_address & 0xfffff000;
#endif

	if (!address || (size_t)address > MAX_ADDRESS)
	{
		return NULL;
	}

	for (cursor_address = spec_func_base; cursor_address >= MIN_ADDRESS; cursor_address -= PAGE_SIZE)
	{
		SE_TRY_BEGIN
			if (!Utility_CheckAddressValid((void *)(cursor_address), sizeof(void *), 1, TRUE)
				|| !Utility_CheckAddressValid((void *)(cursor_address + 0x3c), sizeof(void *), 1, TRUE)
				|| !Utility_CheckAddressValid((void *)(cursor_address + *MAKE_PTR(PULONG, cursor_address, 0x3c)),
				sizeof(void *), 1, TRUE))
			{
				continue;
			}
			if (*(USHORT *)(cursor_address) == IMAGE_DOS_SIGNATURE
				&& *(USHORT *)(cursor_address + *MAKE_PTR(PULONG, cursor_address, 0x3c)) == IMAGE_NT_SIGNATURE)
			{
				if (Utility_EnumeratePEExports((void *)cursor_address, FALSE, module_name, NULL, NULL))
				{
					ptr_base = (void *)(cursor_address);
					break;
				}
			}
			SE_TRY_CATCH
				continue;
			SE_TRY_END
	}

	return ptr_base;
}

NTSTATUS Utility_VerifyPECheckSum(ULONG_PTR nOldBase, ULONG_PTR nMapedBase)
{
	NTSTATUS status = STATUS_UNSUCCESSFUL;

	if (nOldBase > 0 && nMapedBase > 0)
	{
		PIMAGE_DOS_HEADER pDosHeader;
		PIMAGE_NT_HEADERS pNTHeader;
		ULONG nCheckSumOld = 0, nCheckSumReload = 0;

		LOG_INFO(L"VerifyCheckSum-> nOldBase: 0x%llX, nMapedBase: 0x%llX", nOldBase, nMapedBase);

		__try 
		{
			pDosHeader = (PIMAGE_DOS_HEADER)nOldBase;
			if (!Utility_CheckAddressValid(pDosHeader, sizeof(IMAGE_DOS_HEADER), 1, TRUE) &&
				pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
					return FALSE;
			}

			pNTHeader = MAKE_PTR(PIMAGE_NT_HEADERS, pDosHeader, pDosHeader->e_lfanew);
			if (!Utility_CheckAddressValid(pNTHeader, sizeof(IMAGE_NT_HEADERS), 1, TRUE) ||
				pNTHeader->Signature != IMAGE_NT_SIGNATURE || pNTHeader->FileHeader.SizeOfOptionalHeader == 0) {
					return FALSE;
			}

			nCheckSumOld = pNTHeader->OptionalHeader.CheckSum;

			pDosHeader = (PIMAGE_DOS_HEADER)nMapedBase;
			if (!Utility_CheckAddressValid(pDosHeader, sizeof(IMAGE_DOS_HEADER), 1, TRUE) &&
				pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
					return FALSE;
			}

			pNTHeader = MAKE_PTR(PIMAGE_NT_HEADERS, pDosHeader, pDosHeader->e_lfanew);
			if (!Utility_CheckAddressValid(pNTHeader, sizeof(IMAGE_NT_HEADERS), 1, TRUE) ||
				pNTHeader->Signature != IMAGE_NT_SIGNATURE || pNTHeader->FileHeader.SizeOfOptionalHeader == 0) {
					return FALSE;
			}

			nCheckSumReload = pNTHeader->OptionalHeader.CheckSum;

			if (nCheckSumReload > 0				&& 
				nCheckSumOld  > 0				&&
				nCheckSumOld == nCheckSumReload)
			{
				LOG_INFO(L"CheckSum is ok.");
				status = STATUS_SUCCESS;
			}
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
			LOG_ERROR(L"VerifyCheckSum exception");
			status = STATUS_UNSUCCESSFUL;
		}
	}

	return status;
}

BOOLEAN Utility_IsUnicodeStringValid(PUNICODE_STRING SourceString)
{
	if (SourceString == NULL || !Utility_CheckAddressValid(SourceString, sizeof(UNICODE_STRING), 1, TRUE))
		return FALSE;

	if (((SourceString->Length % sizeof(WCHAR)) != 0) || ((SourceString->MaximumLength % sizeof(WCHAR)) != 0)
		|| (SourceString->Length > SourceString->MaximumLength)
		|| (SourceString->MaximumLength > (UNICODE_STRING_MAX_CHARS * sizeof(WCHAR))))
	{
		return FALSE;
	}
	else if ((SourceString->Buffer == NULL) && ((SourceString->Length != 0) || (SourceString->MaximumLength != 0)))
	{
		return FALSE;
	}

	return TRUE;
}
