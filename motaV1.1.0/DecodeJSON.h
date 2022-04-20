#ifndef _DECODEJSON_H_
#define _DECODEJSON_H_


#include <iostream>
#include <nlohmann/json.hpp>
#include <map>
#include <string>

#include "ChatMsg.h"
#include "MsgCode.h"
using json = nlohmann::json;

class DecodeJSON
{
public:
	std::map<std::string, std::string> Decode(std::string jsonStr);
	static std::list<ChatMsg> DecodeChatMsg(std::string charMsgStr);
private:
	std::map<std::string, std::string> DecodeInitGameInfo(const json& jObj);
	std::map<std::string, std::string> DecodeInitGameMap(const json& jObj);
	
private:
};



#endif
