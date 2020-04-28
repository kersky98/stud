/*Реализуйте функцию void Reverse(vector<int>& v), которая переставляет элементы
 * вектора в обратном порядке.
*/
#include <iostream>
#include <vector>
using namespace std;

void Reverse(vector<int>& v)
{
	int tmp;
	for(unsigned int i = 0; i < v.size()/2; i++)
	{
		tmp = v[i];
		v[i] = v[v.size() - 1 - i];
		v[v.size() - 1 - i] = tmp;
	}
}

int main(){
	vector<int> a = {1, 2, 3, 4};

	Reverse(a);

	for(auto i : a)
		cout << i << " ";

	return 0;
}
