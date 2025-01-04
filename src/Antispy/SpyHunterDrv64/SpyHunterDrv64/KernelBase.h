#ifndef _H_KERNELBASE_
#define _H_KERNELBASE_


BOOLEAN  KernelBase_QueryKernelModuleInfoLDR(IN PUNICODE_STRING UnKernelName, OUT PULONG_PTR SystemKernelModuleBase, OUT PSIZE_T SystemKernelModuleSize);
BOOLEAN  KernelBase_QueryKernelModuleSizeLDR(IN ULONG_PTR SystemKernelModuleBase, OUT PSIZE_T SystemKernelModuleSize);
BOOLEAN  KernelBase_GetNtoskrnlInfo(OUT PUNICODE_STRING UnKernelName, OUT PULONG_PTR SystemKernelModuleBase, OUT PSIZE_T SystemKernelModuleSize);
NTSTATUS KernelBase_CheckKernelUpdate();

#endif // _H_KERNELBASE_
