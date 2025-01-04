#ifndef _H_APIDEF_
#define _H_APIDEF_

#include "SystemDefine.h"

// clang-format off

typedef POBJECT_TYPE *typedef_IoDeviceObjectType;
typedef POBJECT_TYPE *typedef_IoDriverObjectType;
typedef POBJECT_TYPE *typedef_MmSectionObjectType;
typedef POBJECT_TYPE *typedef_IoFileObjectType;
typedef PULONG typedef_InitSafeBootMode;
typedef PUCHAR typedef_KeNumberProcessors;
typedef POBJECT_TYPE *typedef_PsProcessType;
typedef POBJECT_TYPE *typedef_PsThreadType;
typedef ULONG(NTAPI *typedef_KeQueryMaximumProcessorCount)(VOID);
typedef KAFFINITY(NTAPI *typedef_KeQueryActiveProcessors)(VOID);

typedef WCHAR(NTAPI *typedef_RtlUpcaseUnicodeChar)(IN WCHAR SourceCharacter);

typedef BOOLEAN(NTAPI *typedef_RtlEqualUnicodeString)(IN CONST UNICODE_STRING *String1,
													  IN CONST UNICODE_STRING *String2, IN BOOLEAN CaseInSensitive);

typedef VOID(FASTCALL *typedef_ExfUnblockPushLock)(IN OUT PEX_PUSH_LOCK PushLock,
												   IN OUT OPTIONAL PEX_PUSH_LOCK_WAIT_BLOCK WaitBlock);

typedef VOID(FASTCALL *typedef_ExBlockPushLock)(IN OUT PEX_PUSH_LOCK PushLock,
												IN OUT OPTIONAL PEX_PUSH_LOCK_WAIT_BLOCK WaitBlock);

typedef NTSTATUS(NTAPI *typedef_ObCloseHandle)(IN HANDLE Handle,
											   IN KPROCESSOR_MODE PreviousMode);

typedef PHANDLE_TABLE_ENTRY(NTAPI *typedef_ExpLookupHandleTableEntry) (
	IN PHANDLE_TABLE HandleTable,
	IN HANDLE Handle
	);

typedef BOOLEAN (NTAPI *PEX_ENUM_HANDLE_CALLBACK_61)(
	IN OUT PHANDLE_TABLE_ENTRY HandleTableEntry,
	IN HANDLE Handle,
	IN PVOID Context
	);

// since WIN8
typedef BOOLEAN (NTAPI *PEX_ENUM_HANDLE_CALLBACK)(
	IN PHANDLE_TABLE HandleTable,
	IN OUT PHANDLE_TABLE_ENTRY HandleTableEntry,
	IN HANDLE Handle,
	IN PVOID Context
	);

typedef BOOLEAN (NTAPI *typedef_ExEnumHandleTable)(
	IN PHANDLE_TABLE HandleTable,
	IN PVOID/*PEX_ENUM_HANDLE_CALLBACK(61)*/ EnumHandleProcedure,
	IN OUT PVOID Context,
	OUT OPTIONAL PHANDLE Handle
	);

typedef ULONG(NTAPI *typedef_KeGetCurrentProcessorNumberEx)(OUT OPTIONAL PPROCESSOR_NUMBER ProcNumber);

typedef VOID(NTAPI *typedef_KeInitializeDpc)(IN PRKDPC Dpc, IN PKDEFERRED_ROUTINE DeferredRoutine,
											 IN PVOID DeferredContext);

typedef VOID(NTAPI *typedef_KeSetImportanceDpc)(IN PRKDPC Dpc, IN KDPC_IMPORTANCE Importance);

typedef VOID(NTAPI *typedef_KeSetTargetProcessorDpc)(IN PRKDPC Dpc, IN CCHAR Number);

typedef BOOLEAN(NTAPI *typedef_KeInsertQueueDpc)(IN PRKDPC Dpc, IN PVOID SystemArgument1, IN PVOID SystemArgument2);

typedef VOID(NTAPI *typedef_KeInitializeThreadedDpc)(IN PKDPC Dpc, IN PKDEFERRED_ROUTINE DeferredRoutine,
													 IN PVOID DeferredContext);

typedef KIRQL(NTAPI *typedef_KeRaiseIrqlToDpcLevel)(VOID);

typedef VOID(NTAPI *typedef_KeLowerIrql)(IN KIRQL NewIrql);

typedef PVOID(NTAPI *typedef_PsGetProcessDebugPort)(IN PEPROCESS Process);

