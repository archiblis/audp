#ifndef AUDP_LOG_SHOP_H
#define AUDP_LOG_SHOP_H

#include <string>
#include "audp/log.h"

namespace Aqua {

class LogShop : public Log
{
public:
	virtual ~LogShop();	
	static LogShop* create(const std::string &file_path);
	void log(int level, const char* buffer, size_t size);
	
	void setLogLevel(int log_level) { log_level_ = log_level; }
	void setMaxLogSize(int max_log_size) { max_log_size_ = max_log_size; }

private:
	LogShop(const std::string &file_path);

private:
	int log_level_;
	int max_log_size_;
};

} // namespace Aqua

#endif

