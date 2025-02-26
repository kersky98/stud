/*Напишите функцию PrintVectorPart, принимающую вектор целых чисел numbers,
 * выполняющую поиск первого отрицательного числа в нём и выводящую в стандартный
 * вывод все числа, расположенные левее найденного, в обратном порядке. Если
 * вектор не содержит отрицательных чисел, выведите все числа в обратном порядке.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers){
  auto it = std::find_if(begin(numbers), end(numbers), [](int i){return i<0;});
  while(it != begin(numbers)){
    it--;
    cout << *it << " ";
  }
}

int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  cout << endl;
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  cout << endl;
  PrintVectorPart({6, 1, 8, 5, 4});
  cout << endl;
  return 0;
}
