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
	int f = 1;
	while (f)
	{
		if (filesize("D:\\C++ projects\\server.txt"))
		{
			ifstream server;
			server.open("D:\\C++ projects\\server.txt");
		
			string name;
			server >> name;

			ofstream output;
			output.open("D:\\C++ projects\\" + name + ".txt");

			int count = 0;
			int tmp;
			for (int i = 0; i < 4; ++i)
			{
				server >> tmp;
				if (tmp < 3) ++count;
			}
			output << count;

			output.close();
			server.close();

			ofstream ofs;
			ofs.open("D:\\C++ projects\\server.txt", ofstream::out | ofstream::trunc);
			ofs.close();
		}
	}
	system("pause");
	return 0;
}