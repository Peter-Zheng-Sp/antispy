#include "Stdafx.h"
#include "SystemOffset.h"
#include "GlobalData.h"
#include "SystemVersion.h"

ULONG SystemOffset_KTHREAD_PreviousMode()
{
    if (OS_IS_WIN7_LOWER(g_GlobalData.SystemVersion))
    {
        return 0x153;
    }
    else if (OS_IS_WIN7(g_GlobalData.SystemVersion))
    {
        return 0x1f6;
    }
    else
    {
        return 0x232;
    }

    // throw error
    NT_ASSERT(FALSE);
    return 0;
}

ULONG SystemOffset_KTHREAD_Win32Thread()
{
    if (OS_IS_WIN7_LOWER(g_GlobalData.SystemVersion))
    {
        return 0x248;
    }
    else if (OS_IS_WIN7(g_GlobalData.SystemVersion))
    {
        return 0x270;
    }
    else
    {
        return 0x1c8;
    }

    // throw error
    NT_ASSERT(FALSE);
    return 0;
}

ULONG SystemOffset_KTHREAD_ApcStateIndex()
{
    if (OS_IS_WIN7_LOWER(g_GlobalData.SystemVersion))
    {
        return 0x1e0;
    }
    else if (OS_IS_WIN7(g_GlobalData.SystemVersion))
    {
        return 0x1f0;
    }
    else
    {
        return 0x24a;
    }

    // throw error
    NT_ASSERT(FALSE);
    return 0;
}

ULONG SystemOffset_KTHREAD_Process()
{
    if (OS_IS_WIN7_LOWER(g_GlobalData.SystemVersion))
    {
        return 0x1f8;
    }
    else if (OS_IS_WIN7(g_GlobalData.SystemVersion))
    {
        return 0x210;
    }
    else
    {
        return 0x220;
    }

    // throw error
    NT_ASSERT(FALSE);
    return 0;
}

ULONG SystemOffset_EPROCESS_ImageFileName()
{
    if (OS_IS_WIN7_LOWER(g_GlobalData.SystemVersion))
    {
        return 0x238;
    }
    else if (OS_IS_WIN10_LOWER(g_GlobalData.SystemVersion))
    {
        return 0x438;
    }
    else if (WINDOWS_10_TH1 == g_GlobalData.SystemVersion)
    {
        return 0x448;
    }
    else if (g_GlobalData.SystemVersion < WINDOWS_10_20H1)
    {
        return 0x450;
    }
    else
    {
        return 0x5a8;
    }

    // throw error
    NT_ASSERT(FALSE);
    return 0;
}

ULONG SystemOffset_EPROCESS_SeAuditProcessCreationInfo()
{
    if (OS_IS_VISTA_LOWER(g_GlobalData.SystemVersion))
    {
        return 0x318;
    }
    else if (OS_IS_VISTA(g_GlobalData.SystemVersion))
    {
        return 0x2e8;
    }
    else if (OS_IS_WIN7(g_GlobalData.SystemVersion))
    {
        return 0x390;
    }
    else if (OS_IS_WIN10_LOWER(g_GlobalData.SystemVersion))
    {
        return 0x450;
    }
    else if (WINDOWS_10_TH1 == g_GlobalData.SystemVersion)
    {
        return 0x460;
    }
    else if (g_GlobalData.SystemVersion < WINDOWS_10_20H1)
    {
        return 0x468;
    }
    else
    {
        return 0x5c0;
    }

    // throw error
    NT_ASSERT(FALSE);
    return 0;
}

ULONG SystemOffset_EPROCESS_ActiveProcessLinks()
{
    if (OS_IS_VISTA_LOWER(g_GlobalData.SystemVersion))
    {
        return 0xe0;
    }
    else if (OS_IS_VISTA(g_GlobalData.SystemVersion))
    {
        return 0xe8;
    }
    else if (OS_IS_WIN7(g_GlobalData.SystemVersion))
    {
        return 0x188;
    }
    else if (OS_IS_WIN8(g_GlobalData.SystemVersion))
    {
        return 0x2e8;
    }
    else if (g_GlobalData.SystemVersion < WINDOWS_10_RS2)
    {
        return 0x2f0;
    }
    else if (g_GlobalData.SystemVersion < WINDOWS_10_19H1)
    {
        return 0x2e8;
    }
    else if (g_GlobalData.SystemVersion < WINDOWS_10_20H1)
    {
        return 0x2f0;
    }
    else
    {
        return 0x448;
    }

    // throw error
    NT_ASSERT(FALSE);
    return 0;
}

ULONG SystemOffset_EPROCESS_UniqueProcessId()
{
    if (OS_IS_VISTA_LOWER(g_GlobalData.SystemVersion))
    {
        return 0xd8;
    }
    else if (OS_IS_VISTA(g_GlobalData.SystemVersion))
    {
        return 0xe0;
    }
    else if (OS_IS_WIN7(g_GlobalData.SystemVersion))
    {
        return 0x180;
    }
    else if (OS_IS_WIN8(g_GlobalData.SystemVersion))
    {
        return 0x2e0;
    }
    else if (g_GlobalData.SystemVersion < WINDOWS_10_RS2)
    {
        return 0x2e8;
    }
    else if (g_GlobalData.SystemVersion < WINDOWS_10_19H1)
    {
        return 0x2e0;
    }
    else if (g_GlobalData.SystemVersion < WINDOWS_10_20H1)
    {
        return 0x2e8;
    }
    else
    {
        return 0x440;
    }

    // throw error
    NT_ASSERT(FALSE);
    return 0;
}

ULONG SystemOffset_EPROCESS_InheritedFromUniqueProcessId()
{
    if (OS_IS_VISTA_LOWER(g_GlobalData.SystemVersion))
    {
        return 0x218;
    }
    else if (OS_IS_VISTA(g_GlobalData.SystemVersion))
    {
        return 0x1f0;
    }
    else if (OS_IS_WIN7(g_GlobalData.SystemVersion))
    {
        return 0x290;
    }
    else if (OS_IS_WIN8(g_GlobalData.SystemVersion))
    {
        return 0x3d0;
    }
    else if (g_GlobalData.SystemVersion < WINDOWS_10_19H1)
    {
        return 0x3e0;
    }
    else if (g_GlobalData.SystemVersion < WINDOWS_10_20H1)
    {
        return 0x3e8;
    }
    else
    {
        return 0x540;
    }

    // throw error
    NT_ASSERT(FALSE);
    return 0;
}

ULONG SystemOffset_EPROCESS_CreateTime()
{
    if (OS_IS_VISTA_LOWER(g_GlobalData.SystemVersion))
    {
        return 0xc0;
    }
    else if (OS_IS_VISTA(g_GlobalData.SystemVersion))
    {
        return 0xc8;
    }
    else if (OS_IS_WIN7(g_GlobalData.SystemVersion))
    {
        return 0x168;
    }
    else if (OS_IS_WIN8(g_GlobalData.SystemVersion))
    {
        return 0x2d0;
    }
    else if (g_GlobalData.SystemVersion < WINDOWS_10_20H1)
    {
        return 0x310;
    }
    else
    {
        return 0x468;
    }

    // throw error
    NT_ASSERT(FALSE);
    return 0;
}
