#include "simple_vector.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <typename T>
void Print( const SimpleVector <T >& v) {
  for (const auto& x : v) {
    std::cout << x << ' ';
  }
}


void TestConstruction() {
  SimpleVector<int> empty;
  ASSERT_EQUAL(empty.Size(), 0u);
  ASSERT_EQUAL(empty.Capacity(), 0u);
  ASSERT(empty.begin() == empty.end());

  SimpleVector<string> five_strings(5);
  ASSERT_EQUAL(five_strings.Size(), 5u);
  ASSERT(five_strings.Size() <= five_strings.Capacity());
  for (auto& item : five_strings) {
    ASSERT(item.empty());
  }
  five_strings[2] = "Hello";
  ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack() {
  SimpleVector<int> v;
  for (int i = 10; i >= 1; --i) {
    v.PushBack(i);
    ASSERT(v.Size() <= v.Capacity());
  }
  //Print(v);
  //cout << endl;
  sort(begin(v), end(v));

  const vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQUAL(v.Size(), expected.size());
  //Print(v);
  //cout << endl;
  ASSERT(equal(begin(v), end(v), begin(expected)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConstruction);
  RUN_TEST(tr, TestPushBack);
  return 0;
}
