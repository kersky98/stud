/*Напишите функцию, которая называется IsPalindrom возвращает bool
принимает параметр типа string и возвращает, является ли переданная
строка палиндромом
Палиндром - это слово или фраза, которые одинаково читаются слева направо
и справа налево. Пустая строка является палиндромом.
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool IsPalindrom(string s)
{
	string s1;
	for(int i=s.size()-1; i >= 0; i--)
		s1.push_back(s[i]);
	if (s == s1)
		return true;
	else
		return false;
}

int main(){
	string s;
	cin >> s;
	//s = "madam";
	//s = "gentleman";
	//s = "  ";

	bool isPalindrom = IsPalindrom(s);
	if(isPalindrom)
		cout << "true";
	else
		cout << "false";

	return 0;
}
