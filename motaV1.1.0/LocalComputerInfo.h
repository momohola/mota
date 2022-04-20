#pragma once
#include <string>
#include <time.h>
#include <process.h>

class LocalComputerInfo
{
public:
	LocalComputerInfo();
	~LocalComputerInfo();
	std::string GetName();
	std::string GetIP();
	time_t GetId();
private:
	std::string m_Name;
	std::string m_IP;
	int m_Id = _getpid();
};

