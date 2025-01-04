#ifndef _H_SYSTEMOFFSET_
#define _H_SYSTEMOFFSET_

#include <ntifs.h>

ULONG SystemOffset_KTHREAD_PreviousMode();

ULONG SystemOffset_KTHREAD_Win32Thread();

ULONG SystemOffset_KTHREAD_ApcStateIndex();

ULONG SystemOffset_KTHREAD_Process();

ULONG SystemOffset_EPROCESS_ImageFileName();

ULONG SystemOffset_EPROCESS_SeAuditProcessCreationInfo();

ULONG SystemOffset_EPROCESS_ActiveProcessLinks();

ULONG SystemOffset_EPROCESS_UniqueProcessId();

ULONG SystemOffset_EPROCESS_InheritedFromUniqueProcessId();

ULONG SystemOffset_EPROCESS_CreateTime();

#endif // _H_SYSTEMOFFSET_
