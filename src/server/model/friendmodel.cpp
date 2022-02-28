#include "friendmodel.hpp"
#include "db.h"

//添加好友关系
void FriendModel::insert(int userid, int friendid)
{
    char sql[1024] = {0};

    sprintf(sql, "insert into friend values(%d,%d)", userid, friendid);
    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

//返回好友列表 friend->name(sql联合查询)
vector<User> FriendModel::query(int userid)
{
    char sql[1024] = {0};
    sprintf(sql, "select a.id,a.name,a.state from user a inner join friend b on b.friendid = a.id where b.userid = %d", userid);

    vector<User> v;
    MySQL mysql; //创建对象
    //连接数据库
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            //查询成功
            MYSQL_ROW row;
            //把userid用户的所有离线消息放入vector容器中
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                User user;
                user.setId(atoi(row[0])); 
                user.setName(row[1]);
                user.setState(row[2]);
                v.push_back(user);
            }
            mysql_free_result(res);
            return v;
        }
    }
    return v;
}