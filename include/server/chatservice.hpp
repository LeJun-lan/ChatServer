#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <mutex>
#include <string>
#include "json.hpp"
using namespace std;
using namespace muduo::net;
using namespace muduo;
using json = nlohmann::json;

using namespace placeholders;
#include "usermodel.hpp"
#include "offlinemessagemodle.hpp"
#include "friendmodel.hpp"
#include "groupmodle.hpp"
#include "redis.hpp"

//表示处理消息的事件回调方法
using MsgHander = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp)>;
//聊天服务器业务类
class ChatService
{
public:
    //获取单例对象的接口函数
    static ChatService *instance();
    //处理登录业务函数
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //处理注册业务函数
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);

    //一对一聊天业务函数
    void onechat(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 创建群组业务
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);

    //添加好友业务函数
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);

    //获取消息对应的处理器
    MsgHander getHander(int msgid);

    //客户端异常关闭处理方法
    void closeClientHandle(const TcpConnectionPtr &conn);

    // 处理注销业务
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //服务器异常 重置函数
    void reset();


    // 从redis消息队列中获取订阅的消息
    void handleRedisSubscribeMessage(int, string);

    
private:
    ChatService();
    //存储消息id和对应的业务处理方法
    unordered_map<int, MsgHander> _msgHandlerMap;

    //数据操作类
    UserModel _userModel;              // user
    OfflineMessagemodle _offlineModle; // offlinemessage
    FriendModel _friendModle;          // friend
    GroupModel _groupModel;

    //存储用户的通信连接
    unordered_map<int, TcpConnectionPtr> _userConnMap;

    //防止线程同时访问变量，定义互斥锁，保证线程安全
    mutex _coonMutex;

    //redis操作对象
    Redis _redis;
};

#endif