#include <WinSock2.h>
#include <iostream>
#include <string>

#pragma comment (lib, "Ws2_32.lib") // настраиваем линкер
#pragma warning(disable : 4996)	// для работы gethostbyname

using namespace std;

u_short MY_PORT = 666; // Порт, слушающий сервер

// макрос печает кол-во пользователей онлайн
#define PrintUsers if (nclients) std::cout << endl <<"users online: " << nclients << endl; \
				   else std::cout<< endl<< "No users online\n";

DWORD WINAPI ConToClient(LPVOID client_socket);
int nclients = 0;

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
	if (WSAStartup(0x0202, (WSADATA *)&buff[0])) {
		std::cout << "Initialization Error" << endl << WSAGetLastError(); // ошибка инициализации
		return -1;
	}

	// Создаём сокет
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		std::cout << "Error socket" << endl << WSAGetLastError();
		WSACleanup();
		return -1;
	}

	// Свяжем сокет с локальным адресом
	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(MY_PORT);
	local_addr.sin_addr.s_addr = 0;

	//bind для связывания
	if (bind(s, (sockaddr *)&local_addr, sizeof(local_addr))) {
		std::cout << "Error bind" << endl << WSAGetLastError();
		WSACleanup();
		return -1;
	}

	// Ожидаем подключение к серверу. Очередь размера 0х100
	if (listen(s, 0x100)) {
		std::cout << "Error listen" << endl << WSAGetLastError();
		WSACleanup();
		return -1;
	}
	std::cout << "Waiting for connections" << endl;

	// Извлечение сообщения из очреди
	SOCKET client;
	sockaddr_in client_addr;
	int client_addr_size = sizeof(client_addr);

	while ((client = accept(s, (sockaddr*)&client_addr, &client_addr_size)))
	{
		nclients++;
		HOSTENT *hst;
		hst = gethostbyaddr((char *)&client_addr.sin_addr.s_addr, 4, AF_INET);
		std::cout << endl << "One new client!" << endl;
		if (hst) { 
			std::cout << hst->h_name;
		}
		else {
			std::cout << "";
		}
		std::cout << inet_ntoa(client_addr.sin_addr);
		PrintUsers
			std::cout << endl;

		// Вызываем новый поток для обслуживания клиента
		DWORD thID;
		CreateThread(NULL, NULL, ConToClient, &client, NULL, &thID);  // Создаёт поток, выполняющийся в пределах виртуального адресного пространства вызывающиего процесса
		/* 1ый парам - дескриптор защиты. NULL - дескриптор не может быть унаследован
		   2ой - начальный размер стека. NULL - по дефолту размер стека исполняемой проги. В случае необх. размер стека растёт
		   3ий - функция потока
		   4ый - параметр потока
		   5ый - опции создания. NULL - поток запускается немедленно после создания
		   6ой - ID потока */

	}
	return 0;
}

// Обслуживает очередного подключившегося клиента независимо от остальных
DWORD WINAPI ConToClient(LPVOID client_socket)
{
	SOCKET my_sock;
	int len;
	char buff[1024];
	string mess = " ";
	Student* msg;
	char name[20] = "default";
	AnswerStruck answer;
	strcpy(answer.nickName, "default");
	answer.debt = -1;

	my_sock = ((SOCKET *)client_socket)[0];
	send(my_sock, (char *)&answer, sizeof(AnswerStruck), 0);

	//цикл эхо-сервера
	while (SOCKET_ERROR != (len = recv(my_sock, (char *)buff, 1024, 0)))
	{
		msg = (Student *)buff;
		strcpy(name, msg->nickName);
		if (msg->firstMark == -1) {
			break;
		}

		std::cout << endl << "Пользователь: " << msg->nickName << endl << " Результаты для " << msg->name << endl;
		// обрабатываем выходную информацию
		
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
		std::cout << "Имя студента: " << answer.name << "." << endl;
		std::cout << "Количество долгов: " << answer.debt << "." << endl;
		std::cout << "Степендия: " << answer.st << "." << endl;

		int answerSize = sizeof(answer);
		send(my_sock, (char *)&answer, answerSize, 0);


	}

	// Соединение с клиентом разорвано
	nclients--;
	std::cout << endl << "User: " << name << " is disconneted" << endl;
	PrintUsers
		closesocket(my_sock);
	std::system("pause");
	return 0;
}

