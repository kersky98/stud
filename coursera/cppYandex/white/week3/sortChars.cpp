/*Условие
В стандартном потоке дана одна строка, состоящая из числа N и следующих за ним N строк S.
Между собой число и строки разделены пробелом.
Отсортируйте строки S в лексикографическом порядке по возрастанию, игнорируя регистр букв,
и выведите их в стандартный поток вывода.
Ограничения
0 <= N <= 1000
1 <= |S| <= 15
Каждая строка S[i] может состоять из следующих символов: [0-9,a-z,A-Z]
*/
#include <iostream>
#include <ctype.h>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVector(const vector<string> &v)
{
  for(const string & i : v)
    cout << i << " ";
  cout << endl;
}

int main()
{
  int n;
  cin >> n;
  vector<string> numbers(n);
  for(auto& i : numbers)
    cin >> i;

  // PrintVector(numbers);
  // в примере использовалась ф-я lexicographical_compare
  sort(numbers.begin(), numbers.end(), [](string a, string b)
       {
        for(auto& i : a)
          i = tolower(i);
        for(auto& i : b)
          i = tolower(i);

        return a < b;
       });
  PrintVector(numbers);
  return 0;
}
