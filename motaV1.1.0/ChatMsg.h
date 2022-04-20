#pragma once
#include <string>


class ChatMsg
{
public:
	ChatMsg(const std::string& mName, const std::string& mContent)
		: m_Name(mName),
		  m_Content(mContent)
	{
	}

	std::string getName() const;
	std::string getContent() const;
private:
	std::string m_Name;
	std::string m_Content;
};




