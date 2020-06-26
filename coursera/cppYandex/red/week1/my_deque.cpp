/*
Напишите шаблонный класс Deque, содержащий следующий набор методов:
конструктор по умолчанию;
константный метод Empty, возвращающий true, если дек не содержит ни одного элемента;
константный метод Size, возвращающий количество элементов в деке;
T& operator[](size_t index) и const T& operator[](size_t index) const;
константный и неконстантный метод At(size_t index), генерирующий стандартное исключение
out_of_range, если индекс больше или равен количеству элементов в деке;;
константные и неконстантные версии методов Front и Back, возвращающих ссылки на первый и
последний элемент дека соответственно;
методы PushFront и PushBack.

Неконстантные версии методов должны позволять изменять соответствующий элемент дека.

Для реализации заведите внутри класса Deque два вектора: в один осуществляйте вставку в
методе PushFront, а в другой — в методе PushBack.

Замечание
Заголовочный файл, который вы пришлёте на проверку, не должен подключать файлы
<list>, <deque>, <set>, <map>. Если у вас будет подключен один из этих файлов,
вы получите ошибку компиляции.
 */

#include <algorithm>
#include <utility>
#include <exception>
#include <stdexcept>
#include <vector>
#include <iostream>

using namespace std;

// Реализуйте здесь шаблонный класс Table
template <typename T>
class Deque{
public:
  bool Empty() const{
    return front.empty() && back.empty();
  }
  size_t Size() const{
    return front.size() + back.size();
  }
  void PushFront(const T& val){
    front.push_back(val);
  }
  void PushBack(const T& val){
    back.push_back(val);
  }
  const T& Front() const{
    if(!front.empty())
      return front.back();
    if(!back.empty())
      return back.front();
    else
      return NULL;
  }
  T& Front(){
    if(!front.empty())
      return front.back();
    if(!back.empty())
      return back.front();
    else
      return temp;
  }
  const T& Back() const{
    if(!back.empty())
      return back.back();
    if(!front.empty())
      return front.front();
    else
      return temp;
  }
  T& Back(){
    if(!back.empty())
      return back.back();
    if(!front.empty())
      return front.front();
    else
      return temp;
  }
  T& operator[](size_t index){
    index = min(index, front.size()+back.size() - 1);
    return (index < front.size()) ?
        front[front.size()-1-index] : back[index-front.size()];
  }
  const T& operator[](size_t index) const{
    index = min(index, front.size()+back.size() - 1);
    return (index < front.size()) ?
            front[front.size()-1-index] : back[index-front.size()];
  }
  T& At(size_t index){
    if(index >= front.size() + back.size()){
      throw std::out_of_range("Error index");
    }
    return (*this)[index];
  }
  const T& At(size_t index) const{
    if(index >= front.size() + back.size()){
      throw std::out_of_range("Error index");
    }
    return (*this)[index];
  }
  void Print(){
    cout << "{";
    for(auto it = rbegin(front); it != rend(front); it++){
      cout << *it << ",";
    }
    for(const auto& item: back){
      cout << item << ",";
    }
    cout << "}";
  }
private:
  T temp;
  vector<T> front;
  vector<T> back;
};
