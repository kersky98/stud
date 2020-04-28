/*
В стандартном потоке дана одна строка, состоящая из N + 1 целых чисел.
Первым числом идёт само число N. Далее следуют ещё N чисел, обозначим их за массив A.
Между собой числа разделены пробелом.

Отсортируйте массив А по модулю и выведите его в стандартный поток.
Ограничения
0 <= N <= 1000
-1000000 <= A[i] <= 1000000
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVector(const vector<int> &v)
{
  for(const int & i : v)
    cout << i << " ";
  cout << endl;
}

int main()
{
  int n, number;
  vector<int> numbers;
  cin >> n;
  for(int i=0; i<n; i++)
  {
    cin >> number;
    numbers.push_back(number);
  }
  //PrintVector(numbers);
  sort(numbers.begin(), numbers.end(), [](int x, int y)
       {
        return abs(x) < abs(y);
       });
  PrintVector(numbers);
  return 0;
}
