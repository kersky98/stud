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

int main(int argc, char **argv)
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	//char *sendbuf = "hello!";
	char recvbuf[DEFAULT_BUFLEN];
  char message[DEFAULT_BUFLEN];
  int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
    system("pause");
    return 1;
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
    system("pause");
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
      system("pause");
			return 1;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
    system("pause");
		return 1;
	}

  printf("Enter message : ");
  gets(message);
    // Send an initial buffer
    iResult = send(ConnectSocket, message, (int)strlen(message), 0);
    if (iResult == SOCKET_ERROR) {
      printf("send failed with error: %d\n", WSAGetLastError());
      closesocket(ConnectSocket);
      WSACleanup();
      system("pause");
      return 1;
    }

    printf("Bytes Sent: %ld\n", iResult);

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
    	printf("shutdown failed with error: %d\n", WSAGetLastError());
    	closesocket(ConnectSocket);
    	WSACleanup();
       system("pause");
    	return 1;
    }

    // Receive until the peer closes the connection
    memset(recvbuf, '\0', DEFAULT_BUFLEN);
    do {

      iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
      if (iResult > 0){
        printf("Bytes received: %d\n", iResult);
      }
      else if (iResult == 0)
        printf("Connection closed\n");
      else
        printf("recv failed with error: %d\n", WSAGetLastError());

    } while (iResult > 0);

    puts(recvbuf);

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

  system("pause");

	return 0;
}