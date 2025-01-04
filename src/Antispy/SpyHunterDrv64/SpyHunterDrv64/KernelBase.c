#include "Stdafx.h"
#include "KernelBase.h"
#include "Logger.h"
#include "SystemDefine.h"
#include "MemoryAllocator.h"
#include "GlobalData.h"
#include "Utility.h"
#include "LibC.h"

NTSTATUS        
ZwQuerySystemInformation(IN SYSTEM_INFORMATION_CLASS SystemInformationClass,    
						 OUT PVOID SystemInformation,    
						 IN ULONG SystemInformationLength,    
						 OUT PULONG ReturnLength OPTIONAL);

static NTSTATUS MapSectionAndCheckSum(WCHAR* wszPath, ULONG_PTR OrginBase)
{
	NTSTATUS ntStatus = STATUS_UNSUCCESSFUL;
	UNICODE_STRING usKrnlPath = {0};
	OBJECT_ATTRIBUTES ObjectAttributes = {0}; 
	HANDLE hFile = NULL;
	HANDLE hSection = NULL; 
	IO_STATUS_BLOCK IoStatusBlock = {0}; 
	PVOID BaseAddress = NULL; 
	SIZE_T size = 0;  

	if (!wszPath || !OrginBase)
	{
		return ntStatus;
	}

	Utility_InitUnicodeString(&usKrnlPath, wszPath);

	LOG_INFO(L"CheckSum Path: %wZ", &usKrnlPath);

	InitializeObjectAttributes(&ObjectAttributes,
		&usKrnlPath,
		OBJ_CASE_INSENSITIVE|OBJ_KERNEL_HANDLE,
		NULL,
		NULL);

	ntStatus = ZwOpenFile(&hFile, 
		SYNCHRONIZE | FILE_EXECUTE, 
		&ObjectAttributes, 
		&IoStatusBlock,   
		FILE_SHARE_READ,   
		FILE_SYNCHRONOUS_IO_NONALERT);

	if (NT_SUCCESS(ntStatus))
	{
		ObjectAttributes.ObjectName = 0;  

		ntStatus = ZwCreateSection(&hSection, 
			SECTION_MAP_EXECUTE | SECTION_MAP_READ | SECTION_QUERY, 
			&ObjectAttributes, 
			0,
			PAGE_EXECUTE, 
			MEM_IMAGE,
			hFile
			);  

		if (NT_SUCCESS(ntStatus))
		{
			ntStatus = ZwMapViewOfSection(hSection, 
				NtCurrentProcess(), 
				&BaseAddress, 
				0, 
				0x1000, 
				0, 
				&size, 
				ViewShare, 
				MEM_TOP_DOWN, 
				PAGE_READWRITE
				);   

			if (NT_SUCCESS(ntStatus))
			{
				ntStatus = Utility_VerifyPECheckSum(OrginBase, (ULONG_PTR)BaseAddress);
				if (NT_SUCCESS(ntStatus))
				{
					LOG_INFO(L"VerifyCheckSum ok");
				}
				else
				{
					ntStatus = STATUS_INVALID_DISPOSITION;
				}

				ZwUnmapViewOfSection(NtCurrentProcess(),BaseAddress);
			}//ZwMapViewOfSection Success
			ZwClose(hSection); 
		}//ZwCreateSection Success
		ZwClose( hFile ); 
	}//Open File Success

	return ntStatus;
}

