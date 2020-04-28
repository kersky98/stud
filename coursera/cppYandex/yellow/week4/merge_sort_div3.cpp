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
  MergeSort(begin(elements), begin(elements)+d/3);
  MergeSort(begin(elements)+d/3, begin(elements)+2*d/3);
  MergeSort(begin(elements)+2*d/3, end(elements));

  vector<typename RandomIt::value_type> tmp;
  merge(begin(elements), begin(elements)+d/3, begin(elements)+d/3, begin(elements)+2*d/3, back_inserter(tmp));
  merge(begin(tmp), end(tmp), begin(elements)+2*d/3, end(elements), range_begin);
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
