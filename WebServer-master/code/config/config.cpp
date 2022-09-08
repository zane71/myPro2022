#include<string>
#include <unistd.h>
#include "../server/webserver.h"
#include<fstream>
#include "ConfigFileReader.h"

using namespace std;

void main_config_Start(const char* filename) {

	CConfigFileReader config(filename);
//端口 ET模式 timeoutMs 优雅退出
	const char* port = config.getConfigName("port");
	if (port == NULL)
	{
		LOG_ERROR("port is not set in config file");
		exit(0);
	}
	int _port = atoi(port);

	const char* trigMode = config.getConfigName("trigMode");
	if (trigMode == NULL)
	{
		LOG_ERROR("trigMode is not set in config file");
		exit(0);
	}
	int _trigMode = atoi(trigMode);

	const char* timeoutMS = config.getConfigName("timeoutMS");
	if (timeoutMS == NULL)
	{
		LOG_ERROR("timeoutMS is not set in config file");
		exit(0);
	}
	int _timeoutMS = atoi(timeoutMS);

	const char* OptLinger = config.getConfigName("OptLinger");
	if (OptLinger == NULL)
	{
		LOG_ERROR("OptLinger is not set in config file");
		exit(0);
	}
	bool _OptLinger = (atoi(OptLinger) == 0) ? false : true;


	



//Mysql配置 
	const char* sqlPort = config.getConfigName("sqlPort");
	if (sqlPort == NULL)
	{
		LOG_ERROR("sqlPort is not set in config file");
		exit(0);
	}
	int _sqlPort = atoi(sqlPort);

	const char* _sqlUser = config.getConfigName("sqlUser");
	if (_sqlUser == NULL)
	{
		LOG_ERROR("sqlUser is not set in config file");
		exit(0);
	}

	const char* _sqlPwd = config.getConfigName("sqlPwd");
	if (_sqlPwd == NULL)
	{
		LOG_ERROR("sqlPwd is not set in config file");
		exit(0);
	}


	const char* _dbName = config.getConfigName("dbName");
	if (_dbName == NULL)
	{
		LOG_ERROR("dbName is not set in config file");
		exit(0);
	}


 // 连接池数量 线程池数量 日志开关 日志等级 日志异步队列容量
	const char* connPoolNum = config.getConfigName("connPoolNum");
	if (connPoolNum == NULL)
	{
		LOG_ERROR("connPoolNum is not set in config file");
		exit(0);
	}
	int _connPoolNum = atoi(connPoolNum);

	const char* threadNum = config.getConfigName("threadNum");
	if (threadNum == NULL)
	{
		LOG_ERROR("threadNum is not set in config file");
		exit(0);
	}
	int _threadNum = atoi(threadNum);

	const char* openLog = config.getConfigName("openLog");
	if (openLog == NULL)
	{
		LOG_ERROR("openLog is not set in config file");
		exit(0);
	}
	bool _openLog = (atoi(openLog) == 0) ? false : true;

	const char* logLevel = config.getConfigName("logLevel");
	if (logLevel == NULL)
	{
		LOG_ERROR("logLevel is not set in config file");
		exit(0);
	}
	int _logLevel = atoi(logLevel);

	const char* logQueSize = config.getConfigName("logQueSize");
	if (logQueSize == NULL)
	{
		LOG_ERROR("logQueSize is not set in config file");
		exit(0);
	}
	int _logQueSize = atoi(logQueSize);

	WebServer server(
		_port, _trigMode, _timeoutMS, _OptLinger,				/* 端口 ET模式 timeoutMs 优雅退出  */
		_sqlPort, _sqlUser, _sqlPwd, _dbName,						/* Mysql配置 */
		_connPoolNum, _threadNum, _openLog, _logLevel, _logQueSize);             /* 连接池数量 线程池数量 日志开关 日志等级 日志异步队列容量 */
	server.Start();
}