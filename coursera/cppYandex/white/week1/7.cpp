/*Дана строка. Найдите в этой строке второе вхождение буквы f и
 * выведите индекс этого вхождения. Если буква f в данной строке
 * встречается только один раз, выведите число -1, а если не встречается
 * ни разу, выведите число -2. Индексы нумеруются с нуля.
*/
#include <iostream>
#include <string>
using namespace std;

int main(){
	string s;
	unsigned int cnt = 0;
    unsigned int i;
	cin >> s;
	//s = "comfort";
	//s = "coffee";
    //s = "car";
    //s = "asfasasfddff";

	for (i=0; i<s.size(); i++)
	{
		if(s[i] == 'f')
			cnt++;
		if(cnt == 2)
			break;
	}

	if(cnt == 2)
		cout << i << endl;
	else if(cnt == 1)
		cout << -1 << endl;
	else if(cnt == 0)
		cout << -2 << endl;

	return 0;
}
