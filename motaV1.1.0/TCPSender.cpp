//#include "TCPSender.h"
//#include <iostream>
//
//using namespace std;
//#pragma warning(disable:4996)
//#pragma comment(lib, "ws2_32.lib")	
//
//void TCPSender::Init()
//{
//	WORD	wVersionRequested;
//	WSADATA wsaData;
//	int		err;
//	wVersionRequested = MAKEWORD(2, 2);
//	//�����׽���
//	err = WSAStartup(wVersionRequested, &wsaData);	
//	if (err != 0)
//	{
//		cout << "�����׽���ʧ��"<<endl;
//		return;
//	}
//	//(2)�����׽���
//	m_SockClt = socket(AF_INET, SOCK_STREAM, 0);
//	if (m_SockClt == INVALID_SOCKET)
//	{
//		cout << "socket() fail:" << WSAGetLastError() << endl;
//		return;
//	}
//	//(3)����IP�Լ��˿�
//	SOCKADDR_IN addrSrv;
//	addrSrv.sin_family = AF_INET;
//	addrSrv.sin_addr.s_addr = inet_addr("172.20.32.62");
//	addrSrv.sin_port = htons(8000);
//
//	//(5)�������������������
//	err = connect(m_SockClt, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
//
//	if (err == INVALID_SOCKET)
//	{
//		cout << "���ӷ�����ʧ��" << WSAGetLastError() << endl;
//		return;
//	}
//}
//
//void TCPSender::Send(const char *buf,int len)
//{
//	char* sendBuf, hostname[100];
//	sendBuf = new char[len];
//	strcpy_s(sendBuf, len, buf);
//
//	send(m_SockClt, sendBuf, strlen(sendBuf), 0);
//}
//
//void TCPSender:: Receive()
//{
//	int	iLen;
//	char recvBuf[1024] = "\0";
//	while(recv(m_SockClt, recvBuf, 1024, 0)>0)
//	{
//		
//	}
//
//	if (iLen == SOCKET_ERROR)
//	{
//		cout << "���շ�������Ϣʧ��" << WSAGetLastError() << endl;
//		return;
//	}
//	else
//	{
//		recvBuf[iLen] = '\0';
//		cout << recvBuf << endl;
//	}
//	closesocket(m_SockClt);
//
//	WSACleanup();
//}