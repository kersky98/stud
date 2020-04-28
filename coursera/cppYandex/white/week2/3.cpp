/*Напишите функцию, которая называется PalindromFilter возвращает vector<string>
 * принимает vector<string> words и int minLength и возвращает все строки из
 * вектора words, которые являются палиндромами и имеют длину не меньше minLength
Входной вектор содержит не более 100 строк, длина каждой строки не больше 100 символов.
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

vector<string> PalindromFilter(vector<string> words, int minLength)
{
	vector<string> out;
	for(auto i : words)
	{
		if(i.size() >= (unsigned int)minLength)
		{
			if(IsPalindrom(i))
			{
				out.push_back(i);
			}
		}
	}

	return out;
}

int main(){
	vector<string> s = {{"aa"},{"bbb"},{"cccc"}};
	//vector<string> s = {{"weew"},{"bro"},{"code"}};
	//vector<string> s = {{"w"}};
	vector<string> out;

	out = PalindromFilter(s, 1);
	for(auto i : out)
		cout << i << " ";

	return 0;
}
