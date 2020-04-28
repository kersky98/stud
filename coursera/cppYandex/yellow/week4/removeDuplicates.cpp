/*Напишите шаблонную функцию RemoveDuplicates, принимающую по ссылке вектор elements
 * объектов типа T и удаляющую из него все дубликаты элементов. Порядок оставшихся
 * элементов может быть любым.
Гарантируется, что объекты типа T можно сравнивать с помощью операторов ==, !=, < и >.
*/

#include <vector>
#include <iostream>
#include <string>
#include <set>

using namespace std;

template <typename T>
void RemoveDuplicates(vector<T>& elements){
  set<T> s(begin(elements), end(elements));
  elements.assign(begin(s), end(s));
}

template <typename DataType>
void RemoveDuplicates1(vector<DataType>& elements) {
  sort(begin(elements), end(elements));
  elements.erase(
      unique(begin(elements), end(elements)),
      elements.end());
}

int main() {
  vector<int> v1 = {6, 4, 7, 6, 4, 4, 0, 1};
  RemoveDuplicates(v1);
  for (int x : v1) {
    cout << x << " ";
  }
  cout << endl;

  vector<string> v2 = {"C", "C++", "C++", "C", "C++"};
  RemoveDuplicates(v2);
  for (const string& s : v2) {
    cout << s << " ";
  }
  cout << endl;
  return 0;
}
