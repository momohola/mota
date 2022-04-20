#ifndef _HTTPSENDER_H_
#define _HTTPSENDER_H_
#include "MyInclude/httplib/httplib.h"
#include "MsgCode.h"
#include "DecodeJSON.h"
#include "LocalComputerInfo.h"
//包含httplib/httplib.h必须位于第一个

class HttpSender
{
public:
	HttpSender(std::string address="47.106.177.228", int port=8081);


	/**
	 * \brief 向服务器指定的控制器发送data里面的数据
	 * \param msgCode 控制器类型
	 * \param data 字典类型的数据
	 */
	void Send(MsgCode msgCode, const std::map<std::string, std::string> data);

	/**
	 * \brief 向服务器指定的控制器发出请求，接收服务器返回的数据
	 * \param msgCode 控制器类型
	 * \param host 本机信息
	 * \return 从服务器接收到的信息
	 */
	std::map<std::string, std::string> Receive(MsgCode msgCode, LocalComputerInfo* host);
	std::string Receive(MsgCode msgCode);
	DecodeJSON* GetJSON();

	static HttpSender* GetInstance();
private:
	std::string ResolutionCode(MsgCode msgCode);
	httplib::Client* m_Client;
	std::string m_Address;
	int m_Port;
	DecodeJSON* m_JSON;
};
#endif

