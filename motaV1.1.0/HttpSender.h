#ifndef _HTTPSENDER_H_
#define _HTTPSENDER_H_
#include "MyInclude/httplib/httplib.h"
#include "MsgCode.h"
#include "DecodeJSON.h"
#include "LocalComputerInfo.h"
//����httplib/httplib.h����λ�ڵ�һ��

class HttpSender
{
public:
	HttpSender(std::string address="47.106.177.228", int port=8081);


	/**
	 * \brief �������ָ���Ŀ���������data���������
	 * \param msgCode ����������
	 * \param data �ֵ����͵�����
	 */
	void Send(MsgCode msgCode, const std::map<std::string, std::string> data);

	/**
	 * \brief �������ָ���Ŀ������������󣬽��շ��������ص�����
	 * \param msgCode ����������
	 * \param host ������Ϣ
	 * \return �ӷ��������յ�����Ϣ
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

