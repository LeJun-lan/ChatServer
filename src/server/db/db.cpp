#include "db.h"
#include <muduo/base/Logging.h>

//数据库配置信息
static string server = "127.0.0.1";
static string user = "root";
static string password = "123456";
static string dbname = "chat";

MySQL::MySQL()
{
    _conn = mysql_init(nullptr);
}
//释放数据库连接资源
//这里用UserModel示例，通过UserModel如何对业务层封装底层数据库的操作。代码示例如下：
MySQL::~MySQL()
{
    if (_conn != nullptr)
        mysql_close(_conn);
}
// 连接数据库
bool MySQL::connect()
{
    MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(),
                                  password.c_str(), dbname.c_str(), 3306, nullptr, 0);
    if (p != nullptr)
    {
        LOG_INFO << "连接成功!";
        // C和C++代码默认的编码字符是ASCII码，如果不设置，从mysql上拉取的中文会显示乱码
        mysql_query(_conn, "set names gbk");
    }
    else
    {
        LOG_INFO << "连接失败!";
    }
    return p;
}
// 更新操作
bool MySQL::update(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "更新失败!";
        return false;
    }
    return true;
}
// 查询操作
MYSQL_RES *MySQL::query(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "查询失败!";
        return nullptr;
    }
    return mysql_use_result(_conn);
}

//获取连接
MYSQL* MySQL::getConnection()
{
    return _conn;
}