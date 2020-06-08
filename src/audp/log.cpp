#include "audp/log.h"

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <sys/times.h>

namespace Aqua {

Log::Log(const std::string &file_path) :
	file_path_(file_path), fp_(NULL)
{

}

Log::~Log()
{
	if (fp_ != NULL) {
		::fclose(fp_);
	}
}

void Log::logWrite(const char *buffer, int size)
{
	if (checkOpenFile() == false) {
		printf("open file %s failed: %s",
			actual_file_path_.c_str(), ::strerror(errno));
	}

	::fwrite(buffer, size, 1, fp_);
}

bool Log::checkOpenFile()
{
	char actual_file_path[512];
	struct timespec tv;
	::clock_gettime(CLOCK_REALTIME, &tv);
	
	struct tm tm;
	::localtime_r(&tv.tv_sec, &tm);
	
	// %Y 年份
	// %m 月份
	// %d 日
	// file_path 格式: xxx_%Y%m%d.log
	strftime(actual_file_path, sizeof actual_file_path, file_path_.c_str(), &tm);
	
	if (actual_file_path_ == actual_file_path) {
		return true;
	}

	actual_file_path_ = actual_file_path;

	FILE *fp = ::fopen(actual_file_path_.c_str(), "a");
	if (NULL == fp) {
		return false;
	}
	if (fp_ != NULL) {
		::fclose(fp_);
	}
	::setbuf(fp, NULL);
	fp_ = fp;

	return true;
}

} // namespace Aqua
