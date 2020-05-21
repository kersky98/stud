/*
 * make_shared_example.cpp
 *
 *  Created on: 21 мая 2020 г.
 *      Author: user
 */

#include <iostream>
#include <memory>
#include <vector>

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

int main(){
  // создает указатель на уже готовый объект в куче
  Node *n = new Node;
  shared_ptr<Node> pNode = shared_ptr<Node>(n);

  // создает указатель на уже готовый объект в стеке, дает ошибку free(): invalid pointer
  Node n1;
  shared_ptr<Node> pNode1 = shared_ptr<Node>(&n1);

  // создает новый объект и указатель на него
  shared_ptr<Node> pNode2 = make_shared<Node>(23, 34/*пареметры конструктора*/);

  cout << n << endl;
  cout << pNode << endl;

  cout << &n1 << endl;
  cout << pNode1 << endl;

  cout << pNode2 << endl;

  n->a = 11;
  n1.a = 12;
  n->Display();
  pNode->Display();  // pNode это указатель на объект n из heap
  pNode1->Display(); // pNode1 это указатель на объект n1 из stack
  pNode2->Display(); // pNode2 это указатель на вновь созданный объект <Node>

  delete n;
  return 0;
}

