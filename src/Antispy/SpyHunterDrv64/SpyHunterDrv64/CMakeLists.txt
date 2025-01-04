SET(DDKPATH "C:/WinDDK/7600.16385.1")

add_executable(SpyHunterDrv64
        SpyHunterDrv.c
        SystemVersion.c
        GlobalData.c
        Logger.c
        Utility.c
        GlobalVariables.c
        MemoryAllocator.c
        KernelBase.c
)

target_include_directories(
	SpyHunterDrv64 PUBLIC
	"${DDKPATH}/inc/ddk"
	"${DDKPATH}/inc/api"
	"${DDKPATH}/inc/crt"
	"${DDKPATH}/inc/wdf/kmdf/1.9"
)

SET(CMAKE_C_STANDARD_LIBRARIES "ntoskrnl.lib hal.lib fltmgr.lib libcntpr.lib ntstrsafe.lib ksecdd.lib ndis.lib tdi.lib usbd.lib fltLib.lib wdmsec.lib rtlver.lib uuid.lib")
SET(CMAKE_CXX_STANDARD_LIBRARIES "ntoskrnl.lib hal.lib fltmgr.lib libcntpr.lib ntstrsafe.lib ksecdd.lib ndis.lib tdi.lib usbd.lib fltLib.lib wdmsec.lib rtlver.lib uuid.lib")

target_link_directories(
	SpyHunterDrv64 PUBLIC
	"${DDKPATH}/lib/win7/amd64"
)

add_definitions(
		-D_KERNEL_MODE
		-DPAGE_SIZE=8192
		-D_WIN64_=1
		-DSTD_CALL
		-DCONDITION_HANDLING=1
		-DNT_UP=1
		-DNT_INST=0
		-DWIN32=100
		-D_NT1X_=100
		-DWINNT=1
		-D_WIN32_WINNT=0x0600
		-DWINVER=0x0600
		-D_WIN32_IE=0x0700
		-DWIN32_LEAN_AND_MEAN=1
		-DDEVL=1
		-DDBG=1
		-D__BUILDMACHINE__=WinDDK
		-DFPO=0
		-DNDEBUG
		-DNTSTRSAFE_NO_DEPRECATE
		-DDDK_VER=7600
		-DNT_KERNEL_MODE
		-DDEPRECATE_DDK_FUNCTIONS=1
		-DMSC_NOOPT
		-DNTDDI_VERSION=0x06000100
		-DKMDF_MAJOR_VERSION_STRING=01
		-DKMDF_MINOR_VERSION_STRING=009
		-U_DLL
)

add_compile_options(
        -Zc:wchar_t-
        -Zl
        -Zp8
        -Gy
        -Gm-
        -cbstring
        -W3
        -Gz
        -hotpatch
        -EHa
        -GR
        -GF
        -GS
        -Zi
        -Od
        -Oi
        -Oy-
        -Zi
        -wd4603
        -wd4627
        -typedil-
        -FIC:/WinDDK/7600.16385.1/inc/api/warning.h
		-integritycheck
)
