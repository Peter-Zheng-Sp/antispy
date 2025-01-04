#ifndef _H_SYSTEMDEFINE_
#define _H_SYSTEMDEFINE_

#include <ntifs.h>

#include <windef.h>

// clang-format off

#define MEM_IMAGE                   0x01000000  

#define MM_ZERO_ACCESS         0  // this value is not used.
#define MM_READONLY            1
#define MM_EXECUTE             2
#define MM_EXECUTE_READ        3
#define MM_READWRITE           4  // bit 2 is set if this is writable.
#define MM_WRITECOPY           5
#define MM_EXECUTE_READWRITE   6
#define MM_EXECUTE_WRITECOPY   7

#define MM_NOCACHE            0x8
#define MM_GUARD_PAGE         0x10
#define MM_DECOMMIT           0x10   // NO_ACCESS, Guard page
#define MM_NOACCESS           0x18   // NO_ACCESS, Guard_page, nocache.
#define MM_UNKNOWN_PROTECTION 0x100  // bigger than 5 bits!

#define MM_INVALID_PROTECTION ((ULONG)-1)  // bigger than 5 bits!

#define MM_PROTECTION_WRITE_MASK     4
#define MM_PROTECTION_COPY_MASK      1
#define MM_PROTECTION_OPERATION_MASK 7 // mask off guard page and nocache.
#define MM_PROTECTION_EXECUTE_MASK   2

#define MM_SECURE_DELETE_CHECK 0x55

#if defined(_M_AMD64) || defined(_WIN64)

//
// A VALID Page Table Entry on an AMD64 has the following definition.
//

#define MI_MAXIMUM_PAGEFILE_SIZE (((UINT64)4 * 1024 * 1024 * 1024 - 1) * PAGE_SIZE)

#define MI_PTE_LOOKUP_NEEDED ((ULONG64)0xffffffff)

#else

//
// A VALID Page Table Entry on the x86 has the following definition.
//

#define MI_MAXIMUM_PAGEFILE_SIZE (((UINT64)1 * 1024 * 1024 - 1) * PAGE_SIZE)

#define MI_PTE_LOOKUP_NEEDED (0xfffff)

#endif

#define MI_PTE_OWNER_USER       1

#define MI_PTE_OWNER_KERNEL     0

#define PROCESS_TERMINATE (0x0001)
#define PROCESS_QUERY_INFORMATION (0x0400)
#define PROCESS_VM_OPERATION (0x0008)
#define PROCESS_VM_WRITE (0x0020)
#define PROCESS_VM_READ (0x0010)
#define PROCESS_SET_INFORMATION (0x0200)
#define PROCESS_SUSPEND_RESUME (0x0800)

#ifndef OBJ_PROTECT_CLOSE
#define OBJ_PROTECT_CLOSE 0x00000001
#endif
#ifndef OBJ_INHERIT
#define OBJ_INHERIT 0x00000002
#endif
#ifndef OBJ_AUDIT_OBJECT_CLOSE
#define OBJ_AUDIT_OBJECT_CLOSE 0x00000004
#endif

#define NUMBER_HASH_BUCKETS 37

#ifndef UNICODE_STRING_MAX_BYTES
#define UNICODE_STRING_MAX_BYTES ((WORD  ) 65534) 
#define UNICODE_STRING_MAX_CHARS (32767) 
#endif

