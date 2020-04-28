/*Определите тип Incognizable, для которого следующий код будет корректен:
 *int main() {
  Incognizable a;
  Incognizable b = {};
  Incognizable c = {0};
  Incognizable d = {0, 1};
  return 0;
}
*/
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

/* or
struct Incognizable {
  int x = 0;
  int y = 0;
};*/

class Incognizable
{
public:
  Incognizable(){};
  Incognizable(int a){};
  Incognizable(int a, int b){};
};

int main() {
  Incognizable a;
  Incognizable b = {};
  Incognizable c = {0};
  Incognizable d = {0, 1};
  return 0;
}
