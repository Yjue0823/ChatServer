#ifndef CHATSERVICE_H
#define CHATSERVICE_H
#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>
#include "muduo/base/Logging.h"

#include "chatserver.hpp"
#include "../public.hpp"
#include "../../thirdparty/json.hpp"

using json = nlohmann::json;
using MsgHandler = std::function<void(const muduo::net::TcpConnectionPtr conn, json& js, muduo::Timestamp time)>;

class ChatService{
public:
    static ChatService* instance(); // 用这个在外部实例化单例对象
    // 登录
    void login(const muduo::net::TcpConnectionPtr conn, json& js, muduo::Timestamp time);
    // 注册
    void reg(const muduo::net::TcpConnectionPtr conn, json& js, muduo::Timestamp time);
    // 获取业务处理器
    MsgHandler getMsgHandler(int msgid);
private:
    ChatService();
    std::unordered_map<int, MsgHandler> _msgHandlerMap;
};

#endif