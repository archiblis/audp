#include "audp/log_master.h"

#include <cstdio>
#include <cstring>
#include <stdarg.h>
#include <ctime>
#include <sys/times.h>

namespace Aqua
{

size_t format(
	char *buffer,
	size_t buffer_size,
	int level,
	const char *filename,
	int line,
	const char *function,
    const char *format,
	va_list args)
{
	struct timespec tv;
	//::clock_gettime(CLOCK_MONOTONIC, &tv);
	::clock_gettime(CLOCK_REALTIME, &tv);
	int64_t second = tv.tv_sec;
	int64_t millsecond = tv.tv_nsec / 1000000;
	struct tm tm;
	::localtime_r(&second, &tm);
	char time_buffer[32];
	strftime(time_buffer, sizeof time_buffer, "%H:%M:%S", &tm);

	static const char *log_level_string[] = {
		"DEBUG", "INFO", "WARN", "ERROR" };

	size_t count = ::snprintf(buffer, buffer_size,
		"[%s][%s:%03ld][%s:%d](%s)", 
		log_level_string[level], time_buffer, millsecond, 
		filename, line, function
	);
	
	count += ::vsnprintf(buffer + count, buffer_size - count, format, args);
	count += ::snprintf(buffer + count, buffer_size - count, "\n");

	return count;
}

LogMaster::LogMaster()
{
}

LogMaster::~LogMaster()
{
}

bool LogMaster::initMainLogger(const std::string &file_path)
{
	sLogPort->addLogShop(0, file_path);
	sLogPort->addFormat(0, format);
	return true;
}

} // namespace Aqua
