#include<string>
#include <unistd.h>
#include "server/webserver.h"
#include<fstream>
#include "config/ConfigFileReader.h"
using namespace std;

extern void main_config_Start(const char* filename);
int main() {
    /* 守护进程 后台运行 */
    //daemon(1, 0); 

	main_config_Start("data.cfg");

	return 0;
}
	//WebServer server(
	//	1316, 3, 60000, false,             /* 端口 ET模式 timeoutMs 优雅退出  */
	//	3306, "root", "root", "webserver", /* Mysql配置 */
	//	12, 6, true, 1, 1024);             /* 连接池数量 线程池数量 日志开关 日志等级 日志异步队列容量 */
	//server.Start();
	