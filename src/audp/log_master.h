#ifndef ADUP_LOG_MASTER_H
#define ADUP_LOG_MASTER_H

#include "audp/log_port.h"

#include "audp/singleton.h"

namespace Aqua
{

enum LogLevel {
	MIN = 0,

	DEBUG = 0,
	INFO,
	WARNING,
	ERROR,

	MAX,
};

class LogMaster
{
public:
	LogMaster();
	~LogMaster();

	bool initMainLogger(const std::string &file_path);

private:

};

} // namespace Aqua

#define sLogMaster Singleton<Aqua::LogMaster>::getInstance() 

// Log
#if 0
#define LOG_INFO(_format, _id, ...) \
	sLogMaster->log(_id, Aqua::LogLevel::INFO, \
		__FILE__, __LINE__, __func__, \
		_format, ##__VA_ARGS__)	
#endif

#define LOG_INFO(_format, ...) \
	sLogPort->log(0, Aqua::LogLevel::INFO, \
		__FILE__, __LINE__, __func__, \
		_format, ##__VA_ARGS__)	

#endif
