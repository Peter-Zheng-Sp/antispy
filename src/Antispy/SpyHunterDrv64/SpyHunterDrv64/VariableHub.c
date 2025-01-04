#include "Stdafx.h"
#include "VariableHub.h"
#include "SystemOffset.h"
#include "Logger.h"
#include "SSDT.h"

static ULONG_PTR gVariableHubArray[enumVarHubId_End] = { 0 };

static VOID InitOffset()
{
    gVariableHubArray[enumVarHubId_Offset_KTHREAD_PreviousMode] = SystemOffset_KTHREAD_PreviousMode();
    gVariableHubArray[enumVarHubId_Offset_KTHREAD_Win32Thread] = SystemOffset_KTHREAD_Win32Thread();
    gVariableHubArray[enumVarHubId_Offset_KTHREAD_ApcStateIndex] = SystemOffset_KTHREAD_ApcStateIndex();
    gVariableHubArray[enumVarHubId_Offset_KTHREAD_Process] = SystemOffset_KTHREAD_Process();
    gVariableHubArray[enumVarHubId_Offset_EPROCESS_ImageFileName] = SystemOffset_EPROCESS_ImageFileName();
    gVariableHubArray[enumVarHubId_Offset_EPROCESS_SeAuditProcessCreationInfo] = SystemOffset_EPROCESS_SeAuditProcessCreationInfo();
    gVariableHubArray[enumVarHubId_Offset_EPROCESS_ActiveProcessLinks] = SystemOffset_EPROCESS_ActiveProcessLinks();
    gVariableHubArray[enumVarHubId_Offset_EPROCESS_UniqueProcessId] = SystemOffset_EPROCESS_UniqueProcessId();
    gVariableHubArray[enumVarHubId_Offset_EPROCESS_InheritedFromUniqueProcessId] = SystemOffset_EPROCESS_InheritedFromUniqueProcessId();
    gVariableHubArray[enumVarHubId_Offset_EPROCESS_CreateTime] = SystemOffset_EPROCESS_CreateTime();
}

static NTSTATUS InitExportedAPI()
{ 
    return STATUS_SUCCESS;
}

static NTSTATUS InitSSDTAPI()
{
    return STATUS_SUCCESS;
}

NTSTATUS VariableHub_Init()
{
    NTSTATUS status = STATUS_SUCCESS;

    InitOffset();

    status = InitExportedAPI();
    if (!NT_SUCCESS(status))
    {
        LOG_ERROR(L"InitExportedAPI Failed, status=0x%X", status);
        return status;
    }

    status = InitSSDTAPI();
    if (!NT_SUCCESS(status))
    {
        LOG_ERROR(L"InitSSDTAPI Failed, status=0x%X", status);
        return status;
    }

    return STATUS_SUCCESS;
}

ULONG_PTR VariableHub_GetById(ULONG Id)
{
    return NULL;
}
