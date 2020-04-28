#include "phone_number.h"
#include "test_runner.h"
#include "tests.h"

int main(){
  TestRunner tr;
  tr.RunTest(TestPositive, "TestPositive");
  tr.RunTest(TestNegative, "TestNegative");

  return 0;
}
