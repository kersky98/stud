/*В stdin даны два натуральных числа. Выведите в stdout их наибольший общий делитель.
*/
#include <iostream>
#include <string>
using namespace std;

int main(){
	unsigned int a, b, nod, ost;
	cin >> a >> b;
	//a = 25; b = 27;
	//a = 12; b = 16;
	//a = 13; b = 13;
	//a = 25; b = 5;

	if (a == b)
		nod = a;
	else if(a < b){
		unsigned int tmp = a;
		a = b;
		b = tmp;
	}

	do{
		ost = a%b;
		if(ost == 0)
			break;
		a = b;
		b = ost;
	}while(true);

	nod = b;
	cout << nod << endl;

	return 0;
}
