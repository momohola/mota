#include "HttpSender.h"



using namespace std;

HttpSender::HttpSender(std::string address, int port)
{
	m_Address = address;
	m_Port = port;
	m_Client = new httplib::Client(m_Address, m_Port);
	m_JSON = new DecodeJSON;
}

string HttpSender::ResolutionCode(MsgCode msgCode)
{
	string dest;
	switch (msgCode)
	{
	case InitGameMap:
		dest = "/initGameMap";
		break;
	case InitGameInfo:
		dest = "/initGameInfo";
		break;
	case UploadGameMap:
		dest = "/uploadGameMap";
		break;
	case UploadGameHeroPos:
		dest = "/uploadGameHeroPos";
		break;
	case CodeGetAllChatMsg:
		dest = "/getAllChatMsg";
		break;
	case CodeAddChatMsg:
		dest = "/addChatMsg";
		break;
	}
	return dest;
}


void HttpSender::Send(MsgCode msgCode, const map<string,string> data)
{
	string dest=ResolutionCode(msgCode);
	

	httplib::Params params;
	for (auto perMap : data)
	{
		string key = perMap.first;
		string value = perMap.second;
		params.emplace(key, value);
	}

	if (auto res = m_Client->Post(dest.c_str(), params))
	{
		if (res->status == 200&&!res->body.empty())
		{
			std::cout << res->body << std::endl;
		}
	}
	else
	{
		cout << "·¢ËÍÇëÇóÊ§°Ü" << endl;
	}
}

map<string, string> HttpSender::Receive(MsgCode msgCode,LocalComputerInfo* host)
{
	string dest = ResolutionCode(msgCode);

	httplib::Params params;

	params.emplace("id",to_string(host->GetId()));
	params.emplace("computer",host->GetName());

	if (auto res = m_Client->Post(dest.c_str(), params))
	{
		if (res->status == 200)
		{
			return m_JSON->Decode(res->body);
		}
		else
		{
			cout << res->status << endl;
		}
	}
	else
	{
		cout << "·¢ËÍÇëÇóÊ§°Ü" << endl;
	}
}

std::string HttpSender::Receive(MsgCode msgCode)
{
	string dest = ResolutionCode(msgCode);

	if (auto res = m_Client->Post(dest.c_str()))
	{
		if (res->status == 200)
		{
			return res->body;
		}
	}
}

DecodeJSON* HttpSender::GetJSON()
{
	return m_JSON;
}

HttpSender* HttpSender::GetInstance()
{
	static HttpSender instance;
	return &instance;
}
