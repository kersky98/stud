#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int main(void)
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN] = { 0 };
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
    system("pause");
		return 1;
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
    system("pause");
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
    system("pause");
		return 1;
	}

	// Setup the TCP listening socket, ���������� ������ � ��������� �������
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
    system("pause");
		return 1;
	}

	freeaddrinfo(result);

  // ������������ ������� ��������
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
    system("pause");
		return 1;
	}

	// Accept a client socket, ����������� ��������� ������� ������� �� ������������ ����������
  printf("Waiting for data...");
  fflush(stdout);
  ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
    system("pause");
		return 1;
	}

	// No longer need server socket
	closesocket(ListenSocket);
  
  // Receive until the peer shuts down the connection
    do {

      iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
      if (iResult > 0) {
        printf("Bytes received: %d\n", iResult);

        // Echo the buffer back to the sender
        iSendResult = send(ClientSocket, recvbuf, iResult, 0);
        if (iSendResult == SOCKET_ERROR) {
          printf("send failed with error: %d\n", WSAGetLastError());
          closesocket(ClientSocket);
          WSACleanup();
          system("pause");
          return 1;
        }
        printf("Bytes sent: %d\n", iSendResult);
      }
      else if (iResult == 0)
        printf("Connection closing...\n");
      else  {
        printf("recv failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        system("pause");
        return 1;
      }

    } while (iResult > 0);

    printf("Text %s\n", recvbuf);

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
    system("pause");
		return 1;
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

  system("pause");

	return 0;
}