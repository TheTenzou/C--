#include <iostream>
#include <fstream>
#include <string>

using namespace std;

std::ifstream::pos_type filesize(const char* filename)
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

int main()
{
	cout << "Server is running!" << endl;
	int f = 1;
	while (f)
	{
		if (filesize("D:\\C++ projects\\server_binary"))
		{
			ifstream server;
			server.open("D:\\C++ projects\\server_binary", ios::binary);
		
			string name;
			size_t size;
			server.read((char*)&size, sizeof(size));
			name.resize(size);
			server.read(&name[0], size);
			cout << name << endl;

			ofstream output;
			output.open("D:\\C++ projects\\" + name + ".txt");

			int count = 0;
			int tmp;
			for (int i = 0; i < 4; ++i)
			{
				server.read((char*)&tmp, sizeof(tmp));
				cout << tmp << ' ';
				//if (tmp < 3) ++count;
			}
			cout << endl;
			output << count;

			output.close();
			server.close();

			ofstream ofs;
			ofs.open("D:\\C++ projects\\server_binary", ofstream::out | ofstream::trunc);
			ofs.close();
		}
	}
	system("pause");
	return 0;
}