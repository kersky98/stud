#include<stdio.h>
#include<winsock2.h>
#include "stdlib.h"
#include <string>
#include "../include/convert.h"
#include <vector>
#include <iostream>
#include <conio.h>
#include <bitset>
#include <sstream>

#define BUFLEN1 2048  //Max length of buffer
#define BUFLEN2 2048  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data
struct ourmessage{
	char message1[BUFLEN1];
	char message2[BUFLEN2];
};

int main()
{
	SOCKET s;
	struct sockaddr_in server, si_other;
	int slen, recv_len;
	char buf1[BUFLEN1];
	char buf2[BUFLEN2];
	WSADATA wsa;
	ourmessage mas[1];
	char type='0';
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
		memset(buf1, '\0', BUFLEN1);

		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf1, BUFLEN1, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		while ((type != '1') && (type != '2') && (type != '3')){
			printf("\n\nInput radix of IP Adress (1-3)\n1)Binary number system\n2)Decimal number system\n3)Hexadecimal number system\n");
			scanf("%c", &type);
			if (type == '2')
				printf("IP adress: %s\n", buf1);
			else if (type == '1')
			{
				std::vector<int> splitAddress = split(buf1, ".");
				std::string bin = ip2Bin(splitAddress);
				std::cout << "IP adress: "<<bin << std::endl;
			}
			else if(type == '3'){
				std::vector<int> splitAddress = split(buf1, ".");
				std::string hex = ip2Hex(splitAddress);
				std::cout << "IP adress: " << hex << std::endl;

			}
			else printf("ERROR!");
			_flushall();
		}
		type = '0';

		//now reply the client with the same data
		if (sendto(s, buf1, recv_len, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		
		//clear the buffer by filling null, it might have previously received data
		memset(buf2, '\0', BUFLEN2);

		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf2, BUFLEN2, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		
		//print details of the client/peer and the data received
		printf("Internet adress: %s\n\n", buf2);

		//now reply the client with the same data
		if (sendto(s, buf2, recv_len, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	closesocket(s);
	WSACleanup();

	return 0;
}
