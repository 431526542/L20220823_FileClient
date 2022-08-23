#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include<WinSock2.h>
#include<string>
#include <fstream>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSAData WseData;

	WSAStartup(MAKEWORD(2, 2), &WseData);


	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN ServerSOCKADDR;
	memset(&ServerSOCKADDR, 0, sizeof(SOCKADDR_IN));
	ServerSOCKADDR.sin_family = PF_INET;
	ServerSOCKADDR.sin_addr.s_addr = inet_addr("192.168.10.141");
	ServerSOCKADDR.sin_port = htons(4000);

	int Result = connect(ServerSocket, (SOCKADDR*)&ServerSOCKADDR, sizeof(SOCKADDR_IN));//바인드가아닌 컨넥트 한다.
	if (Result == SOCKET_ERROR)
	{
		cout << "fail connect : " << GetLastError() << endl;
		exit(-1);
	}

	//파일 정보 받기1
	ofstream WriteFile("this.png", ifstream::binary);//출력용
	if (WriteFile.is_open())
	{
		char* Buffer = new char[55000];

		int RecvSize = recv(ServerSocket, Buffer, 55000, 0);

		WriteFile.write(Buffer, RecvSize);

		delete[] Buffer;
		Buffer = nullptr;
	}
	WriteFile.close();

	//파일 정보 받기2
	/*
	ofstream WriteFile("this.png", ifstream::binary);//출력용
	if (WriteFile.is_open())
	{
		char* Buffer = new char[55000];
		int ReadSize = 0;
		do
		{
			ReadSize = recv(ServerSocket, Buffer, ReadSize, 0);
			WriteFile.write(Buffer, ReadSize);
		} while (ReadSize > 0);

		delete[] Buffer;
		Buffer = nullptr;
	}
	fclose(WriteFile);*/


	closesocket(ServerSocket);
	WSACleanup();

	return 0;
}