typedef NTSTATUS(NTAPI *typedef_IoCreateSymbolicLink)(IN PUNICODE_STRING SymbolicLinkName,
													  IN PUNICODE_STRING DeviceName);

typedef NTSTATUS(NTAPI *typedef_IoDeleteSymbolicLink)(IN PUNICODE_STRING SymbolicLinkName);

typedef KIRQL (NTAPI* typedef_KeGetCurrentIrql)(VOID);

typedef NTSTATUS(NTAPI* typedef_PsAcquireProcessExitSynchronization)(IN PEPROCESS Process);

typedef NTSTATUS(NTAPI* typedef_PsReleaseProcessExitSynchronization)(IN PEPROCESS Process);

typedef PUCHAR(NTAPI *typedef_PsGetProcessImageFileName)(IN PEPROCESS Process);

typedef BOOLEAN(NTAPI *typedef_MmIsAddressValid)(IN PVOID VirtualAddress);

typedef POBJECT_TYPE(NTAPI* typedef_ObGetObjectType)(IN PVOID Object);

typedef HANDLE(NTAPI *typedef_PsGetThreadProcessId)(PETHREAD Thread);

typedef VOID(NTAPI *typedef_ProbeForRead)(IN CONST VOID *Address, IN SIZE_T Length, IN ULONG Alignment);

typedef VOID(NTAPI *typedef_ProbeForWrite)(IN CONST VOID *Address, IN SIZE_T Length, IN ULONG Alignment);

typedef NTSTATUS(NTAPI *typedef_IoQueryFileDosDeviceName)(IN PFILE_OBJECT FileObject,
														  OUT POBJECT_NAME_INFORMATION *ObjectNameInformation);

typedef NTSTATUS(NTAPI *typedef_KeGetProcessorNumberFromIndex)(IN ULONG ProcIndex,
															   OUT PPROCESSOR_NUMBER ProcNumber);

typedef VOID(NTAPI *typedef_KeSetSystemGroupAffinityThread)(IN PGROUP_AFFINITY Affinity,
															OUT OPTIONAL PGROUP_AFFINITY PreviousAffinity);

typedef VOID(NTAPI *typedef_KeRevertToUserGroupAffinityThread)(IN PGROUP_AFFINITY PreviousAffinity);

typedef NTSTATUS(NTAPI *typedef_ZwQuerySystemInformation)(SYSTEM_INFORMATION_CLASS SystemInformationClass,
														  PVOID SystemInformation, ULONG SystemInformationLength,
														  PULONG ReturnLength);

typedef NTSTATUS(NTAPI *typedef_NtQuerySystemInformation)(SYSTEM_INFORMATION_CLASS SystemInformationClass,
														  PVOID SystemInformation, ULONG SystemInformationLength,
														  PULONG ReturnLength);

typedef NTSTATUS(NTAPI *typedef_ObOpenObjectByName)(POBJECT_ATTRIBUTES ObjectAttributes, POBJECT_TYPE ObjectType,
													KPROCESSOR_MODE ProbeMode, ULONG HandleAttributes, HANDLE *Object,
													PACCESS_STATE AccessState);

typedef NTSTATUS(NTAPI *typedef_ZwCreateFile)(PHANDLE FileHandle, ACCESS_MASK DesiredAccess,
											  POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock,
											  PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess,
											  ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer,
											  ULONG EaLength);

typedef NTSTATUS(NTAPI *typedef_NtCreateFile)(PHANDLE FileHandle, ACCESS_MASK DesiredAccess,
											  POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock,
											  PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess,
											  ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer,
											  ULONG EaLength);

typedef NTSTATUS(NTAPI *typedef_ZwDeviceIoControlFile)(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine,
													   PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock,
													   ULONG IoControlCode, PVOID InputBuffer, ULONG InputBufferLength,
													   PVOID OutputBuffer, ULONG OutputBufferLength);

typedef NTSTATUS(NTAPI *typedef_NtDeviceIoControlFile)(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine,
													   PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock,
													   ULONG IoControlCode, PVOID InputBuffer, ULONG InputBufferLength,
													   PVOID OutputBuffer, ULONG OutputBufferLength);

typedef NTSTATUS(NTAPI *typedef_NtOpenDirectoryObject)(OUT PHANDLE DirectoryHandle, IN ACCESS_MASK DesiredAccess,
													   IN POBJECT_ATTRIBUTES ObjectAttributes);

typedef NTSTATUS(NTAPI *typedef_NtQueryDirectoryObject)(IN HANDLE DirectoryHandle, OUT OPTIONAL PVOID Buffer,
														IN ULONG Length, IN BOOLEAN ReturnSingleEntry,
														IN BOOLEAN RestartScan, IN OUT PULONG Context,
														OUT OPTIONAL PULONG ReturnLength);

