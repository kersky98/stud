/*На вход дано целое положительное число N.
 * Выведите его в двоичной системе счисления без ведущих нулей.
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
	unsigned int n, ost;
	vector<int> bin;
	cin >> n;
	//n = 1;

	do{
		ost = n % 2;
		n = n / 2;
		bin.push_back(ost);
	}while(n != 0);

	//cout << bin.size() << endl;
	for(int i = bin.size()-1; i >= 0; i--)
		cout << bin[i];
	cout << endl;

	return 0;
}
