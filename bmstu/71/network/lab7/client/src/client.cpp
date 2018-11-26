#include <winsock.h>
#include <stdio.h>
#include <conio.h>
#include <io.h>

int main()
{
	int rc, size, symbols, y = 0, i = 1; //�������� ����������, ������� ��� ���������� �����, ����� ��������� ��������, �������.   
	WSADATA wsd;
	//�������������� ���������� ��� ����������
	WSAStartup(0X0101, &wsd);
	//������������� ������ � ������ �������/������� TCP
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	//�������� ���������
	sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(1200);
	peer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//������������� �������
	rc = connect(s, (struct sockaddr*) &peer, sizeof(peer));
	if (rc < 0) printf("error");

	FILE *f;
	f = fopen("pic.png", "rb");

	while (!feof(f)) //���� �� ����� �����, �������� ������� ���� (������� ���������� � ������)
	{
		char bufer[100];
		symbols = fread(bufer, 1, 100, f);//� ����� ���� ��� ����������� 100 ���� �� �����, ���������� ����� ��������
		size = ftell(f);//������� ���������� ������� �������
		printf("read symbols: %d, part: %d, pos: %ld \n", symbols, i, size);
		printf("\n");
		send(s, bufer, symbols, 0);//�������� ����������� ������
		i++;
		char buf[100];//��� ������ ��������� �������
		y = recv(s, buf, sizeof(buf), 0);//����� ������ ������� (sizeof(buf) - ����������� ��������� �������� �����)
		printf("%s\n", buf);
	}
	fclose(f);
	getch();
	// ���������� ����������
	shutdown(s, 2);
	WSACleanup();
	return 0;
}