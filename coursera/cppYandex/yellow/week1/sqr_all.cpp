#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
#include <string>
#include <algorithm>
using namespace std;

template <typename T>
vector<T>
operator*(const vector<T>& first, const vector<T>& second);

template <typename First, typename Second>
pair<First, Second>
operator*(const pair<First, Second>& p1, const pair<First, Second>& p2);

template <typename First, typename Second>
map<First, Second>
operator*(const map<First, Second>& m1, const map<First, Second>& m2);


template <typename T>
vector<T>
operator*(const vector<T>& first, const vector<T>& second){
  vector<T> temp;
  for(unsigned int i=0; i<first.size(); i++){
    temp.push_back(first[i] * second[i]);
  }
  return temp;
}

template <typename First, typename Second>
pair<First, Second>
operator*(const pair<First, Second>& p1, const pair<First, Second>& p2){
  First f = p1.first * p2.first;
  Second s = p1.second * p2.second;

  return make_pair(f, s);
}

template <typename First, typename Second>
map<First, Second>
operator*(const map<First, Second>& m1, const map<First, Second>& m2){
  map<First, Second> res;
  for(const auto& item : m1){
    res[item.first] = m1.at(item.first) * m2.at(item.first);
  }
  return res;
}

template <typename T> T Sqr(T x){
  return x * x;
}

int main() {
  vector<int> v = {1, 2, 3};
  cout << "vector:";
  for (int x : Sqr(v)) {
    cout << ' ' << x;
  }
  cout << endl;

  map<int, pair<int, int>> map_of_pairs = {
    {4, {2, 2}},
    {7, {4, 3}}
  };
  cout << "map of pairs:" << endl;
  for (const auto& x : Sqr(map_of_pairs)) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
  }

  return 0;
}
