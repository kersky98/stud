/*
 * FindNearestElement.cpp
 *
 *  Created on: 26 апр. 2020 г.
 *      Author: user
 *
 *TODO: Напишите функцию FindNearestElement, для множества целых чисел numbers и данного
 *числа border возвращающую итератор на элемент множества, ближайший к border.
 *Если ближайших элементов несколько, верните итератор на наименьший из них.
 */

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <set>

using namespace std;
// set<int>::const_iterator —
// тип итераторов для константного множества целых чисел
set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border){
  const set<int>::const_iterator it = numbers.lower_bound(border);
  if(it == begin(numbers)){
    return it;
  }
  if(it == end(numbers)){
    return prev(it);
  }

  /*if(*it-border == border-*prev(it)){
    return prev(it);
  }
  return it;*/
  const bool is_left = (border - *prev(it) <= *it - border);
  return is_left ? prev(it) : it;
}
//1 4 4 6 6
//1
int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << endl;

  set<int> empty_set;

  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;

  numbers = {2, 3, 5};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 4) << " " <<
      //*FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << endl;

  return 0;
}
