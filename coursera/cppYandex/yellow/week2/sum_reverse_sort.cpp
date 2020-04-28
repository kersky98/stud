#include "sum_reverse_sort.h"
#include <algorithm>

int Sum(int x, int y){
  return x + y;
}

string Reverse(string s){
  string s1(s.size(), ' ');
  for(unsigned int i = 0; i < s.size(); i++){
    s1[s.size()-1-i] = s[i];
  }
  return s1;
}

void Sort(vector<int>& nums){
  sort(begin(nums), end(nums));
}
