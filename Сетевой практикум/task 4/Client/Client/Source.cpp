#include <WinSock2.h>
#include <iostream>
#include <string>

#pragma comment (lib, "Ws2_32.lib") // настраиваем линкер
#pragma warning(disable : 4996)	// для работы gethostbyname

using namespace std;

#define PORT 666
#define SERVERADDR "127.0.0.1"

struct Student {
	char nickName[20];
	char name[20];
	int firstMark;
	int secondMark;
	int thirdMark;
	int fourthMark;
};

struct AnswerStruck {
	char nickName[20];
	char name[20];
	int debt;
	int st;
};

int main()
{
	setlocale(LC_ALL, "rus");
	char buff[1024];

	// Инициализруем Библиотеку Сокетов
	if (WSAStartup(0x0202, (WSADATA *)&buff[0]))
	{
		cout << "Initialization Error" << endl << WSAGetLastError(); // ошибка инициализации
		return -1;
	}

	// Создаём сокет
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
	{
		cout << "Error socket" << endl << WSAGetLastError();
		WSACleanup();
		system("pause");
		return -1;
	}

	// Установка соединения
	sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(PORT);
	HOSTENT *hst;

	// Преобразуем IP из символьного в сетевой формат
	if (inet_addr(SERVERADDR) != INADDR_NONE) dest_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
	else if (hst = gethostbyname(SERVERADDR)) ((unsigned long *)&dest_addr.sin_addr)[0] = ((unsigned long **)hst->h_addr_list)[0][0]; // Попытка получить IP по доменному имени сервера. 
		 // hst->h_addr_list - содержит массив указателей на адреса
	else
	{
		cout << "Invalid address" << endl << SERVERADDR;
		closesocket(s);
		WSACleanup();
		system("pause");
		return -1;
	}

	// Устанавливаем соединение
	if (connect(s, (sockaddr *)&dest_addr, sizeof(dest_addr)))
	{
		cout << "Connection error" << endl << WSAGetLastError();
		system("pause");
		return -1;
	}
	cout << " Successfully connected with " << SERVERADDR << endl << " Type quit to exit" << endl;

	// Чтение и передача сообщений
	int nsize, flag = 1;
	string mes;
	Student msg;

	cout << " Enter your nickname: "; cin >> msg.nickName;
	while ((nsize = recv(s, (char *)buff, 1024, 0)) != SOCKET_ERROR)
	{
		
		AnswerStruck *answer = (AnswerStruck *)&buff;
		if (answer->debt != -1) {
			cout << "Имя студента: " << answer->name << "." << endl;
			cout << "Количество долгов: " << answer->debt << "." << endl;
			cout << "Степендия: " << answer->st << "." << endl;
			cout << endl;
		}


		cout << endl << "Введеи данные: ";

		cout << "Ваше имя: ";
		cin >> msg.name;
		if (!strcmp(msg.name, "quit")) {
			strcpy(msg.name,"");
			msg.firstMark = -1;
			msg.secondMark = -1;
			msg.thirdMark = -1;
			msg.fourthMark = -1;

			int msgSize = sizeof(msg);
			send(s, (char *)&msg, msgSize, 0);

			cout << "Goodbye" << endl;
			closesocket(s);
			WSACleanup();
			system("pause");
			return 0;
		}
		else {
			cout << "Первая оценка: ";
			cin >> msg.firstMark;
			cout << "Вторая оценка: ";
			cin >> msg.secondMark;
			cout << "Третья оценка: ";
			cin >> msg.thirdMark;
			cout << "Четвертая оценка: ";
			cin >> msg.fourthMark;
		}

		int msgSize = sizeof(msg);
		send(s, (char *)&msg, msgSize, 0);

		

	}

	cout << "Recieve error" << endl << WSAGetLastError();
	closesocket(s);
	WSACleanup();
	system("pause");
	return -1;
}