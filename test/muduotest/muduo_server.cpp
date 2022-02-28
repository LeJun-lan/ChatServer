/*
muduo网络库给用户提供两个主要的类
TcpServer
TcpClient

epoll + 线程池
好处：可以把网络IO代码和业务代码分开

*/
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <string>
#include <functional>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;
//基于muduo网络库开发的服务器
// 1.创建TcpServer对象
// 2.创建EventLoop事件循环对象的指针
// 3.明确ChatServer(TcpServer)构造函数以及参数
// 4.在当前服务器类的构造中，注册处理连接的回调函数和处理读写事件的回调函数
// 5.设置服务器的线程数量  muduo库会自己分配 IO线程和 worker线程
class ChatServer
{
public:
    ChatServer(EventLoop *loop,               //事件循环
               const InetAddress &listenAddr, // IP + Port
               const string &nameArg          //服务器名字
               ) : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        //给服务器注册用户连接的创建和断开回调
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
        //为服务器注册用户读写事件的回调函数
        _server.setMessageCallback(std::bind(&ChatServer::onMessege, this, _1, _2, _3));
        //设置服务器最大线程数   一个IO线程  三个worker线程
        _server.setThreadNum(1);
    }
    void start()
    {
        _server.start();
    }

private:
    void onConnection(const TcpConnectionPtr &conn) //处理用户的连接 epoll listen fd
    {
        if (conn->connected())
        {
            cout << conn->peerAddress().toPort() << " -> " << conn->localAddress().toIpPort() << endl;
            cout << "state:online!" << endl;
        }
        else
        {
            cout << conn->peerAddress().toPort() << " -> " << conn->localAddress().toIpPort() << endl;
            cout << "state:offline!" << endl;
            conn->shutdown();
            _loop->quit();
        }
    }
    //处理用户的读写事件
    void onMessege(const TcpConnectionPtr &conn, //连接
                   Buffer *buffer,                     //缓冲区
                   Timestamp time)                    //接收数据的时间信息
    {
        string buf=buffer->retrieveAllAsString();
        cout<<"recv date:"<<buf<<" time:"<<time.toString()<<endl;
        conn->send(buf);
    }
    TcpServer _server; // 1
    EventLoop *_loop;  // 2
};

int main()
{
    EventLoop loop; // epoll
    InetAddress addr("127.0.0.1",6000);
    ChatServer server(&loop,addr,"xuhaifeng");
    server.start();//启动服务器   添加listenfd到 epoll上
    loop.loop();//以阻塞方式 等待client连接服务器
    
    return 0;
}