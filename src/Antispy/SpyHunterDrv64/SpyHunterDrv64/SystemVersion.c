#include "Stdafx.h"
#include "SystemVersion.h"

BOOLEAN SystemVersion_IsOsServerVersion(OSVERSIONINFOEXW OsInfo)
{
	return OsInfo.wProductType != VER_NT_WORKSTATION;
}

NTOS_VERSION SystemVersion_ParseOsInfo2InternalVersion(OSVERSIONINFOEXW OsInfo)
{
	NTOS_VERSION WinVersion = WINDOWS_NONE;

	if (OsInfo.dwMajorVersion == 5 && OsInfo.dwMinorVersion == 1 && OsInfo.dwBuildNumber == 2600) {
		WinVersion = WINDOWS_XP_SP3;
		return WinVersion;
	}

	if (OsInfo.dwMajorVersion == 5 && OsInfo.dwMinorVersion == 2 && OsInfo.dwBuildNumber == 3790) {
		WinVersion = WINDOWS_2K3_SP2;
		return WinVersion;
	}

	if (OsInfo.dwMajorVersion == 6 && OsInfo.dwMinorVersion == 0) {
		switch (OsInfo.dwBuildNumber) {
		case 6000:
			WinVersion = WINDOWS_VISTA_2008_RTM;
			break;
		case 6001:
			WinVersion = WINDOWS_VISTA_2008_SP1;
			break;
		case 6002:
			WinVersion = WINDOWS_VISTA_2008_SP2;
			break;
		default:
			break;
		}
		return WinVersion;
	}

	if (OsInfo.dwMajorVersion == 6 && OsInfo.dwMinorVersion == 1) {
		switch (OsInfo.dwBuildNumber) {
		case 7600:
			WinVersion = WINDOWS_7_2008R2_RTM;
			break;
		case 7601:
			WinVersion = WINDOWS_7_2008R2_SP1;
			break;
		default:
			break;
		}
		return WinVersion;
	}

	if (OsInfo.dwMajorVersion == 6 && OsInfo.dwMinorVersion == 2 && OsInfo.dwBuildNumber == 9200) {
		WinVersion = WINDOWS_8_2012_RTM;
		return WinVersion;
	}

	if (OsInfo.dwMajorVersion == 6 && OsInfo.dwMinorVersion == 3 && OsInfo.dwBuildNumber == 9600) {
		switch (OsInfo.wServicePackMajor) {
		case 0:
			WinVersion = WINDOWS_81_2012R2;
			break;
		case 1:
			WinVersion = WINDOWS_81_2012R2_SP1;
			break;
		default:
			break;
		}
		return WinVersion;
	}

	if (OsInfo.dwMajorVersion == 10 && OsInfo.dwMinorVersion == 0) {
		switch (OsInfo.dwBuildNumber) {
		case 10240:
			WinVersion = WINDOWS_10_TH1;
			break;
		case 10586:
			WinVersion = WINDOWS_10_TH2;
			break;
		case 14393:
			WinVersion = WINDOWS_10_RS1;
			break;
		case 15063:
			WinVersion = WINDOWS_10_RS2;
			break;
		case 16299:
			WinVersion = WINDOWS_10_RS3;
			break;
		case 17134:
			WinVersion = WINDOWS_10_RS4;
			break;
		case 17763:
			WinVersion = WINDOWS_10_RS5;
			break;
		case 18362:
			WinVersion = WINDOWS_10_19H1;
			break;
		case 18363:
			WinVersion = WINDOWS_10_19H2;
			break;
		case 19041:
			WinVersion = WINDOWS_10_20H1;
			break;
		case 19042:
			WinVersion = WINDOWS_10_20H2;
			break;
		case 19043:
			WinVersion = WINDOWS_10_21H1;
			break;
		case 19044:
			WinVersion = WINDOWS_10_21H2;
			break;
		case 19045:
			WinVersion = WINDOWS_10_22H2;
			break;
		case 22000:
			WinVersion = WINDOWS_11_21H2;
			break;
		case 22621:
			WinVersion = WINDOWS_11_22H2;
			break;
		case 22631:
			WinVersion = WINDOWS_11_23h2;
			break;
		default:
			break;
		}
	}

	return WinVersion;
}
