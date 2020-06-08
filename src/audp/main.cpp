#include <iostream>
#include <cstdio>

#if 1
#include "audp/log.h"
#include "audp/log_shop.h"
#include "audp/log_port.h"
#endif

#include "audp/log_master.h"

int main()
{
	//Aqua::Log log("test_%Y%m%d.log");
	//Aqua::Log* log = Aqua::LogShop::create("test_%Y%m%d.log");
	//log->logWrite("12345678", 8);
	printf("aqua udp~!\n");
	//if (sLogPort != NULL) {
	//	printf("sLogPort instance.\n");
	//	sLogPort->startThread();
	//}
	sLogMaster->initMainLogger("./log/main.%Y%m%d.log");
	LOG_INFO("aaaa %d %d aaaaa", 1, 2);
	LOG_INFO("bbbb %s cccc", "abc");
}

