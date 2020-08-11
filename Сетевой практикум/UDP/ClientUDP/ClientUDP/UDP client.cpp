// пример простого UDP-клиента​

#define _WINSOCK_DEPRECATED_NO_WARNINGS​
#include <winsock2.h>​
//#include "stdafx.h"​
#include <string>​
#include <windows.h>​
#include <iostream>​

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)​

using namespace std;

#define PORT 666​
#define SERVERADDR "127.0.0.1" // IP-адрес сервера​

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


int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "rus");
	char buff[10 * 1014];
	cout << "UDP Demo Client\nType quit to quit \n";

	// Шаг 1 - иницилизация библиотеки Winsocks​
	if (WSAStartup(0x202, (WSADATA *)&buff)) {
		cout << "WSASTARTUP ERROR: " << WSAGetLastError() << "\n";
		return -1;
	}

	// Шаг 2 - открытие сокета​
	SOCKET my_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (my_sock == INVALID_SOCKET) {
		cout << "SOCKET() ERROR: " << WSAGetLastError() << "\n";
		WSACleanup();
		return -1;
	}

	// Шаг 3 - обмен сообщений с сервером​
	HOSTENT *hst;
	sockaddr_in Daddr;
	Daddr.sin_family = AF_INET;
	//Daddr.sin_port = htons(PORT);
	Daddr.sin_port = htons(666);

	// определение IP-адреса узла​
	if (inet_addr(SERVERADDR)) {
		Daddr.sin_addr.s_addr = inet_addr(SERVERADDR);
	}
	else {
		if (hst = gethostbyname(SERVERADDR)) {
			Daddr.sin_addr.s_addr = ((unsigned long **)hst->h_addr_list)[0][0];
		}
		else {
			cout << "Unknown Host: " << WSAGetLastError() << "\n";
			closesocket(my_sock);
			WSACleanup();
			return -1;
		}
	}

	student msg;
	while (1) {
		// чтение сообщения с клавиатуры​
		cout << "S<=C:" << endl;

		cout << "Ваше имя: ";
		cin >> msg.name;
		cout << "Первая оценка: ";
		cin >> msg.firstMark;
		cout << "Вторая оценка: ";
		cin >> msg.secondMark;
		cout << "Третья оценка: ";
		cin >> msg.thirdMark;
		cout << "Четвертая оценка: ";
		cin >> msg.fourthMark;


		// Передача сообщений на сервер​
		sendto(my_sock, (char*)&msg, sizeof(student), 0,(sockaddr *)&Daddr, sizeof(Daddr));

		// Прием сообщения с сервера​
		sockaddr_in SRaddr;
		int SRaddr_size = sizeof(SRaddr);
		//int n = recvfrom(my_sock, buff, sizeof(buff), 0,(sockaddr *)&SRaddr, &SRaddr_size);
		answerStruck answer;
		int n = recvfrom(my_sock, (char*)&answer, sizeof(answerStruck), 0, (sockaddr *)&SRaddr, &SRaddr_size);

		if (n == SOCKET_ERROR) {
			cout << "RECVFROM() ERROR:" << WSAGetLastError() << "\n";
			closesocket(my_sock);
			WSACleanup();  return -1;
		}

		//buff[n] = '\0';

		cout << "Имя студента: " << answer.name << "." << endl;
		cout << "Количество долгов: " << answer.debt << "." << endl;
		cout << "Степендия: " << answer.st << "." << endl;
		cout << endl;

		cout << "Выйти ";
		string mst;
		cin >> mst;

		if (mst == "yes") break;
	}

	// шаг последний - выход​

	closesocket(my_sock);
	WSACleanup(); 
	return 0;
}



