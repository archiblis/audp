#ifndef AUDP_LOG_PORT_H
#define AUDP_LOG_PORT_H

#include <cstdarg>
#include <mutex>  // std::mutex
#include <map>
#include <string>
#include <thread> // std::thread
#include <list>

#include "audp/singleton.h"

namespace Aqua
{

class LogShop;

class LogPort
{
public:
	typedef size_t (*LogFormat)(
		char *buffer, size_t buffer_size, int level,
		const char *filename, int line, const char *function,
		const char *format, va_list args);

	struct LogData {
		int32_t id;
		LogShop *log_shop;
		std::list<std::string> list;
	};
	typedef std::map<int, LogData> LogDataMap;
	typedef std::map<int, LogShop*> LogShopMap; 
	typedef std::map<int, LogFormat> LogFormatMap;

public:
	LogPort();
	~LogPort();

	// thread
	bool startThread();

	bool addLogShop(int id, const std::string &file_path);
	bool addFormat(int id, LogFormat format);
	void log(int id,
			 int level,
			 const char* buffer,
			 size_t size);
	void log(int id,
			 int level,
			 const char* filename,
			 int line,
			 const char* function,
			 const char* format,
			 va_list args);
	void log(int id,
			 int level,
			 const char* filename,
			 int line,
			 const char* function,
			 const char* format,
			 ...);

private:
	void loop();
	void stopLoop();

private:
	// thread
	std::thread *thread_;
	std::mutex mtx_;
	bool loop_;
	//
	LogDataMap log_data_map_;
	LogShopMap log_shop_map_;
	LogFormatMap log_format_map_;
};

} // namespace AUDP

#define sLogPort Singleton<Aqua::LogPort>::getInstance()

#endif
