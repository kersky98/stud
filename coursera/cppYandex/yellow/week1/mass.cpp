/*Вычислите суммарную массу имеющих форму прямоугольного параллелепипеда блоков
 * одинаковой плотности, но разного размера.

Указание
Считайте, что размеры блоков измеряются в сантиметрах, плотность — в граммах на
кубический сантиметр, а итоговая масса — в граммах. Таким образом, массу блока
можно вычислять как простое произведение плотности на объём.

Формат ввода
В первой строке вводятся два целых положительных числа: количество блоков N и
плотность каждого блока R. Каждая из следующих N строк содержит три целых положительных
числа W, H, D — размеры очередного блока.

Гарантируется, что:
количество блоков N не превосходит 10^5;
плотность блоков R не превосходит 100;
размеры блоков W, H, D не превосходят 10^4.
*/

#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
//  std::cout << std::numeric_limits<int64_t>::max() << '\n'
// << std::numeric_limits<uint64_t>::max() << '\n';

int main() {
  long long unsigned int v=0;
  unsigned int n, p;
  cin >> n >> p;
  for(unsigned int i=0; i < n; i++)
  {
    long long unsigned int w, h, d;
    cin >> w >> h >> d;
    //cout << sizeof(w*h*d) << endl;
    v += w*h*d;
  }
  cout << v*p << endl;
  return 0;
}
