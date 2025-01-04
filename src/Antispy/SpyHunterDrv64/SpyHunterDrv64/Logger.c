#include "Stdafx.h"
#include "Logger.h"

static const LPCWSTR kDbgLevelTable[] = {L"DEFAULT",   L"FATAL",  L"ERROR", L"WARNING", L"IMPORTANT", L"NOTIFY", L"DEBUG", L"INFO"};

#define DBG_OUTPUT_PREFIX ""
#define DBG_OUTPUT_LINE_BREAK "\r\n"

static const LPCWSTR kLogMainString = L"%ws%ws";

#ifdef LOG_WITH_TIME
static const LPCWSTR kLogPrefixFormat = L"%04d-%02d-%02d %02d:%02d:%02d [TID:%08X] %ws - LINE:%u - %ws -- ";
#else
static const LPCWSTR kLogPrefixFormat = L"[TID:%08X] %ws - LINE:%u - %ws -- ";
#endif

#define LOG_ITEM_MAX_LENGTH 0x800
#define LOG_PREFIX_BUFFER_MAX_LENGTH 0xff
#define LOG_CONTEXT_BUFFER_MAX_LENGTH ((LOG_ITEM_MAX_LENGTH) - (LOG_PREFIX_BUFFER_MAX_LENGTH))

static void DebugPrintImpl(__in PCSTR Format, ...)
{
	va_list arglist;
	va_start(arglist, Format);

	vDbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, (PSTR)Format, arglist);
}

static BOOLEAN CheckLogFormatSupportAPC(LPCWSTR sFormat)
{
	const WCHAR *pCur = NULL;

	// Find denied symbols
	for (pCur = sFormat; *pCur != 0; ++pCur)
	{
		if (*pCur != L'%')
			continue;
		switch (pCur[1])
		{
		case L'%':
			++pCur;
			break;
		case L'C':
		case L'S':
			return FALSE;
		case L'l':
		case L'w':
			if (pCur[2] == L'c' || pCur[2] == L's' || pCur[2] == L'Z')
				return FALSE;
			break;
		}
	}

	return TRUE;
}

void Logger_LogIt(LPCSTR func, ULONG line, DBGLEVEL level, LPCWSTR format, ...)
{
    ULONG ThreadId = HandleToUlong(PsGetCurrentThreadId());
    WCHAR LogBuffer[LOG_ITEM_MAX_LENGTH] = {0};
    WCHAR PrefixBuffer[LOG_PREFIX_BUFFER_MAX_LENGTH] = {0};
    WCHAR ContextBuffer[LOG_CONTEXT_BUFFER_MAX_LENGTH] = {0};
	WCHAR FunctionName[256] = {0};
    int PrefixLen = 0, ContextLen = 0, WrapperLen = 0;
    va_list args, args_cpy;

#ifdef KLOG_WITH_TIME
    LARGE_INTEGER utcTime = {0};
	TIME_FIELDS timeField = {0};
#endif

    // Logging work at IRQL <= APC_LEVEL
    if (KeGetCurrentIrql() > APC_LEVEL)
        return;

    // Special process for APC_LEVEL
    if (APC_LEVEL == KeGetCurrentIrql() && !CheckLogFormatSupportAPC(format))
        return;

#ifdef KLOG_WITH_TIME
    // Convert LARGE_INTEGER to a readable format (e.g., YYYY-MM-DD HH:MM:SS)
    KeQuerySystemTime(&utcTime);
    RtlTimeToTimeFields(&utcTime, &timeField);

    /**
     * Calculate Log Prefix Length and Filter or Assign it.
     */
    PrefixLen = _snwprintf(NULL, 0, kLogPrefixFormat, timeField.Year, timeField.Month, timeField.Day, timeField.Hour,
                           timeField.Minute, timeField.Day, ThreadId, func, line, kDbgLevelTable[level]);
    if (PrefixLen < 0 || (ULONG)PrefixLen >= LOG_PREFIX_BUFFER_MAX_LENGTH)
    {
        return;
    }

    PrefixLen = _snwprintf(PrefixBuffer, (size_t)PrefixLen + 1, kLogPrefixFormat, timeField.Year,
                           timeField.Month, timeField.Day, timeField.Hour, timeField.Minute, timeField.Day, ThreadId,
                           func, line, kDbgLevelTable[level]);
    if (PrefixLen < 0)
    {
        return;
    }
#else
	
    /**
     * Calculate Log Prefix Length and Filter or Assign it.
     */
	mbstowcs (FunctionName, func, _countof(FunctionName));
    PrefixLen = _snwprintf(NULL, 0, kLogPrefixFormat, ThreadId, FunctionName, line, kDbgLevelTable[level]);
    if (PrefixLen < 0 || (ULONG)PrefixLen >= LOG_PREFIX_BUFFER_MAX_LENGTH)
    {
        return;
    }

    PrefixLen = _snwprintf(PrefixBuffer, (size_t)PrefixLen + 1, kLogPrefixFormat, ThreadId, FunctionName, line,
                           kDbgLevelTable[level]);
    if (PrefixLen < 0)
    {
        return;
    }
#endif

    /*
     * Calculate Log Context Length and Filter or Assign it.
     */
    va_start(args, format);
    va_copy(args_cpy, args);

    ContextLen = _vsnwprintf(NULL, 0, format, args_cpy);
    if (ContextLen < 0 || (ULONG)ContextLen >= LOG_CONTEXT_BUFFER_MAX_LENGTH)
    {
        va_end(args_cpy);
        va_end(args);
        return;
    }

    va_end(args_cpy);

    ContextLen = _vsnwprintf(ContextBuffer, (size_t)ContextLen + 1, format, args);
    if (ContextLen < 0)
    {
        va_end(args);
        return;
    }

    va_end(args);

    /*
     * Processing Log Wrapper
     */
    WrapperLen = _snwprintf(NULL, 0, kLogMainString, PrefixBuffer, ContextBuffer);
    if (WrapperLen < 0 || WrapperLen >= LOG_ITEM_MAX_LENGTH)
    {
        return;
    }

    WrapperLen =
        _snwprintf(LogBuffer, (size_t)WrapperLen + 1, kLogMainString, PrefixBuffer, ContextBuffer);
    if (WrapperLen < 0)
    {
        return;
    }
	
    DebugPrintImpl(DBG_OUTPUT_PREFIX "%ws" DBG_OUTPUT_LINE_BREAK, LogBuffer);
}