BOOLEAN KernelBase_QueryKernelModuleInfoLDR(IN PUNICODE_STRING UnKernelName, OUT PULONG_PTR SystemKernelModuleBase, OUT PSIZE_T SystemKernelModuleSize)
{
	PLIST_ENTRY lpEntry = (PLIST_ENTRY)g_GlobalData.pDriverObject->DriverSection;
	PLIST_ENTRY lpOrigin = lpEntry;
	if (!lpEntry)
	{
		return FALSE;
	}

	if (!UnKernelName || !SystemKernelModuleBase || !SystemKernelModuleSize)
	{
		return FALSE;
	}

	lpEntry = lpEntry->Flink;
	while (lpEntry && lpEntry != lpOrigin) 
	{
		PLDR_DATA_TABLE_ENTRY pLdrEntry = CONTAINING_RECORD(lpEntry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
		if (Utility_IsUnicodeStringValid(&pLdrEntry->BaseDllName) && 
			Utility_EqualUnicodeString(&pLdrEntry->BaseDllName, UnKernelName, TRUE))
		{
			*SystemKernelModuleBase = (ULONG_PTR)pLdrEntry->DllBase;
			*SystemKernelModuleSize = pLdrEntry->SizeOfImage;
			return TRUE;
		}
	}

	return FALSE;
}

BOOLEAN KernelBase_QueryKernelModuleSizeLDR(IN ULONG_PTR SystemKernelModuleBase, OUT PSIZE_T SystemKernelModuleSize)
{	
	PLIST_ENTRY lpEntry = (PLIST_ENTRY)g_GlobalData.pDriverObject->DriverSection;
	PLIST_ENTRY lpOrigin = lpEntry;
	if (!lpEntry)
	{
		return FALSE;
	}
	
	if (!SystemKernelModuleBase || !SystemKernelModuleSize)
	{
		return FALSE;
	}

	lpEntry = lpEntry->Flink;
	while (lpEntry && lpEntry != lpOrigin) 
	{
		PLDR_DATA_TABLE_ENTRY pLdrEntry = CONTAINING_RECORD(lpEntry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
		if (SystemKernelModuleBase == (ULONG_PTR)pLdrEntry->DllBase)
		{
			*SystemKernelModuleSize = pLdrEntry->SizeOfImage;
			return TRUE;
		}
	}

	return FALSE;
}

BOOLEAN KernelBase_GetNtoskrnlInfo(OUT PUNICODE_STRING UnKernelName, OUT PULONG_PTR SystemKernelModuleBase, OUT PSIZE_T SystemKernelModuleSize)
{
    ULONG ulSize = 0;
    PRTL_PROCESS_MODULES pModuleList = NULL;
    CHAR* szKernelName = NULL;
    ANSI_STRING AnsiKernelName = { 0 };
    BOOLEAN bRet = TRUE;

    if (!UnKernelName)
    {
        return FALSE;
    }

    if (ZwQuerySystemInformation(SystemModuleInformation, NULL, 0, &ulSize) != STATUS_INFO_LENGTH_MISMATCH)
    {
        return FALSE;
    }

    pModuleList = (PRTL_PROCESS_MODULES)MemoryAllocator_ZeroedAlloc(PagedPool, ulSize);
    if (pModuleList)
    {
        if (!NT_SUCCESS(ZwQuerySystemInformation(SystemModuleInformation, pModuleList, ulSize, &ulSize)))
        {
            MemoryAllocator_Free(pModuleList);
            LOG_ERROR(L"ZwQuerySystemInformation error");
            return FALSE;
        }
    }

    szKernelName = (CHAR*)(pModuleList->Module[0].OffsetToFileName + pModuleList->Module[0].Name);
    Utility_InitAnsiString(&AnsiKernelName, szKernelName);
    RtlAnsiStringToUnicodeString(UnKernelName, &AnsiKernelName, TRUE);

    *SystemKernelModuleBase = (ULONG_PTR)pModuleList->Module[0].ImageBase;
    *SystemKernelModuleSize = (ULONG_PTR)pModuleList->Module[0].ImageSize;

    MemoryAllocator_Free(pModuleList);
    return TRUE;
}

NTSTATUS KernelBase_CheckKernelUpdate()
{
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	WCHAR szSystem32[] = {'\\','S','y','s','t','e','m','R','o','o','t','\\','s','y','s','t','e','m','3','2','\\','\0'};
	LPWSTR wszNtoskrnlPath = (LPWSTR)MemoryAllocator_ZeroedAlloc(PagedPool, MAX_PATH * sizeof(WCHAR));

	if (!wszNtoskrnlPath)
	{
		return STATUS_INSUFFICIENT_RESOURCES;
	}
	
	LibC_wcscat(wszNtoskrnlPath, szSystem32);
	LibC_memcpy(wszNtoskrnlPath + LibC_wcslen(szSystem32), g_GlobalData.NtosKrnlName.Buffer, g_GlobalData.NtosKrnlName.Length);

	LOG_IMPORTANT(L"Ntoskrnl Path: %ws\n", wszNtoskrnlPath);

	status = MapSectionAndCheckSum(wszNtoskrnlPath, (ULONG_PTR)g_GlobalData.NtKernelBase);
	if (!NT_SUCCESS(status))
	{
		MemoryAllocator_Free(wszNtoskrnlPath);
		return status;
	}

	MemoryAllocator_Free(wszNtoskrnlPath);
	return STATUS_SUCCESS;
}
