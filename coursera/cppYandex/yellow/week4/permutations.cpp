/*Дано целое положительное число N, не превышающее 9. Выведите все перестановки
 * чисел от 1 до N в обратном лексикографическом порядке (см. пример).*/

#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <numeric>

using namespace std;

template <typename T>
void PrintVector(const vector<T>& v){
  bool flag = false;
  for(const T& item: v){
    if(flag)
      cout << " ";
    cout << item;
    flag = true;
  }
}

int main() {
  int n=3;
  cin >> n;
  vector<int> v(n);
  iota(begin(v), end(v), 1);
  reverse(begin(v), end(v));

  PrintVector(v);
  cout << endl;
  while(prev_permutation(begin(v), end(v))){
    PrintVector(v);
    cout << endl;
  }

  return 0;
}
