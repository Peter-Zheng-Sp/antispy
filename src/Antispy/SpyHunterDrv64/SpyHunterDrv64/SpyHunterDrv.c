/*
 * Copyright (c) [2010-2025] peterzhengsp1997@gmail.com rights reserved.
 *
 * AntiSpy is licensed under the Mulan PSL v1.
 * You can use this software according to the terms and conditions of the Mulan PSL v1.
 * You may obtain a copy of Mulan PSL v1 at:
 *
 *     http://license.coscl.org.cn/MulanPSL
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
 * FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v1 for more details.
*/
#include "Stdafx.h"
#include "Logger.h"
#include "GlobalData.h"
#include "KernelBase.h"
#include "VariableHub.h"

extern PULONG InitSafeBootMode;

VOID
DriverUnload(
    IN PDRIVER_OBJECT	DriverObject
)
{
    LOG_IMPORTANT(L"Enter DriverUnload");

    GlobalData_DeInit();

    LOG_IMPORTANT(L"Leave DriverUnload");
}

NTSTATUS
DriverEntry(
    IN OUT PDRIVER_OBJECT   DriverObject,
    IN PUNICODE_STRING      RegistryPath
)
{
    NTSTATUS status = STATUS_UNSUCCESSFUL;

    LOG_IMPORTANT(L"Enter DriverEntry");
    DriverObject->DriverUnload = DriverUnload;

    if (!*InitSafeBootMode)
    { 
        return STATUS_NOT_SUPPORTED;
    }

    status = GlobalData_Init(DriverObject, RegistryPath);
    if (!NT_SUCCESS(status))
    {
        LOG_FATAL(L"GlobalData_Init failed, status=0x%X", status);
        return STATUS_UNSUCCESSFUL;
    }

    // 如果检测ntoskrnl的checksum失败，那么就返回一个特定的错误码
    status = KernelBase_CheckKernelUpdate();
    if (!NT_SUCCESS(status))
    {
        GlobalData_DeInit();
        LOG_FATAL(L"CheckUpdate failed, status=0x%X", status);
        return STATUS_INVALID_DISPOSITION;
    }

    status = VariableHub_Init();
    if (!NT_SUCCESS(status))
    {
        GlobalData_DeInit();
        LOG_FATAL(L"VariableHub_Init failed, status=0x%X", status);
        return STATUS_INVALID_DISPOSITION;
    }

    LOG_IMPORTANT(L"Leave DriverEntry");
    return STATUS_SUCCESS;
}