typedef NTSTATUS(NTAPI *typedef_ObReferenceObjectByName)(IN PUNICODE_STRING ObjectPath, IN ULONG Attributes,
														 IN PACCESS_STATE PassedAccessState,
														 IN ACCESS_MASK DesiredAccess, IN POBJECT_TYPE ObjectType,
														 IN KPROCESSOR_MODE AccessMode, IN OUT PVOID ParseContext,
														 OUT PVOID *ObjectPtr);

typedef NTSTATUS(NTAPI *typedef_NtRequestPort)(IN HANDLE PortHandle, IN PPORT_MESSAGE LpcMessage);

typedef NTSTATUS(NTAPI *typedef_NtConnectPort)(
	OUT PHANDLE PortHandle, IN PUNICODE_STRING PortName, IN PSECURITY_QUALITY_OF_SERVICE SecurityQos,
	IN OPTIONAL PPORT_VIEW ClientView, IN OPTIONAL PREMOTE_PORT_VIEW ServerView, IN OPTIONAL PULONG MaxMessageLength,
	IN OPTIONAL PVOID ConnectionInformation, IN OPTIONAL PULONG ConnectionInformationLength);

typedef NTSTATUS(NTAPI *typedef_NtRequestWaitReplyPort)(IN HANDLE PortHandle, IN PPORT_MESSAGE Request,
														OUT PPORT_MESSAGE IncomingReply);

typedef NTSTATUS(NTAPI *typedef_ZwOpenFile)(PHANDLE FileHandle, ACCESS_MASK DesiredAccess,
											POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock,
											ULONG ShareAccess, ULONG OpenOptions);

typedef NTSTATUS(NTAPI *typedef_ZwCreateSection)(PHANDLE SectionHandle, ACCESS_MASK DesiredAccess,
												 POBJECT_ATTRIBUTES ObjectAttributes, PLARGE_INTEGER MaximumSize,
												 ULONG SectionPageProtection, ULONG AllocationAttributes,
												 HANDLE FileHandle);

typedef NTSTATUS(NTAPI *typedef_NtCreateSection)(PHANDLE SectionHandle, ACCESS_MASK DesiredAccess,
												 POBJECT_ATTRIBUTES ObjectAttributes, PLARGE_INTEGER MaximumSize,
												 ULONG SectionPageProtection, ULONG AllocationAttributes,
												 HANDLE FileHandle);

typedef NTSTATUS(NTAPI *typedef_ZwMapViewOfSection)(HANDLE SectionHandle, HANDLE ProcessHandle, PVOID *BaseAddress,
													ULONG_PTR ZeroBits, SIZE_T CommitSize, PLARGE_INTEGER SectionOffset,
													PSIZE_T ViewSize, SECTION_INHERIT InheritDisposition,
													ULONG AllocationType, ULONG Win32Protect);

typedef NTSTATUS(NTAPI *typedef_ZwClose)(HANDLE Handle);

typedef PVOID (*typedef_ExAllocatePoolWithTag)(IN POOL_TYPE PoolType, IN SIZE_T NumberOfBytes, IN ULONG Tag);

typedef VOID (*typedef_ExFreePoolWithTag)(IN PVOID P, IN ULONG Tag);

typedef VOID(NTAPI *typedef_RtlInitUnicodeString)(IN OUT PUNICODE_STRING DestinationString, IN PCWSTR SourceString);

typedef NTSTATUS(NTAPI *typedef_ZwQueryValueKey)(IN HANDLE KeyHandle, IN PUNICODE_STRING ValueName,
												 IN KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
												 OUT PVOID KeyValueInformation, IN ULONG Length,
												 OUT PULONG ResultLength);

typedef NTSTATUS(NTAPI *typedef_ZwOpenKey)(OUT PHANDLE KeyHandle, IN ACCESS_MASK DesiredAccess,
										   IN POBJECT_ATTRIBUTES ObjectAttributes);

typedef NTSTATUS(NTAPI *typedef_ZwQuerySystemInformation)(SYSTEM_INFORMATION_CLASS SystemInformationClass,
														  PVOID SystemInformation, ULONG SystemInformationLength,
														  PULONG ReturnLength);

typedef NTSTATUS(NTAPI *typedef_ZwSetSystemInformation)(IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
														IN PVOID SystemInformation, IN ULONG SystemInformationLength);

typedef NTSTATUS(NTAPI *typedef_RtlGetVersion)(OUT PRTL_OSVERSIONINFOW lpVersionInformation);

