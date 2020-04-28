/*Напишите функцию, которая называется Factorial возвращает int
принимает int и возвращает факториал своего аргумента. Гарантируется,
что аргумент функции по модулю не превышает 10. Для отрицательных аргументов
функция должна возвращать 1.
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int Factorial(int n)
{
	int f = n;
	if(n <= 0){
		return 1;
	}
	while(n > 1)
	{
		f *= --n;
	}
	return f;
}

int main(){
	int n;
	cin >> n;
	//n = 0;

	cout << Factorial(n);
	return 0;
}