//0x58 bytes (sizeof)
struct _PEB_LDR_DATA
{
	ULONG Length;                                                           //0x0
	UCHAR Initialized;                                                      //0x4
	VOID* SsHandle;                                                         //0x8
	struct _LIST_ENTRY InLoadOrderModuleList;                               //0x10
	struct _LIST_ENTRY InMemoryOrderModuleList;                             //0x20
	struct _LIST_ENTRY InInitializationOrderModuleList;                     //0x30
	VOID* EntryInProgress;                                                  //0x40
	UCHAR ShutdownInProgress;                                               //0x48
	VOID* ShutdownThreadId;                                                 //0x50
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _LDR_DATA_TABLE_ENTRY
{
	struct _LIST_ENTRY InLoadOrderLinks;                                    //0x0
	struct _LIST_ENTRY InMemoryOrderLinks;                                  //0x10
	struct _LIST_ENTRY InInitializationOrderLinks;                          //0x20
	VOID* DllBase;                                                          //0x30
	VOID* EntryPoint;                                                       //0x38
	ULONG SizeOfImage;                                                      //0x40
	struct _UNICODE_STRING FullDllName;                                     //0x48
	struct _UNICODE_STRING BaseDllName;                                     //0x58
	//...
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef enum _MEMORY_INFORMATION_CLASS {
	MemoryBasicInformation,
    MemoryWorkingSetList,
    MemorySectionName,
    MemoryBasicVlmInformation,  
} MEMORY_INFORMATION_CLASS;

typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBasicInformation, // q: SYSTEM_BASIC_INFORMATION
	SystemProcessorInformation, // q: SYSTEM_PROCESSOR_INFORMATION
	SystemPerformanceInformation, // q: SYSTEM_PERFORMANCE_INFORMATION
	SystemTimeOfDayInformation, // q: SYSTEM_TIMEOFDAY_INFORMATION
	SystemPathInformation, // not implemented
	SystemProcessInformation, // q: SYSTEM_PROCESS_INFORMATION
	SystemCallCountInformation, // q: SYSTEM_CALL_COUNT_INFORMATION
	SystemDeviceInformation, // q: SYSTEM_DEVICE_INFORMATION
	SystemProcessorPerformanceInformation, // q: SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION (EX in: USHORT ProcessorGroup)
	SystemFlagsInformation, // q: SYSTEM_FLAGS_INFORMATION
	SystemCallTimeInformation, // not implemented // SYSTEM_CALL_TIME_INFORMATION // 10
	SystemModuleInformation, // q: RTL_PROCESS_MODULES
	SystemLocksInformation, // q: RTL_PROCESS_LOCKS
	SystemStackTraceInformation, // q: RTL_PROCESS_BACKTRACES
	SystemPagedPoolInformation, // not implemented
	SystemNonPagedPoolInformation, // not implemented
	SystemHandleInformation, // q: SYSTEM_HANDLE_INFORMATION
	SystemObjectInformation, // q: SYSTEM_OBJECTTYPE_INFORMATION mixed with SYSTEM_OBJECT_INFORMATION
	SystemPageFileInformation, // q: SYSTEM_PAGEFILE_INFORMATION
	SystemVdmInstemulInformation, // q: SYSTEM_VDM_INSTEMUL_INFO
	SystemVdmBopInformation, // not implemented // 20
	SystemFileCacheInformation, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypeSystemCache)
	SystemPoolTagInformation, // q: SYSTEM_POOLTAG_INFORMATION
	SystemInterruptInformation, // q: SYSTEM_INTERRUPT_INFORMATION (EX in: USHORT ProcessorGroup)
	SystemDpcBehaviorInformation, // q: SYSTEM_DPC_BEHAVIOR_INFORMATION; s: SYSTEM_DPC_BEHAVIOR_INFORMATION (requires SeLoadDriverPrivilege)
	SystemFullMemoryInformation, // not implemented // SYSTEM_MEMORY_USAGE_INFORMATION
	SystemLoadGdiDriverInformation, // s (kernel-mode only)
	SystemUnloadGdiDriverInformation, // s (kernel-mode only)
	SystemTimeAdjustmentInformation, // q: SYSTEM_QUERY_TIME_ADJUST_INFORMATION; s: SYSTEM_SET_TIME_ADJUST_INFORMATION (requires SeSystemtimePrivilege)
	SystemSummaryMemoryInformation, // not implemented // SYSTEM_MEMORY_USAGE_INFORMATION
	SystemMirrorMemoryInformation, // s (requires license value "Kernel-MemoryMirroringSupported") (requires SeShutdownPrivilege) // 30
	SystemPerformanceTraceInformation, // q; s: (type depends on EVENT_TRACE_INFORMATION_CLASS)
	SystemObsolete0, // not implemented
	SystemExceptionInformation, // q: SYSTEM_EXCEPTION_INFORMATION
	SystemCrashDumpStateInformation, // s: SYSTEM_CRASH_DUMP_STATE_INFORMATION (requires SeDebugPrivilege)
	SystemKernelDebuggerInformation, // q: SYSTEM_KERNEL_DEBUGGER_INFORMATION
	SystemContextSwitchInformation, // q: SYSTEM_CONTEXT_SWITCH_INFORMATION
	SystemRegistryQuotaInformation, // q: SYSTEM_REGISTRY_QUOTA_INFORMATION; s (requires SeIncreaseQuotaPrivilege)
	SystemExtendServiceTableInformation, // s (requires SeLoadDriverPrivilege) // loads win32k only
	SystemPrioritySeperation, // s (requires SeTcbPrivilege)
	SystemVerifierAddDriverInformation, // s (requires SeDebugPrivilege) // 40
	SystemVerifierRemoveDriverInformation, // s (requires SeDebugPrivilege)
	SystemProcessorIdleInformation, // q: SYSTEM_PROCESSOR_IDLE_INFORMATION (EX in: USHORT ProcessorGroup)
	SystemLegacyDriverInformation, // q: SYSTEM_LEGACY_DRIVER_INFORMATION
	SystemCurrentTimeZoneInformation, // q; s: RTL_TIME_ZONE_INFORMATION
	SystemLookasideInformation, // q: SYSTEM_LOOKASIDE_INFORMATION
	SystemTimeSlipNotification, // s: HANDLE (NtCreateEvent) (requires SeSystemtimePrivilege)
	SystemSessionCreate, // not implemented
	SystemSessionDetach, // not implemented
	SystemSessionInformation, // not implemented (SYSTEM_SESSION_INFORMATION)
	SystemRangeStartInformation, // q: SYSTEM_RANGE_START_INFORMATION // 50
	SystemVerifierInformation, // q: SYSTEM_VERIFIER_INFORMATION; s (requires SeDebugPrivilege)
	SystemVerifierThunkExtend, // s (kernel-mode only)
	SystemSessionProcessInformation, // q: SYSTEM_SESSION_PROCESS_INFORMATION
	SystemLoadGdiDriverInSystemSpace, // s: SYSTEM_GDI_DRIVER_INFORMATION (kernel-mode only) (same as SystemLoadGdiDriverInformation)
	SystemNumaProcessorMap, // q: SYSTEM_NUMA_INFORMATION
	SystemPrefetcherInformation, // q; s: PREFETCHER_INFORMATION // PfSnQueryPrefetcherInformation
	SystemExtendedProcessInformation, // q: SYSTEM_PROCESS_INFORMATION
	SystemRecommendedSharedDataAlignment, // q: ULONG // KeGetRecommendedSharedDataAlignment
	SystemComPlusPackage, // q; s: ULONG
	SystemNumaAvailableMemory, // q: SYSTEM_NUMA_INFORMATION // 60
	SystemProcessorPowerInformation, // q: SYSTEM_PROCESSOR_POWER_INFORMATION (EX in: USHORT ProcessorGroup)
	SystemEmulationBasicInformation, // q: SYSTEM_BASIC_INFORMATION
	SystemEmulationProcessorInformation, // q: SYSTEM_PROCESSOR_INFORMATION
	SystemExtendedHandleInformation, // q: SYSTEM_HANDLE_INFORMATION_EX
	SystemLostDelayedWriteInformation, // q: ULONG
	SystemBigPoolInformation, // q: SYSTEM_BIGPOOL_INFORMATION
	SystemSessionPoolTagInformation, // q: SYSTEM_SESSION_POOLTAG_INFORMATION
	SystemSessionMappedViewInformation, // q: SYSTEM_SESSION_MAPPED_VIEW_INFORMATION
	SystemHotpatchInformation, // q; s: SYSTEM_HOTPATCH_CODE_INFORMATION
	SystemObjectSecurityMode, // q: ULONG // 70
	SystemWatchdogTimerHandler, // s: SYSTEM_WATCHDOG_HANDLER_INFORMATION // (kernel-mode only)
	SystemWatchdogTimerInformation, // q: SYSTEM_WATCHDOG_TIMER_INFORMATION // (kernel-mode only)
	SystemLogicalProcessorInformation, // q: SYSTEM_LOGICAL_PROCESSOR_INFORMATION (EX in: USHORT ProcessorGroup)
	SystemWow64SharedInformationObsolete, // not implemented
	SystemRegisterFirmwareTableInformationHandler, // s: SYSTEM_FIRMWARE_TABLE_HANDLER // (kernel-mode only)
	SystemFirmwareTableInformation, // SYSTEM_FIRMWARE_TABLE_INFORMATION
	SystemModuleInformationEx, // q: RTL_PROCESS_MODULE_INFORMATION_EX
	SystemVerifierTriageInformation, // not implemented
	SystemSuperfetchInformation, // q; s: SUPERFETCH_INFORMATION // PfQuerySuperfetchInformation
	SystemMemoryListInformation, // q: SYSTEM_MEMORY_LIST_INFORMATION; s: SYSTEM_MEMORY_LIST_COMMAND (requires SeProfileSingleProcessPrivilege) // 80
	SystemFileCacheInformationEx, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (same as SystemFileCacheInformation)
	SystemThreadPriorityClientIdInformation, // s: SYSTEM_THREAD_CID_PRIORITY_INFORMATION (requires SeIncreaseBasePriorityPrivilege)
	SystemProcessorIdleCycleTimeInformation, // q: SYSTEM_PROCESSOR_IDLE_CYCLE_TIME_INFORMATION[] (EX in: USHORT ProcessorGroup)
	SystemVerifierCancellationInformation, // SYSTEM_VERIFIER_CANCELLATION_INFORMATION // name:wow64:whNT32QuerySystemVerifierCancellationInformation
	SystemProcessorPowerInformationEx, // not implemented
	SystemRefTraceInformation, // q; s: SYSTEM_REF_TRACE_INFORMATION // ObQueryRefTraceInformation
	SystemSpecialPoolInformation, // q; s: SYSTEM_SPECIAL_POOL_INFORMATION (requires SeDebugPrivilege) // MmSpecialPoolTag, then MmSpecialPoolCatchOverruns != 0
	SystemProcessIdInformation, // q: SYSTEM_PROCESS_ID_INFORMATION
	SystemErrorPortInformation, // s (requires SeTcbPrivilege)
	SystemBootEnvironmentInformation, // q: SYSTEM_BOOT_ENVIRONMENT_INFORMATION // 90
	SystemHypervisorInformation, // q: SYSTEM_HYPERVISOR_QUERY_INFORMATION
	SystemVerifierInformationEx, // q; s: SYSTEM_VERIFIER_INFORMATION_EX
	SystemTimeZoneInformation, // q; s: RTL_TIME_ZONE_INFORMATION (requires SeTimeZonePrivilege)
	SystemImageFileExecutionOptionsInformation, // s: SYSTEM_IMAGE_FILE_EXECUTION_OPTIONS_INFORMATION (requires SeTcbPrivilege)
	SystemCoverageInformation, // q: COVERAGE_MODULES s: COVERAGE_MODULE_REQUEST // ExpCovQueryInformation (requires SeDebugPrivilege)
	SystemPrefetchPatchInformation, // SYSTEM_PREFETCH_PATCH_INFORMATION
	SystemVerifierFaultsInformation, // s: SYSTEM_VERIFIER_FAULTS_INFORMATION (requires SeDebugPrivilege)
	SystemSystemPartitionInformation, // q: SYSTEM_SYSTEM_PARTITION_INFORMATION
	SystemSystemDiskInformation, // q: SYSTEM_SYSTEM_DISK_INFORMATION
	SystemProcessorPerformanceDistribution, // q: SYSTEM_PROCESSOR_PERFORMANCE_DISTRIBUTION (EX in: USHORT ProcessorGroup) // 100
	SystemNumaProximityNodeInformation, // q; s: SYSTEM_NUMA_PROXIMITY_MAP
	SystemDynamicTimeZoneInformation, // q; s: RTL_DYNAMIC_TIME_ZONE_INFORMATION (requires SeTimeZonePrivilege)
	SystemCodeIntegrityInformation, // q: SYSTEM_CODEINTEGRITY_INFORMATION // SeCodeIntegrityQueryInformation
	SystemProcessorMicrocodeUpdateInformation, // s: SYSTEM_PROCESSOR_MICROCODE_UPDATE_INFORMATION
	SystemProcessorBrandString, // q: CHAR[] // HaliQuerySystemInformation -> HalpGetProcessorBrandString, info class 23
	SystemVirtualAddressInformation, // q: SYSTEM_VA_LIST_INFORMATION[]; s: SYSTEM_VA_LIST_INFORMATION[] (requires SeIncreaseQuotaPrivilege) // MmQuerySystemVaInformation
	SystemLogicalProcessorAndGroupInformation, // q: SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX (EX in: LOGICAL_PROCESSOR_RELATIONSHIP RelationshipType) // since WIN7 // KeQueryLogicalProcessorRelationship
	SystemProcessorCycleTimeInformation, // q: SYSTEM_PROCESSOR_CYCLE_TIME_INFORMATION[] (EX in: USHORT ProcessorGroup)
	SystemStoreInformation, // q; s: SYSTEM_STORE_INFORMATION (requires SeProfileSingleProcessPrivilege) // SmQueryStoreInformation
	SystemRegistryAppendString, // s: SYSTEM_REGISTRY_APPEND_STRING_PARAMETERS // 110
	SystemAitSamplingValue, // s: ULONG (requires SeProfileSingleProcessPrivilege)
	SystemVhdBootInformation, // q: SYSTEM_VHD_BOOT_INFORMATION
	SystemCpuQuotaInformation, // q; s: PS_CPU_QUOTA_QUERY_INFORMATION
	SystemNativeBasicInformation, // q: SYSTEM_BASIC_INFORMATION
	SystemErrorPortTimeouts, // SYSTEM_ERROR_PORT_TIMEOUTS
	SystemLowPriorityIoInformation, // q: SYSTEM_LOW_PRIORITY_IO_INFORMATION
	SystemTpmBootEntropyInformation, // q: TPM_BOOT_ENTROPY_NT_RESULT // ExQueryTpmBootEntropyInformation
	SystemVerifierCountersInformation, // q: SYSTEM_VERIFIER_COUNTERS_INFORMATION
	SystemPagedPoolInformationEx, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypePagedPool)
	SystemSystemPtesInformationEx, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypeSystemPtes) // 120
	SystemNodeDistanceInformation, // q: USHORT[4*NumaNodes] // (EX in: USHORT NodeNumber)
	SystemAcpiAuditInformation, // q: SYSTEM_ACPI_AUDIT_INFORMATION // HaliQuerySystemInformation -> HalpAuditQueryResults, info class 26
	SystemBasicPerformanceInformation, // q: SYSTEM_BASIC_PERFORMANCE_INFORMATION // name:wow64:whNtQuerySystemInformation_SystemBasicPerformanceInformation
	SystemQueryPerformanceCounterInformation, // q: SYSTEM_QUERY_PERFORMANCE_COUNTER_INFORMATION // since WIN7 SP1
	SystemSessionBigPoolInformation, // q: SYSTEM_SESSION_POOLTAG_INFORMATION // since WIN8
	SystemBootGraphicsInformation, // q; s: SYSTEM_BOOT_GRAPHICS_INFORMATION (kernel-mode only)
	SystemScrubPhysicalMemoryInformation, // q; s: MEMORY_SCRUB_INFORMATION
	SystemBadPageInformation,
	SystemProcessorProfileControlArea, // q; s: SYSTEM_PROCESSOR_PROFILE_CONTROL_AREA
	SystemCombinePhysicalMemoryInformation, // s: MEMORY_COMBINE_INFORMATION, MEMORY_COMBINE_INFORMATION_EX, MEMORY_COMBINE_INFORMATION_EX2 // 130
	SystemEntropyInterruptTimingInformation, // q; s: SYSTEM_ENTROPY_TIMING_INFORMATION
	SystemConsoleInformation, // q; s: SYSTEM_CONSOLE_INFORMATION
	SystemPlatformBinaryInformation, // q: SYSTEM_PLATFORM_BINARY_INFORMATION (requires SeTcbPrivilege)
	SystemPolicyInformation, // q: SYSTEM_POLICY_INFORMATION
	SystemHypervisorProcessorCountInformation, // q: SYSTEM_HYPERVISOR_PROCESSOR_COUNT_INFORMATION
	SystemDeviceDataInformation, // q: SYSTEM_DEVICE_DATA_INFORMATION
	SystemDeviceDataEnumerationInformation, // q: SYSTEM_DEVICE_DATA_INFORMATION
	SystemMemoryTopologyInformation, // q: SYSTEM_MEMORY_TOPOLOGY_INFORMATION
	SystemMemoryChannelInformation, // q: SYSTEM_MEMORY_CHANNEL_INFORMATION
	SystemBootLogoInformation, // q: SYSTEM_BOOT_LOGO_INFORMATION // 140
	SystemProcessorPerformanceInformationEx, // q: SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION_EX // (EX in: USHORT ProcessorGroup) // since WINBLUE
	SystemCriticalProcessErrorLogInformation,
	SystemSecureBootPolicyInformation, // q: SYSTEM_SECUREBOOT_POLICY_INFORMATION
	SystemPageFileInformationEx, // q: SYSTEM_PAGEFILE_INFORMATION_EX
	SystemSecureBootInformation, // q: SYSTEM_SECUREBOOT_INFORMATION
	SystemEntropyInterruptTimingRawInformation,
	SystemPortableWorkspaceEfiLauncherInformation, // q: SYSTEM_PORTABLE_WORKSPACE_EFI_LAUNCHER_INFORMATION
	SystemFullProcessInformation, // q: SYSTEM_PROCESS_INFORMATION with SYSTEM_PROCESS_INFORMATION_EXTENSION (requires admin)
	SystemKernelDebuggerInformationEx, // q: SYSTEM_KERNEL_DEBUGGER_INFORMATION_EX
	SystemBootMetadataInformation, // 150
	SystemSoftRebootInformation, // q: ULONG
	SystemElamCertificateInformation, // s: SYSTEM_ELAM_CERTIFICATE_INFORMATION
	SystemOfflineDumpConfigInformation, // q: OFFLINE_CRASHDUMP_CONFIGURATION_TABLE_V2
	SystemProcessorFeaturesInformation, // q: SYSTEM_PROCESSOR_FEATURES_INFORMATION
	SystemRegistryReconciliationInformation, // s: NULL (requires admin) (flushes registry hives)
	SystemEdidInformation, // q: SYSTEM_EDID_INFORMATION
	SystemManufacturingInformation, // q: SYSTEM_MANUFACTURING_INFORMATION // since THRESHOLD
	SystemEnergyEstimationConfigInformation, // q: SYSTEM_ENERGY_ESTIMATION_CONFIG_INFORMATION
	SystemHypervisorDetailInformation, // q: SYSTEM_HYPERVISOR_DETAIL_INFORMATION
	SystemProcessorCycleStatsInformation, // q: SYSTEM_PROCESSOR_CYCLE_STATS_INFORMATION (EX in: USHORT ProcessorGroup) // 160
	SystemVmGenerationCountInformation,
	SystemTrustedPlatformModuleInformation, // q: SYSTEM_TPM_INFORMATION
	SystemKernelDebuggerFlags, // SYSTEM_KERNEL_DEBUGGER_FLAGS
	SystemCodeIntegrityPolicyInformation, // q: SYSTEM_CODEINTEGRITYPOLICY_INFORMATION
	SystemIsolatedUserModeInformation, // q: SYSTEM_ISOLATED_USER_MODE_INFORMATION
	SystemHardwareSecurityTestInterfaceResultsInformation,
	SystemSingleModuleInformation, // q: SYSTEM_SINGLE_MODULE_INFORMATION
	SystemAllowedCpuSetsInformation,
	SystemVsmProtectionInformation, // q: SYSTEM_VSM_PROTECTION_INFORMATION (previously SystemDmaProtectionInformation)
	SystemInterruptCpuSetsInformation, // q: SYSTEM_INTERRUPT_CPU_SET_INFORMATION // 170
	SystemSecureBootPolicyFullInformation, // q: SYSTEM_SECUREBOOT_POLICY_FULL_INFORMATION
	SystemCodeIntegrityPolicyFullInformation,
	SystemAffinitizedInterruptProcessorInformation, // (requires SeIncreaseBasePriorityPrivilege)
	SystemRootSiloInformation, // q: SYSTEM_ROOT_SILO_INFORMATION
	SystemCpuSetInformation, // q: SYSTEM_CPU_SET_INFORMATION // since THRESHOLD2
	SystemCpuSetTagInformation, // q: SYSTEM_CPU_SET_TAG_INFORMATION
	SystemWin32WerStartCallout,
	SystemSecureKernelProfileInformation, // q: SYSTEM_SECURE_KERNEL_HYPERGUARD_PROFILE_INFORMATION
	SystemCodeIntegrityPlatformManifestInformation, // q: SYSTEM_SECUREBOOT_PLATFORM_MANIFEST_INFORMATION // since REDSTONE
	SystemInterruptSteeringInformation, // SYSTEM_INTERRUPT_STEERING_INFORMATION_INPUT // 180
	SystemSupportedProcessorArchitectures, // p: in opt: HANDLE, out: SYSTEM_SUPPORTED_PROCESSOR_ARCHITECTURES_INFORMATION[] // NtQuerySystemInformationEx
	SystemMemoryUsageInformation, // q: SYSTEM_MEMORY_USAGE_INFORMATION
	SystemCodeIntegrityCertificateInformation, // q: SYSTEM_CODEINTEGRITY_CERTIFICATE_INFORMATION
	SystemPhysicalMemoryInformation, // q: SYSTEM_PHYSICAL_MEMORY_INFORMATION // since REDSTONE2
	SystemControlFlowTransition,
	SystemKernelDebuggingAllowed, // s: ULONG
	SystemActivityModerationExeState, // SYSTEM_ACTIVITY_MODERATION_EXE_STATE
	SystemActivityModerationUserSettings, // SYSTEM_ACTIVITY_MODERATION_USER_SETTINGS
	SystemCodeIntegrityPoliciesFullInformation,
	SystemCodeIntegrityUnlockInformation, // SYSTEM_CODEINTEGRITY_UNLOCK_INFORMATION // 190
	SystemIntegrityQuotaInformation,
	SystemFlushInformation, // q: SYSTEM_FLUSH_INFORMATION
	SystemProcessorIdleMaskInformation, // q: ULONG_PTR[ActiveGroupCount] // since REDSTONE3
	SystemSecureDumpEncryptionInformation,
	SystemWriteConstraintInformation, // SYSTEM_WRITE_CONSTRAINT_INFORMATION
	SystemKernelVaShadowInformation, // SYSTEM_KERNEL_VA_SHADOW_INFORMATION
	SystemHypervisorSharedPageInformation, // SYSTEM_HYPERVISOR_SHARED_PAGE_INFORMATION // since REDSTONE4
	SystemFirmwareBootPerformanceInformation,
	SystemCodeIntegrityVerificationInformation, // SYSTEM_CODEINTEGRITYVERIFICATION_INFORMATION
	SystemFirmwarePartitionInformation, // SYSTEM_FIRMWARE_PARTITION_INFORMATION // 200
	SystemSpeculationControlInformation, // SYSTEM_SPECULATION_CONTROL_INFORMATION // (CVE-2017-5715) REDSTONE3 and above.
	SystemDmaGuardPolicyInformation, // SYSTEM_DMA_GUARD_POLICY_INFORMATION
	SystemEnclaveLaunchControlInformation, // SYSTEM_ENCLAVE_LAUNCH_CONTROL_INFORMATION
	SystemWorkloadAllowedCpuSetsInformation, // SYSTEM_WORKLOAD_ALLOWED_CPU_SET_INFORMATION // since REDSTONE5
	SystemCodeIntegrityUnlockModeInformation,
	SystemLeapSecondInformation, // SYSTEM_LEAP_SECOND_INFORMATION
	SystemFlags2Information, // q: SYSTEM_FLAGS_INFORMATION
	SystemSecurityModelInformation, // SYSTEM_SECURITY_MODEL_INFORMATION // since 19H1
	SystemCodeIntegritySyntheticCacheInformation,
	SystemFeatureConfigurationInformation, // SYSTEM_FEATURE_CONFIGURATION_INFORMATION // since 20H1 // 210
	SystemFeatureConfigurationSectionInformation, // SYSTEM_FEATURE_CONFIGURATION_SECTIONS_INFORMATION
	SystemFeatureUsageSubscriptionInformation, // SYSTEM_FEATURE_USAGE_SUBSCRIPTION_DETAILS
	SystemSecureSpeculationControlInformation, // SECURE_SPECULATION_CONTROL_INFORMATION
	SystemSpacesBootInformation, // since 20H2
	SystemFwRamdiskInformation, // SYSTEM_FIRMWARE_RAMDISK_INFORMATION
	SystemWheaIpmiHardwareInformation,
	SystemDifSetRuleClassInformation,
	SystemDifClearRuleClassInformation,
	SystemDifApplyPluginVerificationOnDriver,
	SystemDifRemovePluginVerificationOnDriver, // 220
	SystemShadowStackInformation, // SYSTEM_SHADOW_STACK_INFORMATION
	SystemBuildVersionInformation, // SYSTEM_BUILD_VERSION_INFORMATION
	SystemPoolLimitInformation, // SYSTEM_POOL_LIMIT_INFORMATION
	SystemCodeIntegrityAddDynamicStore,
	SystemCodeIntegrityClearDynamicStores,
	SystemDifPoolTrackingInformation,
	SystemPoolZeroingInformation, // SYSTEM_POOL_ZEROING_INFORMATION
	SystemDpcWatchdogInformation,
	SystemDpcWatchdogInformation2,
	SystemSupportedProcessorArchitectures2, // q: in opt: HANDLE, out: SYSTEM_SUPPORTED_PROCESSOR_ARCHITECTURES_INFORMATION[] // NtQuerySystemInformationEx  // 230
	SystemSingleProcessorRelationshipInformation, // q: SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX // (EX in: PROCESSOR_NUMBER Processor)
	SystemXfgCheckFailureInformation,
	SystemIommuStateInformation, // SYSTEM_IOMMU_STATE_INFORMATION // since 22H1
	SystemHypervisorMinrootInformation, // SYSTEM_HYPERVISOR_MINROOT_INFORMATION
	SystemHypervisorBootPagesInformation, // SYSTEM_HYPERVISOR_BOOT_PAGES_INFORMATION
	SystemPointerAuthInformation, // SYSTEM_POINTER_AUTH_INFORMATION
	SystemSecureKernelDebuggerInformation,
	SystemOriginalImageFeatureInformation,
	MaxSystemInfoClass
} SYSTEM_INFORMATION_CLASS, *PSYSTEM_INFORMATION_CLASS;

