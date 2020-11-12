/*Дан набор строк. Необходимо разбить их на группы, в каждой из которых все строки
имеют одинаковый набор символов.

Например, если даны строки law, port, top, laptop, pot, paloalto, wall, awl,
нужно разбить их на 4 группы:

    строки, состоящие только из букв a, l и w: law, wall, awl;
    строки, состоящие только из букв o, p, r и t: port;
    строки, состоящие только из букв o, p и t: top, pot;
    строки, состоящие только из букв a, l, o, p, t: laptop, paloalto.

Разбиение на группы должно быть реализовано в виде функции

Здесь Group<String> — синоним для vector<String>:

Наличие такого синонима позволяет записать возвращаемый тип функции GroupHeavyString в
виде vector<Group<String>>, что читается понятнее, чем vector<vector<String>>.

Слова в каждой группе должны располагаться в том же порядке, что и в исходном наборе.
При этом порядок самих групп значения не имеет.

Строка типа String не обязана состоять из символов типа char. Тип символа можно
получить с помощью выражения typename String::value_type или Char<String>, если
определить соответствующий синоним:

Сам тип String может быть, например, обычной строкой (string) или вектором символов.

Про тип Char<String> известно следующее:

Объекты этого типа можно сравнивать с помощью операторов == и <.
«Тяжёлыми» могут быть не только сами строки, но и отдельные символы. Поэтому их можно
свободно перемещать, но скопировать каждый символ в функции можно не более одного
раза (без учёта копирования при передаче аргумента strings по значению).
В противном случае вы получите вердикт «неправильный ответ» с соответствующим комментарием.

Ограничения
За 1 секунду функция должна обработать максимум 100000 строк длины не более 100.
При оценке сложности можете считать, что копирование каждого символа стоит порядка
100 элементарных операций.
 * */
#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
  // Напишите реализацию функции,
  // использовав не более 1 копирования каждого символа
  map<set<typename String::value_type>, vector<size_t>> m;
  size_t index = 0;
  for(auto& item : strings){
    m[{begin(item), end(item)}].push_back(index++);
  }
  vector<Group<String>> vv;
  for(auto& item : m){
    vector<String> tmp;
    for(auto& item1 : item.second){
      tmp.push_back(move(strings[item1]));
    }
    vv.push_back(move(tmp));
    tmp.clear();
  }
  return vv;
}


void TestGroupingABC() {
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 2);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 4);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestGroupingABC);
  RUN_TEST(tr, TestGroupingReal);
  return 0;
}

/*int main1() {
  vector<string> v = {"12", "21", "123", "321"};
  vector<set<char>> vs;
  for(auto& item:v){
    vs.push_back({begin(item), end(item)});
  }
  for(auto& item:vs){
    cout << item << endl;
  }
  map<set<char>, vector<size_t>> m;
  size_t index = 0;
  for(auto& item : v){
    m[{begin(item), end(item)}].push_back(index++);
  }
  for(auto& item : m){
    cout << item << endl;
  }
  vector<vector<string>> vv;
  for(auto& item : m){
    vector<string> tmp;
    for(auto& item1 : item.second){
      tmp.push_back(move(v[item1]));
    }
    vv.push_back(move(tmp));
  }
  for(auto& item : vv){
    cout << item << endl;
  }
  for(auto& item : v){
    cout << item << endl;
  }
  return 0;
}*/