typedef BOOLEAN (*typedef_PsGetVersion)(OUT OPTIONAL PULONG MajorVersion, OUT OPTIONAL PULONG MinorVersion,
										OUT OPTIONAL PULONG BuildNumber, OUT OPTIONAL PUNICODE_STRING CSDVersion);

typedef LARGE_INTEGER (*typedef_KeQueryPerformanceCounter)(OUT OPTIONAL PLARGE_INTEGER PerformanceFrequency);

typedef PVOID (*typedef_ExEnterCriticalRegionAndAcquireResourceExclusive)(IN OUT PERESOURCE Resource);

typedef VOID(FASTCALL *typedef_ExReleaseResourceAndLeaveCriticalRegion)(IN OUT PERESOURCE Resource);

typedef PVOID(NTAPI *typedef_MmGetSystemRoutineAddress)(IN PUNICODE_STRING SystemRoutineName);

typedef HANDLE (NTAPI *typedef_PsGetCurrentProcessId)(VOID);

typedef PEPROCESS (NTAPI *typedef_IoGetCurrentProcess)(VOID);

typedef VOID (NTAPI *typedef_KeGenericCallDpc)(IN PKDEFERRED_ROUTINE Routine, IN PVOID Context);

typedef VOID (NTAPI *typedef_KeSignalCallDpcDone)(IN PVOID SystemArgument1);

typedef BOOLEAN (NTAPI *typedef_KeSignalCallDpcSynchronize)(IN PVOID SystemArgument2);

typedef NTSTATUS (NTAPI *typedef_NtYieldExecution)();

typedef ULONG_PTR (NTAPI *typedef_KeIpiGenericCall) (IN PKIPI_BROADCAST_WORKER BroadcastFunction, IN ULONG_PTR Context);

typedef ULONG (NTAPI *typedef_KeQueryActiveProcessorCountEx)(IN USHORT GroupNumber);

typedef NTSTATUS (NTAPI *typedef_ObCreateObject)(IN KPROCESSOR_MODE ProbeMode, IN POBJECT_TYPE ObjectType,
												 IN POBJECT_ATTRIBUTES ObjectAttributes, IN KPROCESSOR_MODE OwnershipMode,
												 IN OUT OPTIONAL PVOID ParseContext, IN ULONG ObjectBodySize,
												 IN ULONG PagedPoolCharge, IN ULONG NonPagedPoolCharge,
												 OUT PVOID *Object);

typedef NTSTATUS (NTAPI *typedef_ObInsertObject)(IN PVOID Object, IN OPTIONAL PACCESS_STATE AccessState,
												 IN OPTIONAL ACCESS_MASK DesiredAccess, IN ULONG ObjectPointerBias,
												 OUT OPTIONAL PVOID *NewObject, OUT OPTIONAL PHANDLE Handle);

typedef NTSTATUS (NTAPI *typedef_IoCreateDevice)(IN PDRIVER_OBJECT DriverObject, IN ULONG DeviceExtensionSize,
												 IN OPTIONAL PUNICODE_STRING DeviceName, IN DEVICE_TYPE DeviceType,
												 IN ULONG DeviceCharacteristics, IN BOOLEAN Exclusive,
												 OUT PDEVICE_OBJECT *DeviceObject);

typedef VOID (NTAPI *typedef_IoDeleteDevice)(IN PDEVICE_OBJECT DeviceObject);

typedef NTSTATUS (NTAPI *typedef_NtSetSecurityObject)(IN HANDLE Handle, IN SECURITY_INFORMATION SecurityInformation,
													  IN PSECURITY_DESCRIPTOR SecurityDescriptor);

typedef NTSTATUS (NTAPI *typedef_ObOpenObjectByPointer)(IN PVOID Object, IN ULONG HandleAttributes,
														IN OPTIONAL PACCESS_STATE PassedAccessState,
														IN ACCESS_MASK DesiredAccess, IN POBJECT_TYPE ObjectType,
														IN KPROCESSOR_MODE AccessMode, OUT PHANDLE Handle);

typedef NTSTATUS (NTAPI *typedef_NtClose)(IN HANDLE Handle);

typedef NTSTATUS (NTAPI *typedef_IoCreateFile)(OUT PHANDLE FileHandle, IN ACCESS_MASK DesiredAccess,
											   IN POBJECT_ATTRIBUTES ObjectAttributes, OUT PIO_STATUS_BLOCK IoStatusBlock,
											   IN PLARGE_INTEGER AllocationSize OPTIONAL, IN ULONG FileAttributes,
											   IN ULONG ShareAccess, IN ULONG Disposition, IN ULONG CreateOptions,
											   IN PVOID EaBuffer OPTIONAL, IN ULONG EaLength,
											   IN CREATE_FILE_TYPE CreateFileType, IN PVOID InternalParameters OPTIONAL,
											   IN ULONG Options);

