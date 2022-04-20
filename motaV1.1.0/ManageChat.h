#pragma once
#include <list>

#include "ChatMsg.h"
#include "HttpSender.h"

class ManageChat
{
public:
	ManageChat();
	static std::list<ChatMsg> GetAllChatMsg();
	static void SendChatMsg(const ChatMsg& chatMsg);
private:
	
};

