// #include "../../include/server/chatservice.hpp"
#include "chatservice.hpp"
#include "public.hpp"

ChatService *ChatService::instance()
{
    static ChatService service;
    return &service;
}

void ChatService::login(const muduo::net::TcpConnectionPtr conn, json &js, muduo::Timestamp time)
{
    LOG_INFO << "Login Call Back";
}
void ChatService::reg(const muduo::net::TcpConnectionPtr conn, json &js, muduo::Timestamp time)
{
    LOG_INFO << "REG Call Back!";
}

MsgHandler ChatService::getMsgHandler(int msgid)
{
    auto iter = _msgHandlerMap.find(msgid);
    if (iter == _msgHandlerMap.end())
    {
        return [=](const muduo::net::TcpConnectionPtr conn, json &js, muduo::Timestamp time)
        {
            LOG_ERROR << "msgid:" << msgid << "can not find handler";
        };
    }
    else
    {
        return iter->second;
    }
}

ChatService::ChatService()
{
    // 业务列表注册
    _msgHandlerMap.insert(std::pair<int, MsgHandler>(LOGIN_MSG, std::bind(&ChatService::login, this, _1, _2, _3)));
    _msgHandlerMap.insert(std::pair<int, MsgHandler>(REG_MSG, std::bind(&ChatService::reg, this, _1, _2, _3)));
}