typedef struct _SYSTEM_PERFORMANCE_INFORMATION {
	LARGE_INTEGER IdleTime;
	LARGE_INTEGER ReadTransferCount;
	LARGE_INTEGER WriteTransferCount;
	LARGE_INTEGER OtherTransferCount;
	ULONG ReadOperationCount;
	ULONG WriteOperationCount;
	ULONG OtherOperationCount;
	ULONG AvailablePages;
	ULONG TotalCommittedPages;
	ULONG TotalCommitLimit;
	ULONG PeakCommitment;
	ULONG PageFaults;
	ULONG WriteCopyFaults;
	ULONG TransitionFaults;
	ULONG CacheTransitionFaults;
	ULONG DemandZeroFaults;
	ULONG PagesRead;
	ULONG PageReadIos;
	ULONG CacheReads;
	ULONG CacheIos;
	ULONG PagefilePagesWritten;
	ULONG PagefilePageWriteIos;
	ULONG MappedFilePagesWritten;
	ULONG MappedFilePageWriteIos;
	ULONG PagedPoolUsage;
	ULONG NonPagedPoolUsage;
	ULONG PagedPoolAllocs;
	ULONG PagedPoolFrees;
	ULONG NonPagedPoolAllocs;
	ULONG NonPagedPoolFrees;
	ULONG TotalFreeSystemPtes;
	ULONG SystemCodePage;
	ULONG TotalSystemDriverPages;
	ULONG TotalSystemCodePages;
	ULONG SmallNonPagedLookasideListAllocateHits;
	ULONG SmallPagedLookasideListAllocateHits;
	ULONG Reserved3;
	ULONG MmSystemCachePage;
	ULONG PagedPoolPage;
	ULONG SystemDriverPage;
	ULONG FastReadNoWait;
	ULONG FastReadWait;
	ULONG FastReadResourceMiss;
	ULONG FastReadNotPossible;
	ULONG FastMdlReadNoWait;
	ULONG FastMdlReadWait;
	ULONG FastMdlReadResourceMiss;
	ULONG FastMdlReadNotPossible;
	ULONG MapDataNoWait;
	ULONG MapDataWait;
	ULONG MapDataNoWaitMiss;
	ULONG MapDataWaitMiss;
	ULONG PinMappedDataCount;
	ULONG PinReadNoWait;
	ULONG PinReadWait;
	ULONG PinReadNoWaitMiss;
	ULONG PinReadWaitMiss;
	ULONG CopyReadNoWait;
	ULONG CopyReadWait;
	ULONG CopyReadNoWaitMiss;
	ULONG CopyReadWaitMiss;
	ULONG MdlReadNoWait;
	ULONG MdlReadWait;
	ULONG MdlReadNoWaitMiss;
	ULONG MdlReadWaitMiss;
	ULONG ReadAheadIos;
	ULONG LazyWriteIos;
	ULONG LazyWritePages;
	ULONG DataFlushes;
	ULONG DataPages;
	ULONG ContextSwitches;
	ULONG FirstLevelTbFills;
	ULONG SecondLevelTbFills;
	ULONG SystemCalls;
} SYSTEM_PERFORMANCE_INFORMATION, *PSYSTEM_PERFORMANCE_INFORMATION;

