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
#include <string>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  /* тип, используемый для идентификаторов */
  using Id = typename std::deque<T>::iterator;

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object){
    objects.push_back(std::move(object));
    Id id = std::prev(objects.end());
    id2pr[id] = 0;
    s.insert(std::make_pair(0, id));
    return id;
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin){
    while(range_begin != range_end){
      *ids_begin++ = Add(std::move(*range_begin++));
    }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const{
    if(id2pr.count(id) > 0){
      return true;
    }else{
      return false;
    }
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const{
    return *id;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id){
    int oldpr = id2pr[id]++;
    auto it = s.find(std::make_pair(oldpr, id));
    if(it != s.end()){
      s.erase(it);
      s.insert(std::make_pair(id2pr[id], id));
    }
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const{
    // typename std::set<std::pair<int, Id>>::iterator
    auto it = std::prev(s.end());
    pair<const T&, int> res = {*(it->second), it->first};
    return res;
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax(){
    auto it = std::prev(s.end());
    pair<T, int> res = { std::move(*(it->second)), it->first };
    id2pr.erase(it->second);
    s.erase(it);
    return res;
  }

private:
  // Приватные поля и методы
  std::deque<T> objects;
  std::map<Id, int> id2pr;
  std::set<std::pair<int, Id>> s;
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

int main1() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}

int main(){
  std::deque<std::string> v = {"qwe", "asd", "zxc"};
  for(const string& item : v){
    std::cout << item << "\t";
  }
  std::cout << "size = " << v.size() << std::endl;

  std::string s(std::move(v[1]));
  std::cout << s << std::endl;

  for(const string& item : v){
    std::cout << item << "\t";
  }
    std::cout << "size = " << v.size() << std::endl;

  return 0;
}
