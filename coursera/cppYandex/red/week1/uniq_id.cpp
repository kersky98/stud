#include <string>
#include <vector>
using namespace std;

// Реализуйте этот макрос так, чтобы функция main компилировалась
#define CONCAT(a, b) a ## b
#define CONCAT2(a, b) CONCAT(a, b)
#define UNIQ_ID CONCAT2(val, __LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}
