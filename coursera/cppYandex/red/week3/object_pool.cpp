/*На практике часто возникают объекты, создание которых занимает значительное время, например,
 * потоки (threads), TCP-соединения или подключения к базе данных. Поэтому, когда такой объект
 * становится не нужен, его не разрушают, а откладывают в сторону, чтобы потом переиспользовать.
 * В этой задаче вам предстоит реализовать такую схему — вам надо написать шаблон класса ObjectPool:
 *
 * template <class T>
class ObjectPool {
public:
  T* Allocate();
  T* TryAllocate();

  void Deallocate(T* object);

  ~ObjectPool();

private:
  ...
};

Объект класса ObjectPool должен поддерживать два набора объектов: выделенные и освобождённые,
— изначально оба набора пусты.

Метод Allocate должен работать так:
если есть хотя бы один освобождённый объект, то его надо перенести в множество выделенных и
вернуть указатель на него в качестве результата функции
если же освобождённых объектов нет, то создаётся новый объект, помещается в множество выделенных,
и указатель на него возвращается в качестве результата функции

Метод TryAllocate работает аналогично, однако если освобождённых объектов нет, он должен
просто возвращать nullptr.
Метод Deallocate переносит объект из множества выделенных в множество освобождённых;
если переданный объект не содержится в множестве выделенных, метод Deallocate должен бросать
исключение invalid_argument.
Методы Allocate и TryAllocate должны возвращать объекты в порядке FIFO, т.е. множество освобождённых
объектов должно представлять собой очередь: методы [Try]Allocate должны извлекать объекты из её начала,
а метод Deallocate должен помещать освобождаемый объект в её конец.
Деструктор объекта ObjectPool должен уничтожать все объекты пула, как выделенные, так и освобождённые.
*/


#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate(){
    T* tmp = nullptr;
    if(deallocate_obj.empty()){
      tmp = new T;
      allocate_obj.insert(tmp);
      return tmp;
    }
    else{
      tmp = deallocate_obj.front();
      allocate_obj.insert(tmp);
      deallocate_obj.pop_front();
    }
    return tmp;
  }

  T* TryAllocate(){
    if(deallocate_obj.empty()){
      return nullptr;
    }
    else{
      T* tmp = deallocate_obj.front();
      allocate_obj.insert(tmp);
      deallocate_obj.pop_front();
      return tmp;
    }
  }

  void Deallocate(T* object){
    if(allocate_obj.count(object) == 0){
      throw invalid_argument("err");
    }
    else{
      deallocate_obj.push_back(object);
      allocate_obj.erase(object);
    }
  }

  ~ObjectPool(){
    for(auto item: allocate_obj){
      delete item;
    }
    for(auto item: deallocate_obj){
      delete item;
    }
  }

private:
  // Добавьте сюда поля
  set<T*> allocate_obj;
  deque<T*> deallocate_obj;;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
