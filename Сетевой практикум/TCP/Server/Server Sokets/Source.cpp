// SERVER TCP 
//#include <stdafx.h> 
#include <iostream>  
#include <winsock2.h> 
#include <windows.h> 
#include <string.h> 
#include <string>

#pragma comment (lib, "Ws2_32.lib")  

using namespace std;

#define SRV_PORT 1234  
#define BUF_SIZE 64  

const string QUEST = "Здравствуйте\n";

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

	if (WSAStartup(0x0202, (WSADATA *)&buff[0])) //иницилизация win sockets
	{
		cout << "Error WSAStartup \n" << WSAGetLastError();   // Ошибка!
		return -1;
	}

	//SOCKET s; // 
	SOCKET s_new;

	int from_len;
	char buf[BUF_SIZE] = { 0 };

	sockaddr_in sin, from_sin;
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0); //серверный сокет
	sin.sin_family = AF_INET; //доменое имя
	sin.sin_addr.s_addr = 0; //адрес pc
	sin.sin_port = htons(SRV_PORT);//номер порта
	bind(s, (sockaddr *)&sin, sizeof(sin));//связываем s с sin

	string msg1;
	listen(s, 3); //обслуживание клитентов max 3 клиента

	while (1) {
		from_len = sizeof(from_sin); //размер
		s_new = accept(s, (sockaddr *)&from_sin, &from_len);//подгрудает нового клиента из s в from_sin
		cout << "new connected client! " << endl;
		msg1 = QUEST;

		while (1) {

			send(s_new, (char *)&msg1[0], msg1.size(), 0);//оправляем соообшение клиенту

			recv(s_new, (char *)buf, BUF_SIZE, 0);
			student *msg = (student *)&buf;

			answerStruck answer;
			strcpy_s(answer.name, msg->name);
			if (msg->firstMark > 4 && msg->secondMark > 4 && msg->thirdMark > 4 && msg->fourthMark > 4) {
				answer.debt = 0;
				answer.st = 2000;
			}
			else if (msg->firstMark > 3 && msg->secondMark > 3 && msg->thirdMark > 3 && msg->fourthMark > 3) {
				answer.debt = 0;
				answer.st = 1000;
			}
			else if (msg->firstMark > 2 && msg->secondMark > 2 && msg->thirdMark > 2 && msg->fourthMark > 2) {
				answer.debt = 0;
				answer.st = 0;
			}
			else {
				answer.debt = 0;
				answer.st = 0;
				if (msg->firstMark < 3) {
					answer.debt++;
				}
				if (msg->secondMark < 3) {
					answer.debt++;
				}
				if (msg->thirdMark < 3) {
					answer.debt++;
				}
				if (msg->fourthMark < 3) {
					answer.debt++;
				}
			}
			cout << "Имя студента: " << answer.name << "." << endl;
			cout << "Количество долгов: " << answer.debt << "." << endl;
			cout << "Степендия: " << answer.st << "." << endl;
			
			int answerSize = sizeof(answer);
			send(s_new, (char *)&answer, answerSize, 0);

			from_len = recv(s_new, (char *)&buf, BUF_SIZE, 0); //сообшение от сервера, from_len количество полученых байтов
			buf[from_len] = 0;
			string msg2 = (string)buf;
			if (msg2 == "Yes") {
				break;
			}
		}
		cout << "client is lost" << endl << endl;
		closesocket(s_new);//закрываем сокет
	}
	return 0;
}

