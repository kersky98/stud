#include<stdio.h>
#include<winsock2.h>

#define SERVER "127.0.0.1"  //ip address of udp server
#define BUFLEN1 512  //Max length of buffer
#define BUFLEN2 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data
struct student{
	char Name[BUFLEN1];
	char Surname[BUFLEN2];
};

int main(void)
{
	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf1[BUFLEN1];
	char buf2[BUFLEN2];
	student mas[1];
	WSADATA wsa;

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	//start communication
	while (1)
	{
		printf("\nEnter Name: ");
		gets(mas[0].Name);
		printf("Enter Surname: ");
		gets(mas[0].Surname);

		//send the message
		if (sendto(s, mas[0].Name, strlen(mas[0].Name), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		if (sendto(s, mas[0].Surname, strlen(mas[0].Surname), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}


		memset(buf1, '\0', BUFLEN1);
		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf1, BUFLEN1, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		puts(buf1);

		memset(buf2, '\0', BUFLEN2);
		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf2, BUFLEN2, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		puts(buf2);

	}

	closesocket(s);
	WSACleanup();

	return 0;
}

