#include "log.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "LogFile.h"

#ifdef ANDROID
#include <android/log.h>
#endif

/*
#define AHS_DEBUG(file, fmt, ...)					\
{FILE *fp = fopen(file, "a+");					\
	if (fp)											\
{												\
	fprintf(fp, fmt, __VA_ARGS__);				\
	fprintf(fp, " %u\n", timeGetTime());		\
	fclose(fp);									\
}}
*/

#define MAX_BUF_SIZE 2048
static int s_logLevel = kLogDebug;
static YYLogNativeHandler s_logCallBack = NULL;
static bool s_bOpen = true;

static const char* s_levelString[] = {
		"T/",
		"D/",
		"I/",
		"W/",
		"E/",
		"A/"
};

#ifdef ANDROID
static const int s_androidLogLevel[] = {
		ANDROID_LOG_VERBOSE,
		ANDROID_LOG_DEBUG,
		ANDROID_LOG_INFO,
		ANDROID_LOG_WARN,
		ANDROID_LOG_ERROR,
		ANDROID_LOG_FATAL
};
#endif

void SetLogLevel(int nLevel)
{
	s_logLevel = nLevel;
}

void SetYYLogInfo(bool bOpen, LogLevel level, const char* logPath, YYLogNativeHandler handler)
{
	s_bOpen = bOpen;
	s_logLevel = level;
	s_logCallBack = handler;
#ifdef DEBUG
	if (logPath != nullptr)
	{
		LogFile::Instance()->setLogPath(logPath);
	}
#else
	if (handler == nullptr && logPath != nullptr)
	{
		LogFile::Instance()->setLogPath(logPath);
	}
#endif
}

const char* GetMoudleString(LogModule module)
{
	switch (module)
	{
		case kLogPlatform:
			return "YYLiveSdk";
		case kLogAudio:
			return "YYLiveAudio";
		case kLogVideo:
			return "YYLiveVideo";
		case kLogTrans:
			return "YYLiveTrans";
		case kLogUnknown:
		default:
			return "YYLiveUnknown";
	}
}

void LogText(LogLevel level, LogModule module, const char* tag, const char *text)
{
	if (!s_bOpen)
	{
		return;
	}
	if ((level < s_logLevel))
	{
		return;
	}

	if (s_logCallBack)
	{
		s_logCallBack(level, module, text);
#ifdef DEBUG
		std::string msg = s_levelString[level];
		msg.append(tag);
		msg.append(" ");
		msg.append(text);
		LogFile::Instance()->log(msg);
#endif
	}
	else
	{
#ifdef ANDROID
		__android_log_print(s_androidLogLevel[level], GetMoudleString(module), "%s", text);
#endif
		std::string msg = s_levelString[level];
		msg.append(tag);
		msg.append(" ");
		msg.append(text);
		LogFile::Instance()->log(msg);
	}
}

#ifdef ANDROID
static int GetAndroidLogLevel(int level)
{
	switch (level)
	{
		case kLogTrace:
			return ANDROID_LOG_VERBOSE;
		case kLogDebug:
			return ANDROID_LOG_DEBUG;
		case kLogInfo:
			return ANDROID_LOG_INFO;
		case kLogWarning:
			return ANDROID_LOG_WARN;
		case kLogError:
			return ANDROID_LOG_ERROR;
		case kLogAssert:
			return ANDROID_LOG_FATAL;
		default:
			return ANDROID_LOG_UNKNOWN;
	}
}
#endif

void PlatLog(LogLevel level, LogModule module, const char *tag, const char *format, ...)
{
	if (!s_bOpen || level < s_logLevel)
	{
		return;
	}
    
    char buf[MAX_BUF_SIZE] = { 0 };
    va_list args;

	//format threadid.
	uint32_t uLen = 0;
#ifdef ANDROID
	snprintf(buf, 32, "[%u] [%s] ", (uint32_t)gettid(), tag ? tag : "unknown");
#else
//  int tid = syscall(SYS_gettid);//always return -1 in iOS
    int tid = -1;
	snprintf(buf, 32, "[%d] [%s] ", tid, tag ? tag : "unknown");
#endif
	uLen = (uint32_t)strlen(buf);

    va_start(args, format);
    vsnprintf((char*)(buf + uLen), (MAX_BUF_SIZE - 1 - uLen), format, args);
    va_end(args);
    
    buf[MAX_BUF_SIZE - 1] = 0;

	LogText(level, module, kLogTagSdk, buf);
}

void PlatAssertHelper(bool condition, const char *file, const char *func, const char *format, ...)
{
    if (condition)
        return;
    
    char buf[MAX_BUF_SIZE] = { 0 };
    snprintf(buf, MAX_BUF_SIZE - 1, "LibAssert : [%s] [%s], info: ", file, func);
	LogText(kLogAssert, kLogUnknown, "Assert", buf);

    va_list args;
    va_start(args, format);
    vsnprintf(buf, MAX_BUF_SIZE - 1, format, args);
    va_end(args);
    buf[MAX_BUF_SIZE - 1] = 0;
	LogText(kLogAssert, kLogUnknown, "Assert", buf);
}
