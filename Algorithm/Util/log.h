#ifndef _LOG_H_
#define _LOG_H_

#pragma once
#include <stdio.h>
#include <string>

enum LogLevel
{
	kLogTrace = 0,
	kLogDebug,
	kLogInfo,
	kLogWarning,
	kLogError,
	kLogAssert,
};

enum LogModule
{
	kLogUnknown = 0,
	kLogPlatform = 100,
	kLogAudio = 101,
	kLogVideo = 102,
	kLogTrans = 103
};

#define kLogTagCall									"ycall"
#define kLogTagCallBack								"ycallback"
#define kLogTagThread								"ythread"
#define kLogTagPerf									"yperf"
#define kLogTagAudio								"yaudio"
#define kLogTagVideo								"yvideo"
#define kLogTagTrans								"ytrans"
#define kLogTagSdk									"ysdk"

typedef void (*YYLogNativeHandler)(LogLevel level, LogModule module, const char* text);

void PlatLog(LogLevel level, LogModule module, const char* tag, const char* format, ...);
void PlatAssertHelper(bool condition, const char* file, const char *func, const char* format, ...);
void SetLogLevel(int nLevel);
void SetYYLogInfo(bool bOpen, LogLevel level, const char* logPath, YYLogNativeHandler handler);
void LogText(LogLevel level, LogModule module, const char* tag, const char *text);
const char* GetMoudleString(LogModule module);

#if defined(_WINDOWS)

#define PlatAssert(e, format, ...) do {\
	PlatAssertHelper(e, __FILE__, __func__, format, ##args);\
} while(0)

#define LibAssert(e, format, ...) do {\
	PlatAssertHelper(e, __FILE__, __func__, format, ##args);\
} while(0)

#define Log(level, tag, format, ...) do {\
	PlatLog(level, kLogPlatform, tag, format,##args);\
} while(0)

#define LogM(level, module, tag, format, ...) do {\
	PlatLog(level, module, tag, format, ##args);\
} while(0)

#define  LOGD(tag, format, ...)  Log(kLogDebug, tag, format, ##args)
#define  LOGI(tag, format, ...)  Log(kLogInfo, tag, format, ##args)
#define  LOGE(tag, format, ...)  Log(kLogError, tag, format, ##args)
#define  LOGW(tag, format, ...)  Log(kLogWarning, tag, format, ##args)
#define  LOGT(tag, format, ...)  Log(kLogTrace, tag, format, ##args)

#else

#define PlatAssert(e, format, args...) do {\
	PlatAssertHelper(e, __FILE__, __func__, format, ##args);\
} while(0)

#define LibAssert(e, format, args...) do {\
	PlatAssertHelper(e, __FILE__, __func__, format, ##args);\
} while(0)

#define Log(level, tag, format, args...) do {\
	PlatLog(level, kLogPlatform, tag, format,##args);\
} while(0)

#define LogM(level, module, tag, format, args...) do {\
	PlatLog(level, module, tag, format, ##args);\
} while(0)

#define  LOGD(tag, format, args...)  Log(kLogDebug, tag, format, ##args)
#define  LOGI(tag, format, args...)  Log(kLogInfo, tag, format, ##args)
#define  LOGE(tag, format, args...)  Log(kLogError, tag, format, ##args)
#define  LOGW(tag, format, args...)  Log(kLogWarning, tag, format, ##args)
#define  LOGT(tag, format, args...)  Log(kLogTrace, tag, format, ##args)

#endif

class InfoTracker
{
public:
	InfoTracker()
	: m_info(NULL)
	, m_value(0)
	, m_level(kLogTrace)
	{
	}
	
	InfoTracker(const char* msg, int value, bool force)
	{   //the msg point should keep alive after the InfoTracker instance be released
		m_info = msg;
		m_value = value;
		m_level = kLogTrace;
		if (force)
		{
			m_level = kLogInfo;
		}
		Recorder(0);
	}
	
	~InfoTracker()
	{
		if (m_info != NULL)
		{
			Recorder(1);
		}
	}
	
private:
	void Recorder(int mode)
	{
		if (mode == 0)
		{
			LogM(m_level, kLogUnknown, "FUNC", "Enter %s para = %d", m_info, m_value);
		}
		else
		{
			LogM(m_level, kLogUnknown, "[FUNC]", "Leave %s para = %d", m_info, m_value);
		}
	}
	
	const char* m_info;
	int m_value;
	LogLevel m_level;
};

//void PlatformSetLogFilter(const char *filter);
//
#define ENTRY_TRACK(x)		InfoTracker local_info_tracker((x), 0, false);
#define ENTRY_TRACK_EX(x, y)  InfoTracker local_info_tracker((x), (y), false);
#define ENTRY_TRACK_EX_FORCE(x, y)  InfoTracker local_info_tracker((x), (y), true);

#endif
