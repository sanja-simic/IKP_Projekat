// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// TCP veza klijenta i servera

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "conio.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib") 

// serverski port 5059
#define SERVER_IP_ADDRESS "127.0.0.1"
#define SERVER_PORT 5059
#define BUFFER_SIZE 256

int main()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartup failed with error: %d\n", WSAGetLastError());
		return 1;
	}

	int iResult;

	SOCKET connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	char dataBuffer[BUFFER_SIZE];

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);
	serverAddress.sin_port = htons(SERVER_PORT);

	iResult = connect(connectSocket, (SOCKADDR*)&serverAddress,
		sizeof(serverAddress));
	if (iResult == SOCKET_ERROR)
	{
		printf("Unable to connect to server.\n");
		closesocket(connectSocket);
		WSACleanup();
		return -4;
	}

	do {
		printf("Send message to server: ");
		gets_s(dataBuffer, BUFFER_SIZE);
		iResult = send(connectSocket, dataBuffer, (int)strlen(dataBuffer), 0);
		if (iResult == SOCKET_ERROR) {
			printf("Message is successfull sent!\n");
			return -5;
		}

	} while (strcmp(dataBuffer, "End") != true);

	shutdown(connectSocket, SD_BOTH);
	closesocket(connectSocket);
	WSACleanup();
	return 0;
}
