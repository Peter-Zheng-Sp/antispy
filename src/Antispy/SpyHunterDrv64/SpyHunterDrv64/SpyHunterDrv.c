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

    status = GlobalData_Init(DriverObject, RegistryPath);
    if (!NT_SUCCESS(status))
    {
        LOG_FATAL(L"init global data failed, status=0x%X", status);
        return STATUS_UNSUCCESSFUL;
    }

    LOG_IMPORTANT(L"Leave DriverEntry, status=0x%X", );
    return status;
}
