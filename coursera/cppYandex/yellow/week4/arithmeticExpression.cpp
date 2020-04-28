/*Реализуйте построение арифметического выражения согласно следующей схеме:
изначально есть выражение, состоящее из некоторого целого числа x;
на каждом шаге к текущему выражению применяется некоторая операция: прибавление
числа, вычитание числа, умножение на число или деление на число; перед применением
операции выражение всегда должно быть заключено в скобки.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

int main() {
  int a, n;
  cin >> a >> n;
  string sres = to_string(a);
  for(int i=0; i<n; i++){
    char c;
    int value;
    cin >> c >> value;
    sres.insert(begin(sres), '(');
    sres.insert(end(sres), ')');
    sres.insert(end(sres), ' ');
    sres.insert(end(sres), c);
    sres.insert(end(sres), ' ');
    sres.append(to_string(value));
  }

  cout << sres << endl;
  return 0;
}