typedef VOID (NTAPI *typedef_RtlInitAnsiString)(IN OUT PANSI_STRING DestinationString, IN PCSZ SourceString);
typedef NTSTATUS (NTAPI *typedef_RtlAnsiStringToUnicodeString)(IN OUT PUNICODE_STRING DestinationString, IN PANSI_STRING SourceString, IN BOOLEAN AllocateDestinationString);
typedef VOID (NTAPI *typedef_RtlFreeUnicodeString)(IN PUNICODE_STRING UnicodeString);

typedef NTSTATUS (NTAPI *typedef_PsCreateSystemThread)(OUT PHANDLE ThreadHandle, IN ULONG DesiredAccess,
													   IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
													   IN HANDLE ProcessHandle OPTIONAL, OUT PCLIENT_ID ClientId OPTIONAL,
													   IN PKSTART_ROUTINE StartRoutine, IN PVOID StartContext);

typedef NTSTATUS (NTAPI *typedef_PsTerminateSystemThread)(IN NTSTATUS ExitStatus);

typedef NTSTATUS (NTAPI *typedef_KeWaitForSingleObject)(IN PVOID Object, IN KWAIT_REASON WaitReason,
														IN KPROCESSOR_MODE WaitMode, IN BOOLEAN Alertable,
														IN PLARGE_INTEGER Timeout OPTIONAL);

typedef LONG (NTAPI *typedef_KeSetEvent)(IN PRKEVENT Event, IN KPRIORITY Increment, IN BOOLEAN Wait);

typedef VOID (NTAPI *typedef_ObfDereferenceObject)(IN PVOID Object);

typedef NTSTATUS (NTAPI *typedef_ObReferenceObjectByHandle)(IN HANDLE Handle, IN ACCESS_MASK DesiredAccess,
															IN POBJECT_TYPE ObjectType OPTIONAL,
															IN KPROCESSOR_MODE AccessMode, OUT PVOID *Object,
															OUT POBJECT_HANDLE_INFORMATION HandleInformation OPTIONAL);

typedef VOID (NTAPI *typedef_KeInitializeEvent)(IN PRKEVENT Event, IN EVENT_TYPE Type, IN BOOLEAN State);

typedef HANDLE (NTAPI *typedef_PsGetCurrentThreadId)(VOID);

typedef NTSTATUS(NTAPI *typedef_NtCreatePort)(OUT PHANDLE PortHandle, IN POBJECT_ATTRIBUTES ObjectAttributes,
											  IN ULONG MaxConnectInfoLength, IN ULONG MaxDataLength,
											  IN OUT PULONG Reserved OPTIONAL);

typedef NTSTATUS(NTAPI *typedef_NtReplyWaitReceivePort)(IN HANDLE PortHandle, OUT PHANDLE ReceivePortHandle OPTIONAL,
														IN PVOID Reply OPTIONAL, OUT PVOID IncomingRequest);

typedef NTSTATUS(NTAPI *typedef_NtAcceptConnectPort)(OUT PHANDLE ServerPortHandle,
													 IN HANDLE AlternativeReceivePortHandle OPTIONAL,
													 IN PVOID ConnectionReply, IN BOOLEAN AcceptConnection,
													 IN OUT PPORT_VIEW ServerSharedMemory OPTIONAL,
													 OUT PREMOTE_PORT_VIEW ClientSharedMemory OPTIONAL);

typedef NTSTATUS(NTAPI *typedef_NtCompleteConnectPort)(IN HANDLE PortHandle);
typedef NTSTATUS(NTAPI *typedef_NtReplyPort)(IN HANDLE PortHandle, IN PPORT_MESSAGE Reply);

typedef NTSTATUS (NTAPI *typedef_PsLookupProcessByProcessId)(IN HANDLE ProcessId, OUT PEPROCESS *Process);

typedef NTSTATUS(NTAPI *typedef_PsLookupThreadByThreadId)(IN HANDLE ThreadId, OUT PETHREAD *Thread);

typedef NTSTATUS(NTAPI *typedef_MmCopyVirtualMemory)(IN PEPROCESS FromProcess, IN PVOID FromAddress,
													 IN PEPROCESS ToProcess, OUT PVOID ToAddress, IN SIZE_T BufferSize,
													 IN KPROCESSOR_MODE PreviousMode, OUT PSIZE_T NumberOfBytesCopied);

