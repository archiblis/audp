#ifndef AUDP_LOG_H
#define AUDP_LOG_H

#include <string>

namespace Aqua {

class Log
{
public:
	Log(const std::string &file_path);
	virtual ~Log();

	void logWrite(const char *buffer, int size);

private:
	bool checkOpenFile();

private:
	std::string file_path_;
	std::string actual_file_path_;
	FILE *fp_;
};

} // namespace Aqua

#endif

