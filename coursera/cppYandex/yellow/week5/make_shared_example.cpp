/*
 * make_shared_example.cpp
 *
 *  Created on: 21 мая 2020 г.
 *      Author: user
 */

#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Node{
public:
  Node(){
    a = 10;
    b = 20;
  }
  Node(int a, int b){
    this->a = a;
    this->b = b;
  }
  void Display(){
    cout << "a = " << a << ", b = " << b << endl;
  }
public:
  int a = 0;
  int b = 1;
};

int main1(){
  // создает указатель на уже готовый объект в куче
  Node *n = new Node;
  shared_ptr<Node> pNode = shared_ptr<Node>(n);

  // создает указатель на уже готовый объект в стеке, дает ошибку free(): invalid pointer
  //Node n1;
  //shared_ptr<Node> pNode1 = shared_ptr<Node>(&n1);

  // создает новый объект и указатель на него
  shared_ptr<Node> pNode2 = make_shared<Node>(23, 34/*пареметры конструктора*/);

  cout << n << endl;
  cout << pNode << endl;

  //cout << &n1 << endl;
  //cout << pNode1 << endl;

  cout << pNode2 << endl;

  n->a = 11;
  //n1.a = 12;
  n->Display();
  pNode->Display();  // pNode это указатель на объект n из heap
  //pNode1->Display(); // pNode1 это указатель на объект n1 из stack
  pNode2->Display(); // pNode2 это указатель на вновь созданный объект <Node>

  delete n;

  // работа со списком указателей
  cout << "List working:" << endl;
  const shared_ptr<Node> p1 = make_shared<Node>(1, 2);
  const shared_ptr<Node> p2 = make_shared<Node>(3, 4);
  const shared_ptr<Node> p3 = make_shared<Node>(5, 6);
  list<shared_ptr<Node>> v = {p1, p2, p3};
  /*list<shared_ptr<Node>> v;
  v.push_back(p1);
  v.push_back(p2);
  v.push_back(p3);*/

  cout << p1 << ", "<< p2 << ", " << p3 << endl;
  for(const auto& item: v){
    item->Display();
  }
  cout << "List erase:" << endl;
  v.erase(begin(v));
  cout << p1 << ", "<< p2 << ", " << p3 << endl;
  for(const auto& item: v){
    item->Display();
  }
  cout << "List push_back:" << endl;
  v.push_back(p1);
  for(const auto& item: v){
    item->Display();
  }

  cout << "Pointers:" << endl;
  cout << "Before use: "<< p1.use_count() << ", " << p2.use_count() << ", " << p3.use_count() << endl;
  shared_ptr<Node> p12 = p1;
  cout << "After use: "<< p1.use_count() << ", " << p2.use_count() << ", " << p3.use_count() << endl;
  auto it = find(begin(v), end(v), p1);
  v.erase(it);
  //cout << p1 << ", "<< p2 << ", " << p3 << endl;
  //cout << new int(2) << endl;
  cout << "After erase: "<< p1.use_count() << ", " << p2.use_count() << ", " << p3.use_count() << endl;
  p12.reset();
  cout << "After reset: "<< p1.use_count() << ", " << p2.use_count() << ", " << p3.use_count() << endl;
  cout << p12 << endl;
  for(const auto& item: v){
    item->Display();
  }
  return 0;
}

