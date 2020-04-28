/*Часть 2. Без лишних скобок
Модифицируйте решение предыдущей части так, чтобы предыдущее выражение обрамлялось
скобками лишь при необходимости, то есть только в том случае, когда очередная операция
имеет бо́льший приоритет, чем предыдущая.
*/
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

enum class priority{
  PLUS_MINUS,
  MUL_DIV
};

int main() {
  int a, n;
  cin >> a >> n;
  string sa = to_string(a);
  deque<char> d;
  copy(begin(sa), end(sa), back_inserter(d));
  priority pr_prev = priority::MUL_DIV;
  string tmp;
  for(int i=0; i<n; i++){
    char c;
    int value;
    cin >> c >> value;
    priority pr_curr;
    if(c == '+' || c == '-'){
      pr_curr = priority::PLUS_MINUS;
    }else if(c == '*' || c == '/'){
      pr_curr = priority::MUL_DIV;
    }
    if(pr_prev < pr_curr){
      d.push_front('(');
      d.push_back(')');
    }
    pr_prev = pr_curr;

    d.push_back(' ');
    d.push_back(c);
    d.push_back(' ');
    tmp = to_string(value);
    copy(begin(tmp), end(tmp), back_inserter(d));

  }

  for(const auto& item : d)
    cout << item;
  return 0;
}
