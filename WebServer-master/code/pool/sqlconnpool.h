/*
 * @Author       : mark
 * @Date         : 2020-06-16
 * @copyleft Apache 2.0
 */ 
#ifndef SQLCONNPOOL_H
#define SQLCONNPOOL_H

#include <mysql/mysql.h>
#include <string>
#include <queue>
#include <mutex>
#include <semaphore.h>
#include <thread>
#include "../log/log.h"

//数据库连接池  资源复用 
class SqlConnPool {
public: 
    static SqlConnPool *Instance(); // 类内声明SqlConnPool对象指针

    MYSQL *GetConn();
    void FreeConn(MYSQL * conn);
    int GetFreeConnCount();
//初始化数据库连接
    void Init(const char* host, int port,
              const char* user,const char* pwd, 
              const char* dbName, int connSize);
    void ClosePool();

private:
    SqlConnPool();
    ~SqlConnPool();

    int MAX_CONN_;
    int useCount_;
    int freeCount_;
    //连接队列
    std::queue<MYSQL *> connQue_;
    //互斥锁
    std::mutex mtx_;
    //信号量
    sem_t semId_;
};


#endif // SQLCONNPOOL_H