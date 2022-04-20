#include "DecodeJSON.h"
#include <iostream>
#include "EncodingTransform.h"
using namespace std;
using json = nlohmann::json;
map<string,string> DecodeJSON::Decode(string jsonStr)
{
	json jObj = json::parse(jsonStr);

	switch ((int)jObj.at("code"))
	{
	case InitGameInfo:
		return DecodeInitGameInfo(jObj);
		break;
	case InitGameMap:
		return DecodeInitGameMap(jObj);
		break;
	default:
		return map<string, string>();
	}
	
}

//解析地图信息
map<string, string> DecodeJSON::DecodeInitGameMap(const json& jObj)
{
	map<string, string> dataMap;
	string keyStr[4] = { "row","col","height","mapList"};

	dataMap["msg"] = to_string(jObj.at("msg"));

	for (auto it : keyStr)
	{
		dataMap[it] = to_string(jObj.at("data").at(it));
	}

	return dataMap;
}

//解析游戏版本信息
map<string, string> DecodeJSON::DecodeInitGameInfo(const json& jObj)
{
	map<string, string> dataMap;
	string keyStr[3] = {"name","version","save" };

	dataMap["msg"] = to_string(jObj.at("msg"));

	for (auto it : keyStr)
	{
		dataMap[it] = to_string(jObj.at("data").at(it));
	}

	return dataMap;
}

std::list<ChatMsg> DecodeJSON::DecodeChatMsg(std::string charMsgStr)
{
	list<ChatMsg> charMsgList;
	json jObj = json::parse(charMsgStr);

	for (int i = 0; i < jObj.size(); ++i)
	{
		string name = jObj[i].at("name");
		string content = jObj[i].at("content");

		name= EncodingTransform::UTF8ToString(name);
		content= EncodingTransform::UTF8ToString(content);

		ChatMsg chatMsg(name,content);

		charMsgList.push_back(chatMsg);
	}

	return charMsgList;
}
