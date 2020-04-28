/*
 * merge_sort_div2.cpp
 *
 *  Created on: 26 апр. 2020 г.
 *      Author: user
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
  auto d = distance(range_begin, range_end);
  if(d < 2){
    return;
  }
  vector<typename RandomIt::value_type> elements(range_begin, range_end);
  MergeSort(begin(elements), begin(elements)+d/2);
  MergeSort(begin(elements)+d/2, end(elements));
  //inplace_merge(begin(elements), begin(elements)+d/2, end(elements));
  //copy(begin(elements), end(elements), range_begin);
  merge(begin(elements), begin(elements)+d/2, begin(elements)+d/2, end(elements), range_begin);
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  //vector<int> v = {6};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
