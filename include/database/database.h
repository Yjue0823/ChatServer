#ifndef DATABASE_H
#define DATABASE_H

#include <muduo/base/Logging.h>
#include <mysql/mysql.h>
#include <string>

// 数据库基本信息
static std::string server = "127.0.0.1";
static std::string user = "root";
static std::string password = "0823";
static std::string dbname = "chat";

// 数据库类
class MySql{
public:
    // 初始化数据库连接
    MySql();
    // 释放数据库资源
    ~MySql();
    // 连接数据库
    bool connect();
    // 更新操作
    bool updata(std::string sql);
    // 查询操作
    MYSQL_RES* query(std::string sql);
private:
    MYSQL *_conn;
};
#endif