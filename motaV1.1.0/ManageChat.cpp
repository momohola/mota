#include "ManageChat.h"
#include "EncodingTransform.h"
using namespace std;

ManageChat::ManageChat()
{
}

std::list<ChatMsg> ManageChat::GetAllChatMsg()
{
	HttpSender* http=HttpSender::GetInstance();

	list<ChatMsg> chatMsgList;

	string response= http->Receive(CodeGetAllChatMsg);

	chatMsgList =DecodeJSON::DecodeChatMsg(response);

	return chatMsgList;
}

void ManageChat::SendChatMsg(const ChatMsg& chatMsg)
{
	HttpSender* http = HttpSender::GetInstance();

	map<string, string> chatMsgMap;
	chatMsgMap["name"] = chatMsg.getName();
	chatMsgMap["content"] = chatMsg.getContent();

	http->Send(CodeAddChatMsg, chatMsgMap);
}

