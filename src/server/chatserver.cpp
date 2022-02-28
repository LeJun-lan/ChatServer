#include "chatserver.hpp"
#include "json.hpp"
#include "chatservice.hpp"

#include <functional>
#include <string>
using namespace std;
using namespace placeholders;
using json = nlohmann::json;

ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg)
    : _server(loop, listenAddr, "xuhaifeng"), loop(loop)
{
    //注册连接回调函数
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
    //注册消息回调函数
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    //设置线程数量
    _server.setThreadNum(4);
}

//启动服务
void ChatServer::start()
{
    _server.start();
}

//处理用户连接回调函数
void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    //客户端断开
    if (!conn->connected())
    {
        conn->shutdown();
        ChatService::instance()->closeClientHandle(conn);
    }
}

//处理用户读写回调函数
void ChatServer::onMessage(const TcpConnectionPtr &conn,
                           Buffer *buffer,
                           Timestamp time)
{
    string buff = buffer->retrieveAllAsString();
    //数据的反序列化
    json js = json::parse(buff);
    //解耦业务模块和网络模块
    auto msghandler = ChatService::instance()->getHander(js["msgid"].get<int>()); //返回值是map中第二个参数MsgHander类型
    //回调消息绑定好的事件处理器，来执行相应的业务处理
    msghandler(conn, js, time);
}