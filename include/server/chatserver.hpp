#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
using namespace muduo;
using namespace muduo::net;

//聊天服务器主类
class ChatServer
{
public:
    //初始化聊天服务器对象（构造函数）
    ChatServer(EventLoop *loop,
               const InetAddress &listenAddr,
               const string &nameArg);
    void start();

private:
    //处理用户连接回调函数
    void onConnection(const TcpConnectionPtr &);
    //处理用户读写回调函数
    void onMessage(const TcpConnectionPtr&,
                            Buffer*,
                            Timestamp);

    TcpServer _server;//muduo库，实现服务器功能的类对象
    EventLoop *loop;//指向事件循环的指针
};

#endif