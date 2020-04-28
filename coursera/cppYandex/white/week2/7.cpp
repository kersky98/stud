/*Реализуйте функцию vector<int> Reversed(const vector<int>& v), возвращающую
 * копию вектора v, в которой числа переставлены в обратном порядке.
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

vector<int>
Reversed(const vector<int>& v)
{
	vector<int> v1 = v;
	Reverse(v1);
	return v1;
}

int main(){
	const vector<int> a = {1, 2, 3, 4};

	vector<int> b = Reversed(a);

	for(auto i : b)
		cout << i << " ";

	return 0;
}