typedef NTSTATUS (NTAPI *typedef_MmUnmapViewOfSection)(IN PEPROCESS Process, IN OPTIONAL PVOID BaseAddress);

typedef NTSTATUS(NTAPI *typedef_MmMapViewOfSection)(IN PVOID SectionToMap, IN PEPROCESS Process,
													IN OUT PVOID *BaseAddress, IN ULONG_PTR ZeroBits,
													IN SIZE_T CommitSize, IN OUT OPTIONAL PLARGE_INTEGER SectionOffset,
													IN OUT PSIZE_T ViewSize, IN SECTION_INHERIT InheritDisposition,
													IN ULONG AllocationType, IN ULONG Win32Protect);

typedef NTSTATUS(NTAPI *typedef_ZwProtectVirtualMemory)(IN HANDLE ProcessHandle, IN OUT PVOID *BaseAddress,
														IN OUT PSIZE_T RegionSize, IN ULONG NewProtect,
														OUT PULONG OldProtect);

typedef NTSTATUS(NTAPI *typedef_NtProtectVirtualMemory)(IN HANDLE ProcessHandle, IN OUT PVOID *BaseAddress,
														IN OUT PSIZE_T RegionSize, IN ULONG NewProtect,
														OUT PULONG OldProtect);

typedef HANDLE (NTAPI *typedef_PsGetProcessId)(IN PEPROCESS Process);

typedef HANDLE (NTAPI *typedef_PsGetProcessInheritedFromUniqueProcessId)(IN PEPROCESS Process);

typedef LONGLONG (NTAPI *typedef_PsGetProcessCreateTimeQuadPart)(IN PEPROCESS Process);

typedef PRKTHREAD (NTAPI *typedef_KeGetCurrentThread)(VOID);

typedef VOID (NTAPI *typedef_KeStackAttachProcess)(IN PKPROCESS Process, OUT PRKAPC_STATE ApcState);

typedef VOID (NTAPI *typedef_KeUnstackDetachProcess)(IN PRKAPC_STATE ApcState);

typedef PVOID (NTAPI *typedef_RtlImageDirectoryEntryToData)(IN PVOID pBaseAddress, IN BOOLEAN bImageLoaded, IN ULONG ulDirectoryEntry,
															IN PULONG pSize);

typedef NTSTATUS (NTAPI *typedef_PsSetLoadImageNotifyRoutine)(IN PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine);

typedef NTSTATUS (NTAPI *typedef_PsRemoveLoadImageNotifyRoutine)(IN PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine);

typedef NTSTATUS(NTAPI *typedef_PsSetCreateProcessNotifyRoutine)(IN PCREATE_PROCESS_NOTIFY_ROUTINE NotifyRoutine,
																 IN BOOLEAN Remove);

typedef NTSTATUS(NTAPI *typedef_PsSetCreateProcessNotifyRoutineEx)(IN PCREATE_PROCESS_NOTIFY_ROUTINE_EX NotifyRoutine,
																   IN BOOLEAN Remove);

typedef NTSTATUS (NTAPI *typedef_PsSetCreateThreadNotifyRoutine)(IN PCREATE_THREAD_NOTIFY_ROUTINE NotifyRoutine);

typedef NTSTATUS (NTAPI *typedef_PsRemoveCreateThreadNotifyRoutine)(IN PCREATE_THREAD_NOTIFY_ROUTINE NotifyRoutine);

typedef NTSTATUS(NTAPI *typedef_NtQueryVirtualMemory)(HANDLE ProcessHandle, PVOID BaseAddress,
													  MEMORY_INFORMATION_CLASS MemoryInformationClass,
													  PVOID MemoryInformation, SIZE_T MemoryInformationLength,
													  PSIZE_T ReturnLength);

typedef NTSTATUS (NTAPI *typedef_ZwQueryInformationProcess)(IN HANDLE ProcessHandle,
															IN PROCESSINFOCLASS ProcessInformationClass,
															OUT PVOID ProcessInformation, IN ULONG ProcessInformationLength,
															OUT PULONG ReturnLength OPTIONAL);

typedef NTSTATUS (NTAPI *typedef_NtQueryInformationProcess)(IN HANDLE ProcessHandle,
															IN PROCESSINFOCLASS ProcessInformationClass,
															OUT PVOID ProcessInformation, IN ULONG ProcessInformationLength,
															OUT PULONG ReturnLength OPTIONAL);

