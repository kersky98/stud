/*Дан набор строк. Найдите количество уникальных строк в этом наборе.

Формат ввода
Сначала вводится количество строк N, затем — сами N строк, разделённые пробелом.
Все строки состоят лишь из латинских букв, цифр и символов подчёркивания.

Формат вывода
Выведите единственное целое число — количество уникальных строк в данном наборе.
*/
#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

int main()
{
  int n;
  string str;
  set<string> uniqueStrings;

  cin >> n;
  for(int i=0; i<n; i++)
  {
    cin >> str;
    uniqueStrings.insert(str);
  }
  cout << uniqueStrings.size() << endl;

  return 0;
}
