/*
 * pointer_example.cpp
 *
 *  Created on: 23 мая 2020 г.
 *      Author: user
 */

#include <vector>
#include <list>
#include <queue>
#include <memory>
#include <iostream>

using namespace std;

struct Str{
  int a = 1;
  double b = 2.2;
};

int main(){
  Str s, s1;
  vector<Str> v = {s, s1};
  list<Str*> l = {&s, &s1};
  cout << &s << ", " << &s1 << endl;
  cout << &(v[0]) << ", " << &(v[1]) << endl;
  s = s1 = {0, .0};
  cout << "s:" << endl;
  cout << s.a << ", " << s.b << ", " << s1.a << ", " << s1.b << endl;
  cout << "vector:" << endl;
  cout << &v[0] << ", " << &v[1] << endl;
  cout << v[0].a << ", " << v[0].b << ", " << v[0].a << ", " << v[0].b << endl;
  cout << "list:" << endl;
  cout << *begin(l) << ", " << *(++begin(l)) << endl;
  cout << (*(begin(l)))->a << ", " << (*(begin(l)))->b << ", "
      << (++(*(begin(l))))->a << ", " << (++(*(begin(l))))->b << endl;

  return 0;
}
