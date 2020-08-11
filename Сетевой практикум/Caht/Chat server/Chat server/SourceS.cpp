// server_chat
//#include <stdafx.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
using namespace std;

SOCKET Connections[100];
int Counter = 0;
string tableOfNicks[100];

enum Packet { 
	Pack,
	Test,
	Quit,
	Private
};

string toString(char* a) {
	string s(a);
	return s;
}

DWORD WINAPI ServerThread(LPVOID number)
{
    Packet packettype;
    int index = ((int*)number)[0];
    cout << "socket number=" << index << endl;
    SOCKET Con = Connections[index];

    while (true) {

        recv(Con, (char*)&packettype, sizeof(Packet), NULL);

		//общие сообшения
        if (packettype == Pack) {
            cout << "get packet PACK" << endl;

			//получение сообшения
            int msg_size;
            recv(Con, (char*)&msg_size, sizeof(int), NULL);
            char* msg = new char[msg_size + 1];
            msg[msg_size] = 0;
			recv(Con, msg, msg_size, NULL);
			
			//Обработка сообшения
			string newMsg(tableOfNicks[index]);
			newMsg += ": ";
			newMsg += msg;
			int newMsgSize = newMsg.size();
            cout << newMsg << endl;

			//Отправление сообшения всем остальным
            for (int i = 0; i < Counter; i++) {
                if (i == index) {
                    continue;
                }
                Packet msgtype = Pack;
                send(Connections[i], (char*)&msgtype, sizeof(Packet), NULL);
                send(Connections[i], (char*)&newMsgSize, sizeof(int), NULL);
                send(Connections[i], (char*)&newMsg[0], newMsgSize, NULL);
            }
            delete[] msg;
        }
		//Отключение
		else if (packettype == Quit) {
			cout << "get packet QUIT" << endl;
			//Обработка сообшения о отключении
			string disconectMessage(tableOfNicks[index]);
			disconectMessage += " disconnected!";
			int disconectMessageSize = disconectMessage.size();

			cout << disconectMessage << endl;

			//Отправление сообшения всем остальным
			for (int j = 0; j < Counter; j++) {
				if (index == j) {
					continue;
				}
				Packet msgtype = Pack;
				send(Connections[j], (char*)&msgtype, sizeof(Packet), NULL);
				send(Connections[j], (char*)&disconectMessageSize, sizeof(int), NULL);
				send(Connections[j], (char*)&disconectMessage[0], disconectMessageSize, NULL);
			}
			break;
		}
		// Личные сообшения
		else if (packettype == Private) {
			cout << "get packet PRIVATE" << endl;

			//Получение ника
			int msg_size;
			recv(Con, (char*)&msg_size, sizeof(int), NULL);
			char* msg = new char[msg_size + 1];
			msg[msg_size] = 0;
			recv(Con, msg, msg_size, NULL);
			string nickName = msg;

			//получение сообшения
			recv(Con, (char*)&msg_size, sizeof(int), NULL);
			msg = new char[msg_size + 1];
			msg[msg_size] = 0;
			recv(Con, msg, msg_size, NULL);
			string message = msg;
			
			//Оработка сообшения
			string newMsg("Private message from ");
			newMsg += tableOfNicks[index];
			newMsg += ": ";
			newMsg += message;
			int newMsgSize = newMsg.size();
			cout << newMsg << endl;

			for (int i = 0; i < Counter; i++) {
				if (!tableOfNicks[i].compare(nickName)) {
					Packet msgtype = Pack;
					send(Connections[i], (char*)&msgtype, sizeof(Packet), NULL);
					send(Connections[i], (char*)&newMsgSize, sizeof(int), NULL);
					send(Connections[i], (char*)&newMsg[0], newMsgSize, NULL);
				}
			}
			delete[] msg;
		}
        else {
            cout << "Unrecognized packet tread: " << packettype << endl;
			break;
        }
    }
    closesocket(Con);
    return 0;
}

int main() {
    //WSAStartup
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        cout << "Error" << endl;
        exit(1);
    }
    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1024);
    addr.sin_family = AF_INET;

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, 10);
    SOCKET newConnection;

    for (int i = 0; i < 10; i++) {

        newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
        if (newConnection == 0) { 
            cout << "Error #2\n"; 
        }
        else {
			//получам имя пользователя
			Packet packettype;
			recv(newConnection, (char*)&packettype, sizeof(Packet), NULL);
			if (packettype == Pack) {

				//Получаем имя пользователя
				int msg_size;
				recv(newConnection, (char*)&msg_size, sizeof(int), NULL);
				char* nick = new char[msg_size + 1];
				nick[msg_size] = 0;
				recv(newConnection, nick, msg_size, NULL);
				cout << nick << " connected!\n";
				tableOfNicks[i] = nick;

				// Сообшение приветсвия
				string greatingMessage(tableOfNicks[i]);
				greatingMessage += " connected!";
				int greatingMessageSize = greatingMessage.size();

				// Отправка приветствия всем
				for (int j = 0; j < Counter; j++) {
					if (i == j) {
						continue;
					}
					Packet msgtype = Pack;
					send(Connections[j], (char*)&msgtype, sizeof(Packet), NULL);
					send(Connections[j], (char*)&greatingMessageSize, sizeof(int), NULL);
					send(Connections[j], (char*)&greatingMessage[0], greatingMessageSize, NULL);
				}
			}

			// Приветсвие для подключившегося пользователя
            string msg = "Welcome to chat!";
            int msg_size = msg.size();
            Packet msgtype = Pack;
            send(newConnection, (char*)&msgtype, sizeof(Packet), NULL);
            send(newConnection, (char*)&msg_size, sizeof(int), NULL);
            send(newConnection, (char*)&msg[0], msg_size, NULL);
            Connections[i] = newConnection;
            Counter++;     
            cout << "count=" << Counter << endl;
			int tmpInt = i;
            CreateThread(NULL, NULL, ServerThread, &tmpInt, NULL, NULL);
            Packet testpacket = Test;
            cout << "type packet=TEST" << endl;
            send(newConnection, (char*)&testpacket, sizeof(Packet), NULL);
        }
    }
    system("pause");
    return 0;
}
