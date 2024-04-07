// #include "../../include/server/chatserver.hpp"
#include "../../include/server/chatservice.hpp"
#include "chatserver.hpp"
#include "json.hpp"
// #include "../../thirdparty/json.hpp"
// #include "chatserver.hpp"
#include <string>
using json = nlohmann::json;

ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr, 
                       const string &nameArg): _server(loop, listenAddr, nameArg),_loop(loop)
{
    // 注册连接回调函数
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

    // 注册消息回调函数
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    // 线程数量
    _server.setThreadNum(4);
}

void ChatServer::start()
{
    _server.start();
}

// 连接 或 断开连接 回调处理
void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    if(conn->connected()){
        std::cout << conn->peerAddress().toIpPort() << "-->" << 
                     conn->localAddress().toIpPort() << "status:Online" << std::endl;
    }
    else{
        std::cout << conn->peerAddress().toIpPort() << "status:Offline" << std::endl;
        conn->shutdown();
    }
}

void ChatServer::onMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    // 数据反序列化
    json js = json::parse(buf);
    // 通过 js["msg_id"]获取一个业务处理器 handler 目的是完全解耦网络模块代码和业务模块代码
    auto msghandler = ChatService::instance()->getMsgHandler(js["msg_id"].get<int>());
    msghandler(conn, js, time);
}
