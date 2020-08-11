//#include <stdafx.h> // CLIENT TCP
#include <iostream>  
#define _WINSOCK_DEPRECATED_NO_WARNINGS  // ���������� �������������� ���������� winsock2
#include <winsock2.h> 
#include <string>
#include <windows.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma warning(disable: 4996)  // ���������� �������������� 4996 

using namespace std;
#define _WINSOCK_DEPRECATED_NO_WARNINGS  // ���������� �������������� ���������� winsock2
#define SRV_HOST "localhost"  
#define SRV_PORT 1234 
#define CLNT_PORT 1235  
#define BUF_SIZE 64  

char TXT_ANSW[] = "I am your student\n";

struct student {
	char name[20];
	int firstMark;
	int secondMark;
	int thirdMark;
	int fourthMark;
};

struct answerStruck {
	char name[20];
	int debt;
	int st;
};

int main() {

	setlocale(LC_ALL, "rus");

	char buff[1024];

	if (WSAStartup(0x0202, (WSADATA *)&buff[0])) {
		cout << "Error WSAStartup \n" << WSAGetLastError();  // ������!
		return -1;
	}

	//SOCKET s;
	int from_len;   
	char buf[BUF_SIZE] = { 0 };    
	//hostent * hp;
	sockaddr_in clnt_sin, srv_sin;

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	clnt_sin.sin_family = AF_INET;
	clnt_sin.sin_addr.s_addr = 0;
	clnt_sin.sin_port = htons(CLNT_PORT);
	bind(s, (sockaddr *)&clnt_sin, sizeof(clnt_sin));

	

	srv_sin.sin_port = htons(SRV_PORT);
	srv_sin.sin_family = AF_INET;
	//((unsigned long *)&srv_sin.sin_addr)[0] = ((unsigned long **)hp->h_addr_list)[0][0]; // ������������ ����
	//hostent * hp = gethostbyname(SRV_HOST); // 
	srv_sin.sin_addr.s_addr = inet_addr("192.168.1.7");

	connect(s, (sockaddr *)&srv_sin, sizeof(srv_sin));//��������� ��������� ����� � ��������

	string mst;
	student msg;
	do {
		from_len = recv(s, (char *)&buf, BUF_SIZE, 0); //��������� �� �������, from_len ���������� ��������� ������
		buf[from_len] = 0; //�������� ����� ������
		cout << buf << endl;


		cout << "���� ���: ";
		cin >> msg.name;
		cout << "������ ������: ";
		cin >> msg.firstMark;
		cout << "������ ������: ";
		cin >> msg.secondMark;
		cout << "������ ������: ";
		cin >> msg.thirdMark;
		cout << "��������� ������: ";
		cin >> msg.fourthMark;

		int msgSize = sizeof(msg);
		send(s, (char *)&msg, msgSize, 0);

//		getline(cin, mst);						//
//		int msg_size = mst.size();				//����������� ��������� �������
//		send(s, (char *)& mst[0], msg_size, 0);	//

		recv(s, (char *)buf, BUF_SIZE, 0);
		answerStruck *answer = (answerStruck *)&buf;

		cout << "��� ��������: " << answer->name << "." << endl;
		cout << "���������� ������: " << answer->debt << "." << endl;
		cout << "���������: " << answer->st << "." << endl;
		cout << endl;
		
		cout << "����� ";
		cin >> mst;
		send(s, (char *)&mst[0], mst.size(), 0);

	} while (mst != "Yes"); 

	cout << "exit to infinity" << endl;
	cin.get();   
	closesocket(s);
	system("pause");
	return 0;
}