typedef NTSTATUS(NTAPI *typedef_ZwOpenProcess)(OUT PHANDLE ProcessHandle, IN ACCESS_MASK DesiredAccess,
											   IN POBJECT_ATTRIBUTES ObjectAttributes, IN OPTIONAL PCLIENT_ID ClientId);

typedef NTSTATUS (NTAPI *typedef_ZwTerminateProcess)(IN HANDLE ProcessHandle, IN NTSTATUS ExitStatus);

typedef BOOLEAN(NTAPI *typedef_SePrivilegeCheck)(IN OUT PPRIVILEGE_SET RequiredPrivileges,
												 IN PSECURITY_SUBJECT_CONTEXT SubjectSecurityContext,
												 IN KPROCESSOR_MODE AccessMode);

typedef PMDL(NTAPI *typedef_IoAllocateMdl)(IN PVOID VirtualAddress, IN ULONG Length, IN BOOLEAN SecondaryBuffer,
										   IN BOOLEAN ChargeQuota, IN OUT PIRP Irp OPTIONAL);

typedef VOID(NTAPI *typedef_MmProbeAndLockPages)(IN OUT PMDL MemoryDescriptorList, IN KPROCESSOR_MODE AccessMode,
												 IN LOCK_OPERATION Operation);

typedef PVOID(NTAPI *typedef_MmMapLockedPagesSpecifyCache)(IN PMDL MemoryDescriptorList, IN KPROCESSOR_MODE AccessMode,
														   IN MEMORY_CACHING_TYPE CacheType, IN PVOID BaseAddress,
														   IN ULONG BugCheckOnFailure, IN MM_PAGE_PRIORITY Priority);

typedef VOID(NTAPI *typedef_MmUnmapLockedPages)(IN PVOID BaseAddress, IN PMDL MemoryDescriptorList);

typedef VOID(NTAPI *typedef_MmUnlockPages)(IN PMDL MemoryDescriptorList);

typedef VOID(NTAPI *typedef_IoFreeMdl)(IN PMDL Mdl);

typedef VOID(NTAPI *typedef_KeBugCheckEx)(IN ULONG BugCheckCode, IN ULONG_PTR BugCheckParameter1,
										  IN ULONG_PTR BugCheckParameter2, IN ULONG_PTR BugCheckParameter3,
										  IN ULONG_PTR BugCheckParameter4);

typedef NTSTATUS(NTAPI *typedef_ObRegisterCallbacks)(IN POB_CALLBACK_REGISTRATION CallBackRegistration, OUT PVOID *RegistrationHandle);

typedef VOID(NTAPI *typedef_ObUnRegisterCallbacks)(IN PVOID RegistrationHandle);

typedef VOID(NTAPI *typedef_KeSetSystemAffinityThread)(IN KAFFINITY Affinity);

typedef VOID(NTAPI *typedef_KeRevertToUserAffinityThreadEx)(IN KAFFINITY Affinity);

typedef VOID(NTAPI *typedef_KeRevertToUserAffinityThread)(VOID);

typedef NTSTATUS(NTAPI *typedef_ZwUnloadDriver)(IN PUNICODE_STRING DriverServiceName);

typedef VOID(NTAPI *typedef_ExFreePool)(IN PVOID P);

typedef PEPROCESS (NTAPI *typedef_IoThreadToProcess)(IN PETHREAD Thread);

typedef BOOLEAN (NTAPI* typedef_PsIsCurrentThreadInServerSilo)(VOID);

typedef KPROCESSOR_MODE (NTAPI* typedef_ExGetPreviousMode)(VOID);

typedef NTSTATUS(NTAPI *typedef_ZwQuerySymbolicLinkObject)(IN HANDLE LinkHandle, IN OUT PUNICODE_STRING LinkTarget,
														   OUT OPTIONAL PULONG ReturnedLength);

typedef NTSTATUS(NTAPI *typedef_ZwOpenSymbolicLinkObject)(OUT PHANDLE LinkHandle, IN ACCESS_MASK DesiredAccess,
														  IN POBJECT_ATTRIBUTES ObjectAttributes);

typedef BOOLEAN(NTAPI *typedef_IoCancelIrp)(IN PIRP Irp);

typedef PIRP(NTAPI *typedef_IoAllocateIrp)(IN CCHAR StackSize, IN BOOLEAN ChargeQuota);

typedef VOID(NTAPI *typedef_IoReleaseCancelSpinLock)(IN KIRQL Irql);

typedef VOID(NTAPI *typedef_IoFreeIrp)(IN PIRP Irp);

typedef VOID(NTAPI *typedef_ExQueueWorkItem)(IN PWORK_QUEUE_ITEM WorkItem, IN WORK_QUEUE_TYPE QueueType);

