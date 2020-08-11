// CLIENT_CHAT_with threads
//#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")
// #pragma warning(disable: 4996)

using namespace std;
SOCKET Connection;
int reciveMsg = 1;

enum Packet {
    Pack,
    Test,
	Quit,
	Private
};

DWORD WINAPI ClientThread(LPVOID sock) {
    SOCKET Con = ((SOCKET*)sock)[0]; 
    Packet packettype;

    while (reciveMsg) {
        recv(Con, (char*)&packettype, sizeof(Packet), NULL);
        if (packettype == Pack)
        {
            //cout << "type packet=PACK" << endl;
			//Получение сообшения от клиента
            int msg_size;
            recv(Con, (char*)&msg_size, sizeof(int), NULL);
            char* msg = new char[msg_size + 1];
			msg[msg_size] = 0;
            recv(Con, msg, msg_size, NULL);
            cout << msg << endl;
            delete[] msg;
        }
        else {
			if (packettype == Test) {
				//cout << "Test packet.\n";
			}
            else {
                cout << "Unrecognized packet tread: " << packettype << endl;
                break;
            }
        }
    }
    closesocket(Connection);
    return 0;
}

int main() {    // with threads
    WSAData wsaData;     
    WORD Ver = MAKEWORD(2, 1);
    
    if (WSAStartup(Ver, &wsaData) != 0) {
        cout << "Error" << endl;         
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1024);
    addr.sin_family = AF_INET;
    Connection = socket(AF_INET, SOCK_STREAM, NULL);

    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        cout << "Error: failed connect to server.\n";
        return 1;
    }

    cout << "Connected!\n";
    CreateThread(NULL, NULL, ClientThread, &Connection, NULL, NULL);

	// Ввод ника
	string nick;
	cout << " Please enter your nick: ";
	//cin >> nick;
	getline(cin, nick);
	int nickSize = nick.size();
	Packet packettype = Pack;
	send(Connection, (char*)&packettype, sizeof(Packet), NULL);
	send(Connection, (char*)&nickSize, sizeof(int), NULL);
	send(Connection, (char*)&nick[0], nickSize, NULL);

    string msg1;
    while (true) {
        getline(cin, msg1);
        //cin >> msg1;
        int msg_size = msg1.size();

		// Обработка команд
		if (msg1[0] == '/') {
			//cout << msg1.substr(1, 12) << endl;
			//Выход
			if (!msg1.substr(1,4).compare("quit")) {
				Packet packettype = Quit;
				send(Connection, (char*)&packettype, sizeof(Packet), NULL);
				reciveMsg = 0;
				closesocket(Connection);
				exit(0);
				//break;
			}
			// Помощ
			else if (!msg1.substr(1, 4).compare("help")) {
				cout << "=================================================" << endl;
				cout << "/help - type get help" << endl;
				cout << "/private msg [name of the reciver] [message text]" << endl;
				cout << "/quit - type to exit" << endl;
				cout << "=================================================" << endl;
			}
			// Личное сообшени
			else if (!msg1.substr(1, 12).compare("private msg ")) {

				Packet packettype = Private;
				msg1 = msg1.substr(13, msg1.length() - 1);
				msg_size -= msg1.size();

				string nickReciver = msg1.substr(0, msg1.find(' '));
				int nickSize = nickReciver.size();
				msg1 = msg1.substr(msg1.find(' ') + 1, msg1.length());
				msg_size = msg1.size();

				send(Connection, (char*)&packettype, sizeof(Packet), NULL);
				send(Connection, (char*)&nickSize, sizeof(int), NULL);
				send(Connection, (char*)&nickReciver[0], nickSize, NULL);
				send(Connection, (char*)&msg_size, sizeof(int), NULL);
				send(Connection, (char*)&msg1[0], msg_size, NULL);
			}
			else {
				cout << "Wrong comand. Try to use /help" << endl;
			}
		}
		// стандартное сообшение всем
		else {
			Packet packettype = Pack;
			send(Connection, (char*)&packettype, sizeof(Packet), NULL);
			send(Connection, (char*)&msg_size, sizeof(int), NULL);
			send(Connection, (char*)&msg1[0], msg_size, NULL);
		}
		Sleep(10);
    }
    system("pause");
    return 0;
}     
