#include<stdio.h>
#include<winsock2.h>
#include "stdlib.h"

#define BUFLEN1 512  //Max length of buffer
#define BUFLEN2 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data
struct student{
	char Name[BUFLEN1];
	char Surname[BUFLEN2];
};

int main()
{
	SOCKET s;
	struct sockaddr_in server, si_other;
	int slen, recv_len;
	char buf1[BUFLEN1];
	char buf2[BUFLEN2];
	WSADATA wsa;
  student mas[1];

	slen = sizeof(si_other);

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	//Bind
	if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	puts("Bind done");

	//keep listening for data
	while (1)
	{
		printf("Waiting for data...");
		fflush(stdout);

		//clear the buffer by filling null, it might have previously received data
		memset(mas[0].Name, '\0', BUFLEN1);

		//try to receive some data, this is a blocking call
    if ((recv_len = recvfrom(s, mas[0].Name, BUFLEN1, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

    printf("\n\nName: %s\n", mas[0].Name);

		//now reply the client with the same data
    if (sendto(s, mas[0].Name, recv_len, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//clear the buffer by filling null, it might have previously received data
    memset(mas[0].Surname, '\0', BUFLEN2);

		//try to receive some data, this is a blocking call
    if ((recv_len = recvfrom(s, mas[0].Surname, BUFLEN2, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//print details of the client/peer and the data received
		//printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
    printf("Surname: %s\n\n", mas[0].Surname);

		//now reply the client with the same data
    if (sendto(s, mas[0].Surname, recv_len, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		FILE *f = fopen("struct.txt", "a");
    fprintf(f, "Name: %s\n", mas[0].Name);
    fprintf(f, "Surname: %s\n", mas[0].Surname);
		fclose(f);

	}

	closesocket(s);
	WSACleanup();

	return 0;
}
