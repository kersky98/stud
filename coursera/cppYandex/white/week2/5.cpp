/*Напишите функцию MoveStrings, которая принимает два вектора строк,
 * source и destination, и дописывает все строки из первого вектора в
 * конец второго. После выполнения функции вектор source должен оказаться пустым.

Чтобы очистить содержимое вектора, надо вызвать у него метод clear:
*/
#include <iostream>
#include <vector>
using namespace std;

void MoveStrings(vector<string>& source, vector<string>& destination)
{
	for(auto i : source)
	{
		destination.push_back(i);
	}
	source.clear();
}

int main(){
	vector<string> a = {{"123"}, {"456"}};
	vector<string> b = {{"abc"}, {"def"}};
	MoveStrings(a, b);

	for(auto i : a)
		cout << i << " ";
	cout << endl;
	for(auto i : b)
		cout << i << " ";
	//cout << a.size() << endl;
	//cout << a[0] << " " << b[0] << endl;

	return 0;
}
