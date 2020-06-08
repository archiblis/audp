#include "audp/log_shop.h"

#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

namespace Aqua {

#define MAX_LOG_SIZE 0x0FFFFFFF

LogShop::LogShop(const std::string &file_path) :
	Log(file_path), log_level_(0), max_log_size_(MAX_LOG_SIZE)
{
}

// static
LogShop* LogShop::create(const std::string &file_path)
{
	// check dir
	for (size_t i = 0; i < file_path.size(); ++i) {
		if (file_path[i] == '/') {
			if (0 == i) {
				continue;
			}
			if (::access(file_path.substr(0, i).c_str(), 0) != 0) {
				::mkdir(file_path.substr(0, i).c_str(), 0777);
			}
		}
	}

	return new LogShop(file_path);
}

LogShop::~LogShop()
{
}

void LogShop::log(int level, const char* buffer, size_t size)
{
	if (level < log_level_) {
		return;
	}

	if ((int)size > max_log_size_) {
		return;
	}

	this->logWrite(buffer, size);
}

} // namespace Aqua
