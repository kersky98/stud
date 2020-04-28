/*Имеется база регионов, представленная вектором структур Region:

Здесь Lang — идентификатор языка:

Напишите функцию FindMaxRepetitionCount, принимающую базу регионов и определяющую,
какое максимальное количество повторов(число вхождений одного и того же элемента) она
содержит. Две записи (объекты типа Region) считаются различными, если они отличаются
хотя бы одним полем.

Если все записи уникальны, считайте максимальное количество повторов равным 1.
Если записи отсутствуют, верните 0. Гарантируется, что типа int достаточно для хранения
ответа.
*/

#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <tuple>

using namespace std;

enum class Lang {
  DE, FR, IT
};

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};

bool operator==(const Region& lhs, const Region& rhs){
  tuple<const string&, const string&, const map<Lang, string>&, const int64_t&> lhs_key =
      tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population);
  tuple<const string&, const string&, const map<Lang, string>&, const int64_t&> rhs_key =
      tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
  return lhs_key == rhs_key;
}

bool operator<(const Region& lhs, const Region& rhs){
  return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
      tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions){
  int maxRepetitionCount=0;
  map<Region, int> m;
  for(const auto& item : regions){
    ++m[item];
    if(m[item] > maxRepetitionCount)
      maxRepetitionCount = m[item];
  }
  return maxRepetitionCount;
}

int FindMaxRepetitionCount1(const vector<Region>& regions) {
  int result = 0;
  map<Region, int> repetition_count;
  for (const Region& region : regions) {
    result = max(result, ++repetition_count[region]);
  }
  return result;
}

struct R {
  int a;
  string b;
};

int main1()
{
  R r1({1, "one"});
  R r2 = r1;
  cout << r1.a << " " << r1.b << endl;
  return 0;
}

int main() {
  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      },
  }) << endl;

  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Toulouse",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          31
      },
  }) << endl;

  return 0;
}
