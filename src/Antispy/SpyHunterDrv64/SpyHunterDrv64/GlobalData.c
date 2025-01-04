#include "Stdafx.h"
#include "Logger.h"
#include "Utility.h"
#include "GlobalData.h"
#include "SystemVersion.h"
#include "KernelBase.h"

GLOBAL_DATA g_GlobalData;

static NTSTATUS InitVersion()
{
    NTSTATUS status = STATUS_UNSUCCESSFUL;
    UNICODE_STRING ustrAPI = { 0 };
    OSVERSIONINFOEXW WindowsVersionInfo = { 0 };
    BOOLEAN bRet = FALSE;

    WindowsVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
    status = RtlGetVersion((PRTL_OSVERSIONINFOW)&WindowsVersionInfo);
    if (!NT_SUCCESS(status))
    {
        bRet = PsGetVersion(&WindowsVersionInfo.dwMajorVersion,
            &WindowsVersionInfo.dwMinorVersion, &WindowsVersionInfo.dwBuildNumber, NULL);
        WindowsVersionInfo.wServicePackMajor = 0;
        WindowsVersionInfo.wServicePackMinor = 0;
        if (bRet)
        {
            status = STATUS_SUCCESS;
        }
    }

    if (NT_SUCCESS(status))
    {
        g_GlobalData.SystemVersion = SystemVersion_ParseOsInfo2InternalVersion(WindowsVersionInfo);
        if (!OS_IS_SUPPORTED(g_GlobalData.SystemVersion))
        {
            status = STATUS_NOT_SUPPORTED;
        }
    }

    return status;
}

NTSTATUS GlobalData_Init(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
    NTSTATUS status = STATUS_SUCCESS;
    UNICODE_STRING ustrAPI = { 0 };
    ULONG_PTR KernelBase = 0;
    SIZE_T KernelSize = 0;

    if (!DriverObject || !RegistryPath)
    {
        LOG_ERROR(L"DriverObject=0x%llX, RegistryPath=0x%llX, Value Invalid", DriverObject, RegistryPath);
        return STATUS_INTERNAL_ERROR;
    }

    LOG_IMPORTANT(L"DriverObject=0x%llX, RegistryPath=%wZ", DriverObject, RegistryPath);

    g_GlobalData.pDriverObject = DriverObject;
    g_GlobalData.pRegPath = RegistryPath;

    status = InitVersion();
    if (!NT_SUCCESS(status))
    {
        LOG_ERROR(L"Initialize System Version Failed, status=0x%X", status);
        return STATUS_UNSUCCESSFUL;
    }

    if (!OS_IS_SUPPORTED(g_GlobalData.SystemVersion))
    {
        LOG_ERROR(L"Unsupported System Version");
        return STATUS_NOT_SUPPORTED;
    }

    Utility_InitUnicodeString(&ustrAPI, VCRYPTW(L"MmGetSystemRoutineAddress"));
    g_GlobalData.MmGetSystemRoutineAddress = (typedef_MmGetSystemRoutineAddress)MmGetSystemRoutineAddress(&ustrAPI);
    if (!g_GlobalData.MmGetSystemRoutineAddress)
    {
        LOG_ERROR(L"Get MmGetSystemRoutineAddress Failed");
        return STATUS_NOT_SUPPORTED;
    }

    if (!KernelBase_GetNtoskrnlInfo(&g_GlobalData.NtosKrnlName, &KernelBase, &KernelSize))
    {
        LOG_ERROR(L"GetNtoskrnlInfo Failed");
        return STATUS_UNSUCCESSFUL;
    }

    Utility_InitUnicodeString(&ustrAPI, VCRYPTW(L"ExRaiseStatus"));
    g_GlobalData.NtKernelBase = Utility_GetPEHeaderViaMemoryAddress(
        VCRYPT("ntoskrnl.exe"), g_GlobalData.MmGetSystemRoutineAddress(&ustrAPI));

    LOG_IMPORTANT(L"NtKernel name=%wZ base=0x%llX, size=0x%llX", &g_GlobalData.NtosKrnlName,
        g_GlobalData.NtKernelBase, g_GlobalData.NtKernelSize);

    if (!g_GlobalData.NtKernelBase ||
        !Utility_IsAddressInKernel((ULONG_PTR)g_GlobalData.NtKernelBase) ||
        !Utility_CheckKernelAddressValid(g_GlobalData.NtKernelBase))
    {
        Utility_FreeUnicodeString(&g_GlobalData.NtosKrnlName);
        LOG_ERROR(L"NtKernel Info Check Failed");
        return STATUS_INTERNAL_ERROR;
    }

    if (!KernelBase_QueryKernelModuleSizeLDR((ULONG_PTR)g_GlobalData.NtKernelBase, &g_GlobalData.NtKernelSize) ||
        !g_GlobalData.NtKernelSize)
    {
        Utility_FreeUnicodeString(&g_GlobalData.NtosKrnlName);
        LOG_ERROR(L"QueryKernelModuleSizeLDR Failed");
        return STATUS_UNSUCCESSFUL;
    }

    return STATUS_SUCCESS;
}

void GlobalData_DeInit()
{
    Utility_FreeUnicodeString(&g_GlobalData.NtosKrnlName);
}
