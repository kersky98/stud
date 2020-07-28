/*Односвязный список — классический пример структуры данных, для реализации
которой нужно пользоваться памятью в куче. В этой задаче вам нужно реализовать
шаблон класса LinkedList, который представляет собой односвязный список и обладает
следующим интерфейсом:

Метод GetHead возвращает указатель на голову списка, он используется для перебора
элементов списка (см. шаблон ToVector в заготовке решения)

Метод PushFront добавляет новый элемент в голову списка.

Метод InsertAfter вставляет новый элемент в список так, чтобы он шёл после узла node.
Если node == nullptr, метод эквивалентен PushFront

Метод PopFront удаляет элемент из головы списка и освобождает выделенную под него память.
Если список пуст, метод завершается корректно. Если после выполнения метода список стал пустым,
метод GetHead должен возвращать nullptr

Метод RemoveAfter должен удалять из списка элемент, который следует за узлом node,
и освобождать выделенную под него память. Если node == nullptr, метод эквивалентен PopFront.
Если node->next == nullptr, то метод должен корректно завершаться.

Все методы, перечисленные выше, должны работать за O(1)

Деструктор класса LinkedList освобождает всю память, выделенную для хранения элементов списка.
 * */

#include "test_runner.h"

#include <vector>
using namespace std;

template <typename T>
class LinkedList {
public:
  struct Node {
    T value;
    Node* next = nullptr;
  };

  ~LinkedList(){
    Node* node = head;
    while(head){
      node = head;
      head = head->next;
      delete node;
    }
  }

  void Print(){
    for(Node* node = head; node; node = node->next){
      cerr << node->value << ", " << node->next << "; ";
    }
  }
  void PushFront(const T& value){
    if(head != nullptr){
      Node* tmp = new Node;
      tmp->value = value;
      tmp->next = head;
      head = tmp;
    }else{
      head = new Node;
      head->value = value;
      head->next = nullptr;
    }
  }
  void InsertAfter(Node* node, const T& value){
    if(node == nullptr){
      PushFront(value);
    }else{
      Node* tmp = new Node;
      tmp->value = value;
      tmp->next = node->next;
      node->next = tmp;
    }
  }
  void RemoveAfter(Node* node){
    if(node == nullptr){
      PopFront();
    }else{
      if(node->next != nullptr){
        Node* tmp = node->next;
        node->next = node->next->next;
        delete tmp;
      }
    }
  }
  void PopFront(){
    if(head != nullptr){
      Node* tmp = head->next;
      delete head;
      head = tmp;
    }
  }

  Node* GetHead() { return head; }
  const Node* GetHead() const { return head; }

private:
  Node* head = nullptr;
};

template <typename T>
vector<T> ToVector(const LinkedList<T>& list) {
  vector<T> result;
  for (auto node = list.GetHead(); node; node = node->next) {
    result.push_back(node->value);
  }
  return result;
}

void TestPushFront() {
  LinkedList<int> list;

  list.PushFront(1);
  ASSERT_EQUAL(list.GetHead()->value, 1);
  list.PushFront(2);
  ASSERT_EQUAL(list.GetHead()->value, 2);
  list.PushFront(3);
  ASSERT_EQUAL(list.GetHead()->value, 3);

  //list.Print();

  const vector<int> expected = {3, 2, 1};
  ASSERT_EQUAL(ToVector(list), expected);
}

void TestInsertAfter() {
  LinkedList<string> list;

  list.PushFront("a");
  auto head = list.GetHead();
  ASSERT(head);
  ASSERT_EQUAL(head->value, "a");

  list.InsertAfter(head, "b");
  const vector<string> expected1 = {"a", "b"};
  ASSERT_EQUAL(ToVector(list), expected1);

  list.InsertAfter(head, "c");
  const vector<string> expected2 = {"a", "c", "b"};
  ASSERT_EQUAL(ToVector(list), expected2);
}

void TestRemoveAfter() {
  LinkedList<int> list;
  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }

  const vector<int> expected = {5, 4, 3, 2, 1};
  ASSERT_EQUAL(ToVector(list), expected);

  auto next_to_head = list.GetHead()->next;
  list.RemoveAfter(next_to_head); // удаляем 3
  list.RemoveAfter(next_to_head); // удаляем 2

  const vector<int> expected1 = {5, 4, 1};
  ASSERT_EQUAL(ToVector(list), expected1);

  while (list.GetHead()->next) {
    list.RemoveAfter(list.GetHead());
  }
  ASSERT_EQUAL(list.GetHead()->value, 5);

  LinkedList<int> list1;
  list1.PushFront(1);
  LinkedList<int>::Node* node_to_remove = nullptr;
  list1.RemoveAfter(node_to_remove);
  ASSERT(list1.GetHead()==nullptr);
}

void TestPopFront() {
  LinkedList<int> list;

  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }
  for (int i = 1; i <= 5; ++i) {
    list.PopFront();
  }
  ASSERT(list.GetHead() == nullptr);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestPushFront);
  RUN_TEST(tr, TestInsertAfter);
  RUN_TEST(tr, TestRemoveAfter);
  RUN_TEST(tr, TestPopFront);
  return 0;
}
