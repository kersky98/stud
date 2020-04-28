#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
#include <string>
#include <algorithm>
using namespace std;

template <typename First, typename Second>
Second&
GetRefStrict(map<First, Second>& m, const First& f){
  if(m.count(f) == 0){
    throw runtime_error("Error");
  }
  return m.at(f);
}

int main() {
  map<int, string> m = {{0, "value"}};
  string& item = GetRefStrict(m, 0);
  item = "newvalue";
  cout << m[0] << endl; // выведет newvalue

  return 0;
}
