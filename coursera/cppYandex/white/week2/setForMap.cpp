/*Напишите функцию BuildMapValuesSet, принимающую на вход словарь map<int, string>
 * и возвращающую множество значений этого словаря:
*/
#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m) {
  set<string> s;
  for(auto item : m)
    s.insert(item.second);
    //cout << item.first << " " << item.second << endl;

  return s;
}

int main1()
{
  set<string> values = BuildMapValuesSet({
      {1, "odd"},
      {2, "even"},
      {3, "odd"},
      {4, "even"},
      {5, "odd"}
  });

  for (const string& value : values) {
    cout << value << endl;
  }

  return 0;
}
