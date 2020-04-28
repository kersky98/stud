/*Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней.
 * Найдите номера дней (в нумерации с нуля) со значением температуры выше
 * среднего арифметического за все N дней.
Гарантируется, что среднее арифметическое значений температуры является целым числом.

Формат ввода
Вводится число N, затем N неотрицательных целых чисел — значения температуры
в 0-й, 1-й, ... (N−1)-й день.

Формат вывода
Первое число K — количество дней, значение температуры в которых выше среднего
арифметического. Затем K целых чисел — номера этих дней.
*/
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int nCommand = 0, nPeople = 0;
  vector<int> v;
  vector<int> worry;
  string command;

  cin >> nCommand;
  for(int i = 0; i < nCommand; i++)
  {
    cin >> command;
    if (command != "WORRY_COUNT")
      cin >> nPeople;
    if(command == "COME")
    {
      v.resize(v.size() + nPeople, 0);
    }
    else if(command == "WORRY")
    {
      v[nPeople] = 1;
    }
    else if(command == "QUIET")
    {
      v[nPeople] = 0;
    }
    else if(command == "WORRY_COUNT")
    {
      int nWorry = 0;
      for(auto iv : v)
	{
	if(iv > 0)
	  nWorry++;
	}
      worry.push_back(nWorry);
    }
  }

  for(auto i : worry)
    cout << i << endl;

  return 0;
}
