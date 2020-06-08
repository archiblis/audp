#include "audp/log_port.h"

#include <cstdio>
#include <cstring>
#include <string.h>
#include "audp/log_shop.h"

namespace Aqua
{

LogPort::LogPort() :
	thread_(NULL)
{
}

LogPort::~LogPort()
{
	if (thread_ != NULL) {
		stopLoop();
		const std::lock_guard<std::mutex> lock(mtx_);
		thread_->join();
		delete thread_;
	}
}

bool LogPort::startThread()
{
	const std::lock_guard<std::mutex> lock(mtx_);
	if (thread_ != NULL) {
		return false;
	}

	thread_ = new std::thread(&LogPort::loop, this);
	return true;
}

void LogPort::loop()
{
	loop_ = true;
	for ( ;loop_; ) {
		int count = 0;
		LogDataMap::iterator iter = log_data_map_.begin();
		for (; iter != log_data_map_.end(); ++iter) {
			LogData &log_data = iter->second;
			std::list<std::string>::iterator iter_list = log_data.list.begin();
			for (; iter_list != log_data.list.end(); ) {
				

				log_data.list.erase(iter_list++);
				
				if (count >= 100) {
					break;
				}
			}
			if (count >= 100) {
				break;
			}
		}
	}
}

void LogPort::stopLoop()
{
	for ( ;loop_; ) {
		break;
	}
}

void LogPort::log(int id, int level, const char* buffer, size_t size)
{
	if (thread_ != NULL && loop_) {
		const std::lock_guard<std::mutex> lock(mtx_);
		LogDataMap::iterator it = log_data_map_.find(id);
		if (it == log_data_map_.end()) {
			return;
		}
		//std::string str;
		//str.resize(size);
		//memcpy(str.c_str(), buffer, size);	
		std::string str(buffer, buffer + size);
		it->second.list.push_back(str);
	} else {
		LogShopMap::iterator it = log_shop_map_.find(id);
		if (it == log_shop_map_.end()) {
			return;
		}
		it->second->log(level, buffer, size);
	}
}

void LogPort::log(int id,
	int level,
	const char* filename,
	int line,
	const char* function,
	const char* format,
	va_list args)
{
	LogFormat log_format = NULL;
	{
		LogFormatMap::iterator iter = log_format_map_
			.find(id);
		if (iter != log_format_map_.end()) {
			log_format = iter->second;
		} else {
			return;
		}
	}	

	char buffer[1024] = {'\0'};
	int buffer_size = 1024;
	size_t count = log_format(buffer, buffer_size, level,
		filename, line, function, format, args);

	this->log(id, level, buffer, count); 
}

void LogPort::log(int id,
	int level,
	const char* filename,
	int line,
	const char* function,
	const char* format,
	...)
{
	va_list args;
	va_start(args, format);
	
	LogFormat log_format = NULL;
	{
		LogFormatMap::iterator iter = log_format_map_
			.find(id);
		if (iter != log_format_map_.end()) {
			log_format = iter->second;
		} else {
			return;
		}
	}	

	char buffer[1024] = {'\0'};
	int buffer_size = 1024;
	size_t count = log_format(buffer, buffer_size, level,
		filename, line, function, format, args);

	this->log(id, level, buffer, count); 

	va_end(args);
}

bool LogPort::addFormat(int id, LogFormat format)
{
	log_format_map_[id] = format;
	return true;
}

bool LogPort::addLogShop(int id, const std::string &file_path)
{
	if (log_shop_map_.find(id) != log_shop_map_.end()) {
		return false;
	}

	const std::lock_guard<std::mutex> lock(mtx_);
	LogShop *log_shop = LogShop::create(file_path);
	log_shop_map_.insert(std::make_pair(
		id, log_shop));
	log_shop_map_[id] = log_shop;
	LogData log_data;
	log_data.id = id;
	log_data.log_shop = log_shop;
	log_data.list.clear();
	log_data_map_.insert(std::make_pair(
		id, log_data));

	return true;
}

} // namespace AUDP