typedef enum _KTHREAD_STATE {
	Initialized,
	Ready,
	Running,
	Standby,
	Terminated,
	Waiting,
	Transition,
	DeferredReady,
	GateWaitObsolete,
	WaitingForProcessInSwap,
	MaximumThreadState
} KTHREAD_STATE, * PKTHREAD_STATE;

typedef struct _SYSTEM_THREAD_INFORMATION {
	LARGE_INTEGER KernelTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER CreateTime;
	ULONG WaitTime;
	PVOID StartAddress;
	CLIENT_ID ClientId;
	LONG /* KPRIORITY */ Priority;
	LONG BasePriority;
	ULONG ContextSwitches;
	ULONG /* KTHREAD_STATE */ ThreadState;
	ULONG /* KWAIT_REASON */WaitReason;
} SYSTEM_THREAD_INFORMATION, * PSYSTEM_THREAD_INFORMATION;

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO {
	USHORT UniqueProcessId;
	USHORT CreatorBackTraceIndex;
	UCHAR ObjectTypeIndex;
	UCHAR HandleAttributes;
	USHORT HandleValue;
	PVOID Object;
	ULONG GrantedAccess;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO;

typedef struct _SYSTEM_HANDLE_INFORMATION {
	ULONG NumberOfHandles;
	SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX
{
	PVOID Object;
	ULONG_PTR UniqueProcessId;
	ULONG_PTR HandleValue;
	ULONG GrantedAccess;
	USHORT CreatorBackTraceIndex;
	USHORT ObjectTypeIndex;
	ULONG HandleAttributes;
	ULONG Reserved;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO_EX;

typedef struct _SYSTEM_HANDLE_INFORMATION_EX
{
	ULONG_PTR NumberOfHandles;
	ULONG_PTR Reserved;
	SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX Handles[1];
} SYSTEM_HANDLE_INFORMATION_EX, *PSYSTEM_HANDLE_INFORMATION_EX;

typedef struct _MEMORY_SECTION_NAME {
	UNICODE_STRING Name;
	WCHAR     Buffer[260];
} MEMORY_SECTION_NAME, *PMEMORY_SECTION_NAME;

typedef struct _PROCESS_HANDLE_TABLE_ENTRY_INFO
{
	HANDLE HandleValue;
	ULONG_PTR HandleCount;
	ULONG_PTR PointerCount;
	ULONG GrantedAccess;
	ULONG ObjectTypeIndex;
	ULONG HandleAttributes;
	ULONG Reserved;
} PROCESS_HANDLE_TABLE_ENTRY_INFO, *PPROCESS_HANDLE_TABLE_ENTRY_INFO;

typedef struct _PROCESS_HANDLE_SNAPSHOT_INFORMATION
{
	ULONG_PTR NumberOfHandles;
	ULONG_PTR Reserved;
	PROCESS_HANDLE_TABLE_ENTRY_INFO Handles[1];
} PROCESS_HANDLE_SNAPSHOT_INFORMATION, *PPROCESS_HANDLE_SNAPSHOT_INFORMATION;

typedef struct _SYSTEM_PROCESS_INFORMATION {
	ULONG NextEntryOffset;  // Next struct offset, the last offset is 0.
	ULONG NumberOfThreads;
	LARGE_INTEGER SpareLi1;
	LARGE_INTEGER SpareLi2;
	LARGE_INTEGER SpareLi3;
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER KernelTime;
	UNICODE_STRING ImageName;  // Process name
	LONG BasePriority;
	HANDLE UniqueProcessId;               // Process id
	HANDLE InheritedFromUniqueProcessId;  // Parent process id
	ULONG HandleCount;
	ULONG SessionId;  // Session ID
	ULONG_PTR PageDirectoryBase;
	SIZE_T PeakVirtualSize;
	SIZE_T VirtualSize;
	ULONG PageFaultCount;
	SIZE_T PeakWorkingSetSize;
	SIZE_T WorkingSetSize;
	SIZE_T QuotaPeakPagedPoolUsage;
	SIZE_T QuotaPagedPoolUsage;
	SIZE_T QuotaPeakNonPagedPoolUsage;
	SIZE_T QuotaNonPagedPoolUsage;
	SIZE_T PagefileUsage;
	SIZE_T PeakPagefileUsage;
	SIZE_T PrivatePageCount;
	LARGE_INTEGER ReadOperationCount;
	LARGE_INTEGER WriteOperationCount;
	LARGE_INTEGER OtherOperationCount;
	LARGE_INTEGER ReadTransferCount;
	LARGE_INTEGER WriteTransferCount;
	LARGE_INTEGER OtherTransferCount;
} SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;

typedef struct _RTL_PROCESS_MODULE_INFORMATION {
	HANDLE Section;
	PVOID MappedBase;
	PVOID ImageBase;
	ULONG ImageSize;
	ULONG Flags;
	USHORT LoadOrderIndex;
	USHORT InitOrderIndex;
	USHORT LoadCount;
	USHORT OffsetToFileName;
	UCHAR Name[MAXIMUM_FILENAME_LENGTH];
} RTL_PROCESS_MODULE_INFORMATION, *PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _RTL_PROCESS_MODULES {
	ULONG ModuleCount;
	RTL_PROCESS_MODULE_INFORMATION Module[1];    
}RTL_PROCESS_MODULES,*PRTL_PROCESS_MODULES;

typedef struct _RTL_PROCESS_MODULE_INFORMATION_EX
{
	USHORT NextOffset;
	RTL_PROCESS_MODULE_INFORMATION BaseInfo;
	ULONG ImageChecksum;
	ULONG TimeDateStamp;
	PVOID DefaultBase;
} RTL_PROCESS_MODULE_INFORMATION_EX, *PRTL_PROCESS_MODULE_INFORMATION_EX;

typedef struct _SYSTEM_EXCEPTION_INFORMATION {
	ULONG AlignmentFixupCount;
	ULONG ExceptionDispatchCount;
	ULONG FloatingEmulationCount;
	ULONG ByteWordEmulationCount;
} SYSTEM_EXCEPTION_INFORMATION, *PSYSTEM_EXCEPTION_INFORMATION;

typedef struct _SYSTEM_SERVICE_DESCRIPTOR_TABLE {
	PULONG_PTR ServiceTableBase;
	PULONG ServiceCounterTableBase;
	ULONG_PTR NumberOfServices;
	PUCHAR ParamTableBase;
} SYSTEM_SERVICE_DESCRIPTOR_TABLE, *PSYSTEM_SERVICE_DESCRIPTOR_TABLE;

typedef struct _SYSTEMTIME {
	USHORT wYear;
	USHORT wMonth;
	USHORT wDayOfWeek;
	USHORT wDay;
	USHORT wHour;
	USHORT wMinute;
	USHORT wSecond;
	USHORT wMilliseconds;
} SYSTEMTIME;

typedef struct _OBJECT_DIRECTORY_INFORMATION {
	UNICODE_STRING Name;
	UNICODE_STRING TypeName;
} OBJECT_DIRECTORY_INFORMATION, *POBJECT_DIRECTORY_INFORMATION;

typedef struct _SYSTEM_BIGPOOL_ENTRY
{
	union {
		PVOID VirtualAddress;
		ULONG_PTR NonPaged : 1;
	};
	ULONG_PTR SizeInBytes;
	union {
		UCHAR Tag[4];
		ULONG TagUlong;
	};
} SYSTEM_BIGPOOL_ENTRY, *PSYSTEM_BIGPOOL_ENTRY;

typedef struct _SYSTEM_BIGPOOL_INFORMATION {
	ULONG Count;
	SYSTEM_BIGPOOL_ENTRY AllocatedInfo[1];
} SYSTEM_BIGPOOL_INFORMATION, *PSYSTEM_BIGPOOL_INFORMATION;

//
// This is the maximum MaximumLength for a UNICODE_STRING.
//
#define MAX_USTRING (sizeof(WCHAR) * (MAXUSHORT / sizeof(WCHAR)))

typedef struct _EXHANDLE
{
    union
    {
        struct
        {
            ULONG TagBits:2;
            ULONG Index:30;
        };
        VOID* GenericHandleOverlay;
        ULONG_PTR Value;
    };
} EXHANDLE, *PEXHANDLE; 

typedef struct _HANDLE_TABLE_ENTRY
{
    union
    {
        PVOID Object;
        ULONG ObAttributes;
        ULONG_PTR Value;
    };
    union
    {
        ACCESS_MASK GrantedAccess;
        LONG NextFreeTableEntry;
    };
} HANDLE_TABLE_ENTRY, *PHANDLE_TABLE_ENTRY;

#if defined(_M_AMD64) || defined(_WIN64)
//0x8 bytes (sizeof)
struct _EX_PUSH_LOCK
{
    union
    {
        struct
        {
            ULONGLONG Locked:1;                                             //0x0
            ULONGLONG Waiting:1;                                            //0x0
            ULONGLONG Waking:1;                                             //0x0
            ULONGLONG MultipleShared:1;                                     //0x0
            ULONGLONG Shared:60;                                            //0x0
        };
        ULONGLONG Value;                                                    //0x0
        VOID* Ptr;                                                          //0x0
    };
}; 
#else
//0x4 bytes (sizeof)
struct _EX_PUSH_LOCK
{
    union
    {
        struct
        {
            ULONG Locked:1;                                                 //0x0
            ULONG Waiting:1;                                                //0x0
            ULONG Waking:1;                                                 //0x0
            ULONG MultipleShared:1;                                         //0x0
            ULONG Shared:28;                                                //0x0
        };
        ULONG Value;                                                        //0x0
        VOID* Ptr;                                                          //0x0
    };
}; 
#endif

typedef struct _EX_PUSH_LOCK_WAIT_BLOCK *PEX_PUSH_LOCK_WAIT_BLOCK;
typedef struct _HANDLE_TABLE HANDLE_TABLE, *PHANDLE_TABLE;

//
// Fast reference routines. See (WRK) ntos\ob\fastref.c for algorithm description.
//
#if defined (_WIN64)
#define MAX_FAST_REFS 15
#else
#define MAX_FAST_REFS 7
#endif

typedef struct _EX_CALLBACK_ROUTINE_BLOCK {
    EX_RUNDOWN_REF RundownProtect;
    PEX_CALLBACK_FUNCTION Function;
    PVOID Context;
} EX_CALLBACK_ROUTINE_BLOCK, *PEX_CALLBACK_ROUTINE_BLOCK;

typedef struct _EX_FAST_REF {
    union {
        PVOID Object;
#if defined(_WIN64)
        ULONG_PTR RefCnt : 4;
#else
        ULONG_PTR RefCnt : 3;
#endif
        ULONG_PTR Value;
    };
} EX_FAST_REF, *PEX_FAST_REF;

typedef struct _EX_CALLBACK {
    EX_FAST_REF RoutineBlock;
} EX_CALLBACK, *PEX_CALLBACK;

typedef struct _OB_CALLBACK_ENTRY {
    USHORT Version;
    USHORT Count;
    CHAR Padding1[4];
    POB_OPERATION_REGISTRATION RegistrationContext;
    UNICODE_STRING Altitude;
    CHAR ObCallbackEntries[1];  // There is actually an array of OB_CALLBACK_ENTRY_ITEM that are also
                                // in a doubly linked list
} OB_CALLBACK_ENTRY, *POB_CALLBACK_ENTRY;

typedef struct _OB_CALLBACK_ENTRY_ITEM {
    LIST_ENTRY EntryItemList;
    OB_OPERATION Operations;
    OB_CALLBACK_ENTRY* CallbackEntry;  // Points to the CALLBACK_ENTRY which we use for ObUnRegisterCallback
    POBJECT_TYPE ObjectType;
    POB_PRE_OPERATION_CALLBACK PreOperation;
    POB_POST_OPERATION_CALLBACK PostOperation;
    INT64 Unknown;
} OB_CALLBACK_ENTRY_ITEM, *POB_CALLBACK_ENTRY_ITEM;

typedef enum _MI_VAD_TYPE {
    VadNone,
    VadDevicePhysicalMemory,
    VadImageMap,
    VadAwe,
    VadWriteWatch,
    VadLargePages,
    VadRotatePhysical,
    VadLargePageSection
} MI_VAD_TYPE, *PMI_VAD_TYPE;

//
// PTE protection values
//
#define MM_ZERO_ACCESS         0
#define MM_READONLY            1
#define MM_EXECUTE             2
#define MM_EXECUTE_READ        3
#define MM_READWRITE           4
#define MM_WRITECOPY           5
#define MM_EXECUTE_READWRITE   6
#define MM_EXECUTE_WRITECOPY   7

#define MM_PTE_VALID_MASK         0x1
#define MM_PTE_WRITE_MASK         0x800
#define MM_PTE_OWNER_MASK         0x4
#define MM_PTE_WRITE_THROUGH_MASK 0x8
#define MM_PTE_CACHE_DISABLE_MASK 0x10
#define MM_PTE_ACCESS_MASK        0x20
#define MM_PTE_DIRTY_MASK         0x42
#define MM_PTE_LARGE_PAGE_MASK    0x80
#define MM_PTE_GLOBAL_MASK        0x100
#define MM_PTE_COPY_ON_WRITE_MASK 0x200
#define MM_PTE_PROTOTYPE_MASK     0x400
#define MM_PTE_TRANSITION_MASK    0x800

#define VIRTUAL_ADDRESS_BITS 48
#define VIRTUAL_ADDRESS_MASK ((((ULONG_PTR)1) << VIRTUAL_ADDRESS_BITS) - 1)

typedef struct _CONTROL_AREA // Size=120
{
    PVOID Segment;
    struct _LIST_ENTRY ListHead;
    unsigned __int64 NumberOfSectionReferences;
    unsigned __int64 NumberOfPfnReferences; 
    unsigned __int64 NumberOfMappedViews;
    unsigned __int64 NumberOfUserReferences;
    unsigned long f1; 
    unsigned long f2;
    EX_FAST_REF FilePointer;
    // Other fields
} CONTROL_AREA, *PCONTROL_AREA;

typedef struct _SUBSECTION // Size=56
{
    PCONTROL_AREA ControlArea;
    // Other fields
} SUBSECTION, *PSUBSECTION;

typedef union _WSL_CREATE_NOTIFY_INFO_FLAGS {
    ULONG Flags;
    struct {
        ULONG FileOpenNameAvailable : 1;
        ULONG IsSubSystemProcess : 1; // new for WSL
        ULONG Reserved : 30;
    };
} WSL_CREATE_NOTIFY_INFO_FLAGS;

//0x10 bytes (sizeof)
struct _OBJECT_DUMP_CONTROL
{
	VOID* Stream;                                                           //0x0
	ULONG Detail;                                                           //0x8
}; 

//0x4 bytes (sizeof)
enum _OB_OPEN_REASON
{
	ObCreateHandle = 0,
	ObOpenHandle = 1,
	ObDuplicateHandle = 2,
	ObInheritHandle = 3,
	ObMaxOpenReason = 4
}; 

//0x70 bytes (sizeof)
typedef struct _OBJECT_TYPE_INITIALIZER_Win7
{
    USHORT Length;                                                          //0x0
    union
    {
        UCHAR ObjectTypeFlags;                                              //0x2
        struct
        {
            UCHAR CaseInsensitive:1;                                        //0x2
            UCHAR UnnamedObjectsOnly:1;                                     //0x2
            UCHAR UseDefaultObject:1;                                       //0x2
            UCHAR SecurityRequired:1;                                       //0x2
            UCHAR MaintainHandleCount:1;                                    //0x2
            UCHAR MaintainTypeList:1;                                       //0x2
            UCHAR SupportsObjectCallbacks:1;                                //0x2
        };
    };
    ULONG ObjectTypeCode;                                                   //0x4
    ULONG InvalidAttributes;                                                //0x8
    struct _GENERIC_MAPPING GenericMapping;                                 //0xc
    ULONG ValidAccessMask;                                                  //0x1c
    ULONG RetainAccess;                                                     //0x20
    enum _POOL_TYPE PoolType;                                               //0x24
    ULONG DefaultPagedPoolCharge;                                           //0x28
    ULONG DefaultNonPagedPoolCharge;                                        //0x2c
    VOID (*DumpProcedure)(VOID* arg1, struct _OBJECT_DUMP_CONTROL* arg2);   //0x30
    LONG (*OpenProcedure)(enum _OB_OPEN_REASON arg1, CHAR arg2, PEPROCESS arg3, VOID* arg4, ULONG* arg5, ULONG arg6); //0x38
    VOID (*CloseProcedure)(PEPROCESS arg1, VOID* arg2, ULONGLONG arg3, ULONGLONG arg4); //0x40
    VOID (*DeleteProcedure)(VOID* arg1);                                    //0x48
    LONG (*ParseProcedure)(VOID* arg1, VOID* arg2, struct _ACCESS_STATE* arg3, CHAR arg4, ULONG arg5, struct _UNICODE_STRING* arg6, struct _UNICODE_STRING* arg7, VOID* arg8, struct _SECURITY_QUALITY_OF_SERVICE* arg9, VOID** arg10); //0x50
    LONG (*SecurityProcedure)(VOID* arg1, enum _SECURITY_OPERATION_CODE arg2, ULONG* arg3, VOID* arg4, ULONG* arg5, VOID** arg6, enum _POOL_TYPE arg7, struct _GENERIC_MAPPING* arg8, CHAR arg9); //0x58
    LONG (*QueryNameProcedure)(VOID* arg1, UCHAR arg2, struct _OBJECT_NAME_INFORMATION* arg3, ULONG arg4, ULONG* arg5, CHAR arg6); //0x60
    UCHAR (*OkayToCloseProcedure)(PEPROCESS arg1, VOID* arg2, VOID* arg3, CHAR arg4); //0x68
} OBJECT_TYPE_INITIALIZER_Win7, *POBJECT_TYPE_INITIALIZER_Win7; 

//0x78 bytes (sizeof)
typedef struct _OBJECT_TYPE_INITIALIZER_Win8
{
    USHORT Length;                                                          //0x0
    union
    {
        UCHAR ObjectTypeFlags;                                              //0x2
        struct
        {
            UCHAR CaseInsensitive:1;                                        //0x2
            UCHAR UnnamedObjectsOnly:1;                                     //0x2
            UCHAR UseDefaultObject:1;                                       //0x2
            UCHAR SecurityRequired:1;                                       //0x2
            UCHAR MaintainHandleCount:1;                                    //0x2
            UCHAR MaintainTypeList:1;                                       //0x2
            UCHAR SupportsObjectCallbacks:1;                                //0x2
            UCHAR CacheAligned:1;                                           //0x2
        };
    };
    ULONG ObjectTypeCode;                                                   //0x4
    ULONG InvalidAttributes;                                                //0x8
    struct _GENERIC_MAPPING GenericMapping;                                 //0xc
    ULONG ValidAccessMask;                                                  //0x1c
    ULONG RetainAccess;                                                     //0x20
    enum _POOL_TYPE PoolType;                                               //0x24
    ULONG DefaultPagedPoolCharge;                                           //0x28
    ULONG DefaultNonPagedPoolCharge;                                        //0x2c
    VOID (*DumpProcedure)(VOID* arg1, struct _OBJECT_DUMP_CONTROL* arg2);   //0x30
    LONG (*OpenProcedure)(enum _OB_OPEN_REASON arg1, CHAR arg2, PEPROCESS arg3, VOID* arg4, ULONG* arg5, ULONG arg6); //0x38
    VOID (*CloseProcedure)(PEPROCESS arg1, VOID* arg2, ULONGLONG arg3, ULONGLONG arg4); //0x40
    VOID (*DeleteProcedure)(VOID* arg1);                                    //0x48
    LONG (*ParseProcedure)(VOID* arg1, VOID* arg2, struct _ACCESS_STATE* arg3, CHAR arg4, ULONG arg5, struct _UNICODE_STRING* arg6, struct _UNICODE_STRING* arg7, VOID* arg8, struct _SECURITY_QUALITY_OF_SERVICE* arg9, VOID** arg10); //0x50
    LONG (*SecurityProcedure)(VOID* arg1, enum _SECURITY_OPERATION_CODE arg2, ULONG* arg3, VOID* arg4, ULONG* arg5, VOID** arg6, enum _POOL_TYPE arg7, struct _GENERIC_MAPPING* arg8, CHAR arg9); //0x58
    LONG (*QueryNameProcedure)(VOID* arg1, UCHAR arg2, struct _OBJECT_NAME_INFORMATION* arg3, ULONG arg4, ULONG* arg5, CHAR arg6); //0x60
    UCHAR (*OkayToCloseProcedure)(PEPROCESS arg1, VOID* arg2, VOID* arg3, CHAR arg4); //0x68
    ULONG WaitObjectFlagMask;                                               //0x70
    USHORT WaitObjectFlagOffset;                                            //0x74
    USHORT WaitObjectPointerOffset;                                         //0x76
} OBJECT_TYPE_INITIALIZER, *POBJECT_TYPE_INITIALIZER;

// struct of x86 and x64 is equal
typedef struct _OBJECT_TYPE_Win7
{
    struct _LIST_ENTRY TypeList;                                            
    struct _UNICODE_STRING Name;                                            
    VOID* DefaultObject;                                                    
    UCHAR Index;                                                            
    ULONG TotalNumberOfObjects;                                             
    ULONG TotalNumberOfHandles;                                             
    ULONG HighWaterNumberOfObjects;                                         
    ULONG HighWaterNumberOfHandles;                                         
    struct _OBJECT_TYPE_INITIALIZER_Win7 TypeInfo;                          
    EX_PUSH_LOCK TypeLock;                                                  
    ULONG Key;                                                              
    struct _LIST_ENTRY CallbackList;                                        
} OBJECT_TYPE_Win7, *POBJECT_TYPE_Win7; 

typedef struct _OBJECT_TYPE_Win8
{
    struct _LIST_ENTRY TypeList;                                            
    struct _UNICODE_STRING Name;                                            
    VOID* DefaultObject;                                                    
    UCHAR Index;                                                            
    ULONG TotalNumberOfObjects;                                             
    ULONG TotalNumberOfHandles;                                             
    ULONG HighWaterNumberOfObjects;                                         
    ULONG HighWaterNumberOfHandles;                                         
    struct _OBJECT_TYPE_INITIALIZER_Win8 TypeInfo;                          
    EX_PUSH_LOCK TypeLock;                                                  
    ULONG Key;                                                              
    struct _LIST_ENTRY CallbackList;                                        
} OBJECT_TYPE_Win8, *POBJECT_TYPE_Win8;

//0x40 bytes (sizeof)
struct _OBJECT_CREATE_INFORMATION
{
	ULONG Attributes;                                                       //0x0
	VOID* RootDirectory;                                                    //0x8
	CHAR ProbeMode;                                                         //0x10
	ULONG PagedPoolCharge;                                                  //0x14
	ULONG NonPagedPoolCharge;                                               //0x18
	ULONG SecurityDescriptorCharge;                                         //0x1c
	VOID* SecurityDescriptor;                                               //0x20
	struct _SECURITY_QUALITY_OF_SERVICE* SecurityQos;                       //0x28
	struct _SECURITY_QUALITY_OF_SERVICE SecurityQualityOfService;           //0x30
}; 

//0x38 bytes (sizeof)
// Win7 or Later
typedef struct _OBJECT_HEADER
{
	LONGLONG PointerCount;                                                  //0x0
	union
	{
		LONGLONG HandleCount;                                               //0x8
		VOID* NextToFree;                                                   //0x8
	};
	struct _EX_PUSH_LOCK Lock;                                              //0x10
	UCHAR TypeIndex;                                                        //0x18
	union
	{
		UCHAR TraceFlags;                                                   //0x19
		struct
		{
			UCHAR DbgRefTrace:1;                                            //0x19
			UCHAR DbgTracePermanent:1;                                      //0x19
		};
	};
	UCHAR InfoMask;                                                         //0x1a
	union
	{
		UCHAR Flags;                                                        //0x1b
		struct
		{
			UCHAR NewObject:1;                                              //0x1b
			UCHAR KernelObject:1;                                           //0x1b
			UCHAR KernelOnlyAccess:1;                                       //0x1b
			UCHAR ExclusiveObject:1;                                        //0x1b
			UCHAR PermanentObject:1;                                        //0x1b
			UCHAR DefaultSecurityQuota:1;                                   //0x1b
			UCHAR SingleHandleEntry:1;                                      //0x1b
			UCHAR DeletedInline:1;                                          //0x1b
		};
	};
	ULONG Reserved;                                                         //0x1c
	union
	{
		struct _OBJECT_CREATE_INFORMATION* ObjectCreateInfo;                //0x20
		VOID* QuotaBlockCharged;                                            //0x20
	};
	VOID* SecurityDescriptor;                                               //0x28
	struct _QUAD Body;                                                      //0x30
} OBJECT_HEADER;

//0x150 bytes (sizeof)
struct _OBJECT_DIRECTORY_Win7
{
	struct _OBJECT_DIRECTORY_ENTRY* HashBuckets[37];                        //0x0
	struct _EX_PUSH_LOCK Lock;                                              //0x128
	PVOID DeviceMap;                                                        //0x130
	ULONG SessionId;                                                        //0x138
	VOID* NamespaceEntry;                                                   //0x140
	ULONG Flags;                                                            //0x148
}; 

//0x150 bytes (sizeof)
typedef struct _OBJECT_DIRECTORY_Win8
{
    struct _OBJECT_DIRECTORY_ENTRY* HashBuckets[37];                        //0x0
    struct _EX_PUSH_LOCK Lock;                                              //0x128
    union
    {
        PVOID DeviceMap;                                                    //0x130
        struct OBJECT_DIRECTORY_Win8* ShadowDirectory;                      //0x130
    };
    ULONG SessionId;                                                        //0x138
    VOID* NamespaceEntry;                                                   //0x140
    ULONG Flags;                                                            //0x148
} OBJECT_DIRECTORY_Win8;

//0x158 bytes (sizeof)
typedef struct _OBJECT_DIRECTORY_Win10
{
    struct _OBJECT_DIRECTORY_ENTRY* HashBuckets[37];                        //0x0
    struct _EX_PUSH_LOCK Lock;                                              //0x128
    PVOID DeviceMap;                                                        //0x130
    struct OBJECT_DIRECTORY_Win10* ShadowDirectory;                         //0x138
    VOID* NamespaceEntry;                                                   //0x140
    VOID* SessionObject;                                                    //0x148
    ULONG Flags;                                                            //0x150
    ULONG SessionId;                                                        //0x154
} OBJECT_DIRECTORY_Win10; 

//0x18 bytes (sizeof)
typedef struct _OBJECT_DIRECTORY_ENTRY
{
    struct _OBJECT_DIRECTORY_ENTRY* ChainLink;                              //0x0
    VOID* Object;                                                           //0x8
    ULONG HashValue;                                                        //0x10
} OBJECT_DIRECTORY_ENTRY, *POBJECT_DIRECTORY_ENTRY; 

/*
 * LPC Structs BEGIN
 */

typedef enum _LPC_TYPE {
    LPC_TYPE_NEW_MESSAGE = 0,    // A new message
    LPC_TYPE_REQUEST,            // A request message (NtRequestWaitReplyPort)
    LPC_TYPE_REPLY,              // A reply to a request message
    LPC_TYPE_DATAGRAM,           // NtRequestPort
    LPC_TYPE_LOST_REPLY,         //
    LPC_TYPE_PORT_CLOSED,        // Sent when port is deleted
    LPC_TYPE_CLIENT_DIED,        // Messages to thread termination ports
    LPC_TYPE_EXCEPTION,          // Messages to thread exception port
    LPC_TYPE_DEBUG_EVENT,        // Messages to thread debug port
    LPC_TYPE_ERROR_EVENT,        // Used by ZwRaiseHardError
    LPC_TYPE_CONNECTION_REQUEST  // Used by ZwConnectPort
} LPC_TYPE;

#pragma pack(push, 8)
typedef struct _PORT_VIEW {
    ULONG Length;          // Size of this structure
    HANDLE SectionHandle;  // Handle to section object with
    // SECTION_MAP_WRITE and SECTION_MAP_READ
    ULONG SectionOffset;  // The offset in the section to map a view for

    // the port data area. The offset must be aligned
    // with the allocation granularity of the system.
    ULONGLONG ViewSize;  // The size of the view (in bytes)
    PVOID ViewBase;      // The base address of the view in the creator
    //
    PVOID ViewRemoteBase;  // The base address of the view in the process
                           // connected to the port.
} PORT_VIEW, *PPORT_VIEW;
#pragma pack(pop)

#pragma pack(push, 8)
typedef struct _REMOTE_PORT_VIEW {
    ULONG Length;        // Size of this structure
    ULONGLONG ViewSize;  // The size of the view (bytes)
    PVOID ViewBase;      // Base address of the view
} REMOTE_PORT_VIEW, *PREMOTE_PORT_VIEW;
#pragma pack(pop)

#pragma pack(push, 8)
typedef struct _PORT_MESSAGE {
    union {
        struct {
            SHORT DataLength;   // Length of data following header (bytes)
            SHORT TotalLength;  // Length of data + sizeof(PORT_MESSAGE)
        } s1;
        ULONG Length;
    } u1;
    union {
        struct {
            SHORT Type;            // // Type of the message (LPC_TYPE)
            SHORT DataInfoOffset;  // Offset of array of virtual address ranges
        } s2;
        ULONG ZeroInit;
    } u2;
    union {
        CLIENT_ID ClientId;  // Client identifier of the message sender
        QUAD DoNotUseThisField;
    };
    ULONG MessageId;  // Identifier of the particular message instance
    union {
        ULONGLONG ClientViewSize;  // only valid for LPC_CONNECTION_REQUEST messages
        ULONG CallbackId;          // only valid for LPC_REQUEST messages
    };
} PORT_MESSAGE, *PPORT_MESSAGE;
#pragma pack(pop)

#define IS_INTRESOURCE(_r) ((((ULONG_PTR)(_r)) >> 16) == 0)
#define MAKEINTRESOURCEA(i) ((LPSTR)((ULONG_PTR)((WORD)(i))))
#define MAKEINTRESOURCEW(i) ((LPWSTR)((ULONG_PTR)((WORD)(i))))
#ifdef UNICODE
#define MAKEINTRESOURCE  MAKEINTRESOURCEW
#else
#define MAKEINTRESOURCE  MAKEINTRESOURCEA
#endif // !UNICODE

#define RT_VERSION MAKEINTRESOURCE(16)

typedef struct tagVS_FIXEDFILEINFO {
  DWORD dwSignature;
  DWORD dwStrucVersion;
  DWORD dwFileVersionMS;
  DWORD dwFileVersionLS;
  DWORD dwProductVersionMS;
  DWORD dwProductVersionLS;
  DWORD dwFileFlagsMask;
  DWORD dwFileFlags;
  DWORD dwFileOS;
  DWORD dwFileType;
  DWORD dwFileSubtype;
  DWORD dwFileDateMS;
  DWORD dwFileDateLS;
} VS_FIXEDFILEINFO;

/*
 * LPC Structs END
 */

/*
 * Windows Internal
 */
#define ASSERT_WELL_FORMED_UNICODE_STRING(Str) \
    NT_ASSERT((!(((Str)->Length & 1) || ((Str)->MaximumLength & 1))) && ((Str)->Length <= (Str)->MaximumLength))

#define ASSERT_WELL_FORMED_UNICODE_STRING_IN(Str) NT_ASSERT(!((Str)->Length & 1))

#define ASSERT_WELL_FORMED_UNICODE_STRING_OUT(Str) \
    NT_ASSERT((!((Str)->MaximumLength & 1)) && ((Str)->Length <= (Str)->MaximumLength))

// clang-format on

#endif // _H_SYSTEMDEFINE_
