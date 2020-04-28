/*Дано два целых числа A и B (A <= B, A >= 1, B <= 30000).
 * Выведите через пробел все чётные числа от A до B (включительно).
*/
#include <iostream>
using namespace std;

int main(){
	int a, b;
    cin >> a >> b;
	//a = 1; b=10;
	//a=2; b=3;
	//a=9; b=11;
	//a=4; b=4;
	if(a == b)
	{
		if(a%2 == 0)
			cout << a << endl;
	}else
	{
		do
		{
			if(a%2 == 0)
				cout << a << " ";
			a++;
		}while(a <= b);
		cout << endl;
	}

	return 0;
}
