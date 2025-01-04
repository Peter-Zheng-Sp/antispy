#ifndef _H_GLOBALDATA_
#define _H_GLOBALDATA_

#include "SystemVersion.h"
#include "ApiDefine.h"

typedef struct _GLOBAL_DATA
{
	NTOS_VERSION SystemVersion;
	PVOID NtKernelBase;
	SIZE_T NtKernelSize;
	PDRIVER_OBJECT pDriverObject;
	PUNICODE_STRING pRegPath;
	UNICODE_STRING NtosKrnlName;
	typedef_MmGetSystemRoutineAddress MmGetSystemRoutineAddress;
} GLOBAL_DATA, *PGLOBAL_DATA;

extern GLOBAL_DATA g_GlobalData;

NTSTATUS GlobalData_Init(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath);

void GlobalData_DeInit();

#endif // _H_GLOBALDATA_
