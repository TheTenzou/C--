#include <string>
#include <winsock2.h>
#include <iostream>
#pragma comment (lib,"Ws2_32.lib")
#pragma warning(disable: 4996)
using namespace std;
#define _WINSOCK_DEPRCATED_NO_WARNINGS
#define request "get/ http/1.1\r\n host: www.itcorp.com \r\n\r\n" //http ������.
#define max_packet_size         65535

int main()
{
	WSADATA         ws;
	SOCKET          s;
	sockaddr_in     adr;
	HOSTENT*        hn;
	char            buff[max_packet_size];

	// init
	if (WSAStartup(0x0202, &ws) != 0)
	{
		// error
		return -1;
	}

	// ������ �����
	if (INVALID_SOCKET == (s = socket(AF_INET, SOCK_STREAM, 0)))
	{
		// error
		return -1;
	}


	// �������� �����
	if (NULL == (hn = gethostbyname("www.itcorp.com")))//gethostbyname
	{
		// error
		return -1;
	}

	// ���������  ���� ��������� adr ��� ������������� �� � connect
	adr.sin_family = AF_INET;
	((unsigned long *)&adr.sin_addr)[0] = ((unsigned long **)hn->h_addr_list)[0][0];
	adr.sin_port = htons(80);

	// ������������� ���������� � ��������
	if (SOCKET_ERROR == connect(s, (sockaddr*)&adr, sizeof(adr)))
	{
		// error
		int res = WSAGetLastError();
		//return -1;
	}

	// �������� ������ �������
	if (SOCKET_ERROR == send(s, (char *)&request, sizeof(request), 0))
	{
		// error
		int res = WSAGetLastError();
		return -1;
	}


	// ��� ������
	int len = 0;
	do
	{
		if (SOCKET_ERROR == (len = recv(s, (char *)&buff, max_packet_size, 0)))
		{
			int res = WSAGetLastError();
			return -1;
		}
		for (int i = 0; i < len; i++)
			cout << buff[i];

	} while (len != 0); //�������� ������ �� ������, ���� �� len != 0.

	if (SOCKET_ERROR == closesocket(s))   // ��������� ���������� 
	{                // error
		return -1;
	}

	cin.get();

	return 1;

}
