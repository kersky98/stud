#include <stdio.h>
#include <string.h>
#include<winsock2.h>
#include<conio.h>

#define SERVER "127.0.0.1"  //ip address of udp server
#define BUFLEN1 512  //Max length of buffer
#define BUFLEN2 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data

struct ourmessage{
	char message1[BUFLEN1];
	char message2[BUFLEN2];
};

int main(void)
{

	struct sockaddr_in si_other;
	int s, n, slen = sizeof(si_other);
	char buf1[BUFLEN1];
	char buf2[BUFLEN2];
	ourmessage mas[1];
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
		printf("\nInput number of string:\n");
		scanf("%d", &n);

		FILE *file;
		char *fname = "file.txt";
		char result_sting[512]; //Строка в 20 символов

		file = fopen(fname, "r");

		if (file == NULL)
		{
			printf("NO file! '%s'", fname);
			return 0;
		}

		int i = 0;
		char *real_tail;

		while (fgets(result_sting, sizeof(result_sting), file))
		{
			real_tail = "";
			
			if (result_sting[strlen(result_sting) - 1] == '\n')//проверяем является ли последний элемент в строке символом её окончания
			{
				real_tail = "\n";
				result_sting[strlen(result_sting) - 1] = '\0';
				i++;
			};// эта часть кода добавлена лишь для отображения символа конца строки в консоль без перевода на новую строку	
			
			if (i == n) break;
		}
		
		fclose(file);
		i = 0;
		while (result_sting[i] != ' ')
		{
			mas[0].message1[i] = result_sting[i];
			i++;
		}

		n = 0;
		i++;
		
		while (result_sting[i] != '\0') 
		{
			mas[0].message2[n] = result_sting[i];
			i++;
			n++;
		}

		
		//send the message
		if (sendto(s, mas[0].message1, i-n-1, 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		if (sendto(s, mas[0].message2, n, 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
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