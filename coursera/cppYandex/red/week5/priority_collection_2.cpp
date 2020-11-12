/*Реализуйте шаблонный контейнер PriorityCollection, позволяющий хранить объекты
некопируемого типа, а также совершать с ними следующие операции:

добавить элемент с нулевым приоритетом;
добавить набор элементов с нулевыми приоритетами;
увеличить на 1 приоритет заданного элемента;
извлечь из контейнера элемент с максимальным приоритетом.

Поскольку добавление элемента заключается в его перемещении в контейнер, метод увеличения
приоритета не может принимать сам элемент. Поэтому метод, добавляющий элементы, для каждого
из них должен вернуть некий идентификатор, который затем можно использовать для вызова других методов.

Тип идентификатора — PriorityCollection::Id — вы должны выбрать самостоятельно.
Он должен быть легко копируемым: например, числом, указателем или итератором. Примеры определения
и использования типа Id вы можете найти в шаблоне решения.

Гарантии

Вы можете полагаться на то, что для элементов типа T определены перемещение и сравнение
на ==, != и <. Все операции над элементами имеют константную сложность.

Гарантируется, что все добавляемые элементы различны, однако добавленный и затем извлечённый
элемент может быть добавлен вновь.

Методы Get и Promote всегда вызываются от валидных с точки зрения метода IsValid идентификаторов.

Методы GetMax и PopMax вызываются только при наличии элементов в контейнере.

При наличии нескольких элементов с одинаковым максимальным приоритетом необходимо выбирать и
извлекать тот, который был добавлен позже остальных.

Контейнер должен обрабатывать 10^6 запросов не более чем за 1 секунду. Гарантируется, что
суммарная длина диапазонов, с которыми вызывается вторая версия метода Add, также не превосходит 10^6.
*/

#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <deque>
#include <map>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  /* тип, используемый для идентификаторов */
  using Id = typename deque<T>::iterator;

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object){
    d.push_back(move(object));
    Id it = prev(end(d));
    i2p[it] = 0;
    s.insert({0, it});
    return it;
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin){
  while(range_begin != range_end) {
    *ids_begin= Add(move(*range_begin));
    range_begin++;
    if (range_begin == range_end) return;
    ids_begin++;
    }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const{
    //if(i2p.find(id) != i2p(end))
    if(i2p.count(id) > 0)
      return true;
    else
      return false;
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const{
    return *id;
  }

  int GetPrior(Id id){
    if(IsValid(id)){
      return i2p[id];
    }
    return 0;
  }
  // Увеличить приоритет объекта на 1
  void Promote(Id id){
    if(IsValid(id)){
      int prev_p = i2p[id];
      i2p[id]++;
      typename set<pair<int, Id>>::iterator it_p = s.find({prev_p, id});
      pair<int, Id> tmp_p = *it_p;
      s.erase(it_p);
      tmp_p.first++;
      s.insert(tmp_p);
    }
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const{
    typename set<pair<int, Id>>::iterator it_max_elem = prev(end(s));
    pair<int, Id> pair_max_elem = *it_max_elem; //max element
    return {*(pair_max_elem.second), pair_max_elem.first};
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax(){
    typename set<pair<int, Id>>::iterator it_max_elem = prev(end(s));
    pair<int, Id> pair_max_elem = *it_max_elem; //max element
    s.erase(it_max_elem);
    i2p.erase(pair_max_elem.second);
    return {move(*pair_max_elem.second), pair_max_elem.first};
  }

  struct lex_compare{
    bool operator()(const pair<int, Id> &lhs, const pair<int, Id> &rhs) const
    {
      if(lhs.first == rhs.first){
        return lhs.second < rhs.second;
      }else
        return lhs.first < rhs.first;
    }
  };
  /*void PrintS(){
    for(const auto& item : s)
      cout << "s:(" << item.first << ", " << *item.second << ")";
    cout << endl;
  }*/
private:
  // Приватные поля и методы
  deque<T> d;
  set<pair<int, Id>, lex_compare> s;
  map<Id, int> i2p;
};


class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

void TestBySmirnov(){
  PriorityCollection<StringNonCopyable> s;
  const auto white_id = s.Add("white");
  const auto white_id1 = s.Add("white1");
  s.Promote(white_id);
  const auto yellow_id = s.Add("yellow");
  ASSERT_EQUAL(s.Get(yellow_id), "yellow");
  ASSERT_EQUAL(s.GetPrior(yellow_id), 0);
  ASSERT_EQUAL(s.Get(white_id), "white");
  ASSERT_EQUAL(s.GetPrior(white_id), 1);
  ASSERT_EQUAL(s.Get(white_id1), "white1");
  ASSERT_EQUAL(s.GetPrior(white_id1), 0);
}

void TestPopMax(){
  PriorityCollection<StringNonCopyable> s;
  const auto white_id = s.Add("white0");
  const auto white_id1 = s.Add("white3");
  //const auto white_id2 = s.Add("white2");
  //const auto white_id3 = s.Add("white1");
  s.Promote(white_id);
  s.Promote(white_id1);
  //s.PrintS();
  auto val = s.PopMax();
  //cout << val << endl;
  //s.PrintS();
  ASSERT_EQUAL(val.first, "white3");
  ASSERT_EQUAL(val.second, 1);

  const auto white_id2 = s.Add("white2");
  //const auto white_id3 = s.Add("white1");
  //s.PrintS();
  s.Promote(white_id2);
  //s.PrintS();
  val = s.PopMax();
  //s.PrintS();
  //cout << val << endl;
  ASSERT_EQUAL(val.first, "white2");
  ASSERT_EQUAL(val.second, 1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  RUN_TEST(tr, TestBySmirnov);
  RUN_TEST(tr, TestPopMax);
  return 0;
}
