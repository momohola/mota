#include "LocalComputerInfo.h"

#include <Winsock2.h>


#pragma warning(disable:4996)

using namespace std;

string GetLocalIpAddress();
string GetHostName();
LocalComputerInfo::LocalComputerInfo()
{

	m_Name = GetHostName();
	m_IP = GetLocalIpAddress();
}

LocalComputerInfo::~LocalComputerInfo()
{
	
}


std::string LocalComputerInfo::GetIP()
{
	return m_IP;
}

std::string LocalComputerInfo::GetName()
{
	return m_Name;
}

time_t LocalComputerInfo::GetId()
{
	return m_Id;
}


//得到本机ip
string GetLocalIpAddress()
{
	WORD wVersionRequested = MAKEWORD(2, 2);

	WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
		return "";

	char local[255] = { 0 };
	gethostname(local, sizeof(local));
	hostent* ph = gethostbyname(local);
	if (ph == NULL)
		return "";

	in_addr addr;
	memcpy(&addr, ph->h_addr_list[0], sizeof(in_addr)); // 这里仅获取第一个ip

	string localIP;
	localIP.assign(inet_ntoa(addr));

	WSACleanup();
	return localIP;
}

//得到本机用户名
string GetHostName()
{
	WORD wVersionRequested = MAKEWORD(2, 2);

	WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
		return "None";
	char local[255] = { 0 };
	gethostname(local, sizeof(local));

	string str(local);
	return str;

}