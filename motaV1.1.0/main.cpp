#include <iostream>

#include "HttpSender.h"
#include "GameController.h"
#include "Guests.h"
//HttpSender.h�ļ���Ҫλ��GameController.h֮ǰ

using namespace std;


int main(int argc, char* argv[])
{
	GameController* gameController=new GameController;
	gameController->GameRun();

	return 0;
}


/*
�򵥹���:��һ
���󹤳�:

C++��Ŀ:���ģʽ����̬���顢��װ���̳С���̬
1.Ӣ���ƶ���ս��������
2.��ͼ���л�(��̬����)
3.�ļ���д fread fwrite
4.��Ʒ��ʰȡ������ʹ�á�
5.װ��
6.����

*/

