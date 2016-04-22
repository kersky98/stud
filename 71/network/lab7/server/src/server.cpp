#include <winsock2.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
using namespace std;

int main()
{
	int rc, i = 1;
	WSADATA wsd;
	WSAStartup(0X0101, &wsd);
	FILE *f;
	//инициализаци€ сокета в случае сервера/клиента TCP. »нтернет, тип сокета TCP, протокол
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

  char filename[100] = { 0 };
  strcat(filename, "pic_new_");
  strcat(filename, __DATE__);
  strcat(filename, ".png");

	//структура дл€ инициализаци€ сервера
	struct sockaddr_in myCom;
	myCom.sin_family = AF_INET;
	myCom.sin_port = htons(1200);
	myCom.sin_addr.S_un.S_addr = INADDR_ANY;
	
	rc = bind(s, (struct sockaddr*)&myCom, sizeof(myCom));
	if (rc<0) printf("error");
	listen(s, 5);

	//прин€тие соединени€, вызов сокета
	SOCKET s1;
	if ((s1 = accept(s, NULL, NULL)) == -1)printf("error");

	while (true)
	{
    f = fopen(filename, "ab");
		char buf[100];
		int r = recv(s1, buf, sizeof(buf), 0);//прием файла от клиента. ‘ункци€ возвращает число считанных байтов 
		if (r <= 0)//если нет данных
		{
			cout << "0 bytes" << endl;
			cout << "Error: " << WSAGetLastError() << endl; //вывод кода ошибки
			return false;//выход из цикла
		}
		fwrite(buf, 1, r, f);
		cout << "receive bytes: " << r << ", part: " << i << endl;
		printf("\n");
		send(s1, "ready", 6 * sizeof(char), 0);
		i++;
		fclose(f);
	}
	getch();
	//размыкание соединени€
	shutdown(s1, 2);
	WSACleanup();
	return 0;
}