typedef PKEVENT(NTAPI *typedef_IoCreateNotificationEvent)(IN PUNICODE_STRING EventName, OUT PHANDLE EventHandle);

typedef VOID(NTAPI *typedef_KeClearEvent)(IN PRKEVENT Event);

typedef NTSTATUS(NTAPI *typedef_RtlCreateSecurityDescriptor)(OUT PSECURITY_DESCRIPTOR SecurityDescriptor,
															 IN ULONG Revision);

typedef NTSTATUS(NTAPI *typedef_RtlCreateAcl)(PACL Acl, IN ULONG AclLength, IN ULONG AclRevision);

typedef NTSTATUS(NTAPI *typedef_RtlAddAccessAllowedAce)(IN OUT PACL Acl, IN ULONG AceRevision,
														IN ACCESS_MASK AccessMask, IN PSID Sid);

typedef NTSTATUS(NTAPI *typedef_RtlSetDaclSecurityDescriptor)(IN OUT PSECURITY_DESCRIPTOR SecurityDescriptor,
															  IN BOOLEAN DaclPresent, IN OPTIONAL PACL Dacl,
															  IN BOOLEAN DaclDefaulted);

typedef NTSTATUS(NTAPI *typedef_ZwEnumerateKey)(IN HANDLE KeyHandle, IN ULONG Index,
												IN KEY_INFORMATION_CLASS KeyInformationClass, OUT PVOID KeyInformation,
												IN ULONG Length, OUT PULONG ResultLength);

typedef NTSTATUS(NTAPI *typedef_ZwCreateEvent)(OUT PHANDLE EventHandle, IN ACCESS_MASK DesiredAccess,
											   IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL, IN EVENT_TYPE EventType,
											   IN BOOLEAN InitialState);

typedef NTSTATUS(NTAPI *typedef_ZwWaitForSingleObject)(IN HANDLE Handle, IN BOOLEAN Alertable,
													   IN PLARGE_INTEGER Timeout OPTIONAL);

typedef NTSTATUS(NTAPI *typedef_NtWaitForSingleObject)(IN HANDLE Handle, IN BOOLEAN Alertable,
													   IN PLARGE_INTEGER Timeout OPTIONAL);

typedef INT64(FASTCALL *typedef_ExfAcquirePushLockExclusive)(IN OUT PEX_PUSH_LOCK PushLock);

typedef INT64(FASTCALL *typedef_ExfAcquirePushLockShared)(IN OUT PEX_PUSH_LOCK PushLock);

typedef INT64(FASTCALL *typedef_ExfReleasePushLockExclusive)(IN OUT PEX_PUSH_LOCK PushLock);

typedef INT64(FASTCALL *typedef_ExfReleasePushLockShared)(IN OUT PEX_PUSH_LOCK PushLock);

typedef VOID(NTAPI *typedef_KeEnterCriticalRegion)(VOID);

typedef VOID(NTAPI *typedef_KeLeaveCriticalRegion)(VOID);

typedef VOID(FASTCALL *typedef_KeAcquireInStackQueuedSpinLock)(IN OUT PKSPIN_LOCK SpinLock,
															   OUT PKLOCK_QUEUE_HANDLE LockHandle);

typedef VOID(FASTCALL *typedef_KeReleaseInStackQueuedSpinLock)(IN PKLOCK_QUEUE_HANDLE LockHandle);

typedef NTSTATUS(NTAPI *typedef_ExInitializeResourceLite)(IN PERESOURCE Resource);

typedef NTSTATUS(NTAPI *typedef_ExDeleteResourceLite)(IN PERESOURCE Resource);

typedef BOOLEAN(NTAPI *typedef_ExAcquireResourceSharedLite)(IN PERESOURCE Resource, IN BOOLEAN Wait);

typedef BOOLEAN(NTAPI *typedef_ExAcquireResourceExclusiveLite)(IN PERESOURCE Resource, IN BOOLEAN Wait);

typedef VOID(NTAPI *typedef_ExReleaseResourceLite)(IN PERESOURCE Resource);

typedef ULONG(NTAPI *typedef_vDbgPrintEx)(IN ULONG ComponentId, IN ULONG Level, IN PCHAR Format,
										  IN va_list arglist);

typedef VOID(NTAPI *typedef_ExRaiseStatus)(IN NTSTATUS Status);

typedef PVOID(NTAPI *typedef_MmGetVirtualForPhysical)(IN PHYSICAL_ADDRESS PhysicalAddress);

// clang-format on

#endif // _H_APIDEF_
