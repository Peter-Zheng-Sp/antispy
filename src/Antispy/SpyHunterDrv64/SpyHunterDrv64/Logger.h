#ifndef _H_LOGGER_
#define _H_LOGGER_

#include <ntifs.h>

typedef enum _DBGLEVEL
{
	LEVEL_FATAL = 0x1,
	LEVEL_ERROR = 0x2,
	LEVEL_WARNING = 0x3,
	LEVEL_IMPORTANT = 0x4,
	LEVEL_NOTIFY = 0x5,
	LEVEL_DEBUG = 0x6,
	LEVEL_INFO = 0x7,
	LEVEL_MAX
} DBGLEVEL;

#ifdef DBG
#define KLOG_TAG L"SHDrv64(Debug): "
#else
#define KLOG_TAG L"SHDrv64(Free): "
#define KLOG_WITH_TIME
#endif

void Logger_LogIt(LPCSTR func, ULONG line, DBGLEVEL level, LPCWSTR format, ...);

#define _DBPRINT(level, ...) Logger_LogIt(__FUNCTION__, __LINE__, level, __VA_ARGS__)

#ifdef DBG

#define LOG_INFO(__str__, ...) _DBPRINT(LEVEL_INFO, KLOG_TAG __str__, __VA_ARGS__)

#define LOG_DEBUG(__str__, ...) _DBPRINT(LEVEL_DEBUG, KLOG_TAG __str__, __VA_ARGS__)

#define LOG_NOTIFY(__str__, ...) _DBPRINT(LEVEL_NOTIFY, KLOG_TAG __str__, __VA_ARGS__)

#define LOG_IMPORTANT(__str__, ...) _DBPRINT(LEVEL_IMPORTANT, KLOG_TAG __str__, __VA_ARGS__)

#define LOG_WARNING(__str__, ...) _DBPRINT(LEVEL_WARNING, KLOG_TAG __str__, __VA_ARGS__)

#else

#define LOG_INFO(__str__, ...)

#define LOG_DEBUG(__str__, ...)

#define LOG_NOTIFY(__str__, ...)

#define LOG_IMPORTANT(__str__, ...)

#define LOG_WARNING(__str__, ...)

#endif

#define LOG_ERROR(__str__, ...) _DBPRINT(LEVEL_ERROR, VCRYPTW(KLOG_TAG __str__), __VA_ARGS__)

#define LOG_FATAL(__str__, ...) _DBPRINT(LEVEL_FATAL, VCRYPTW(KLOG_TAG __str__), __VA_ARGS__)

#endif // _H_LOGGER_
