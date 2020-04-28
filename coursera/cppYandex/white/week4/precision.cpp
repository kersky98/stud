/*В файле input.txt записаны вещественные числа, по одному на строчку. На стандартный
 * вывод напечатайте эти числа в том же порядке, по одному на строке, но сделайте так,
 * чтобы у каждого из них было ровно три знака после десятичной точки.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main()
{
  ifstream input("input.txt");
  double s;
  //cout << bool(input) << endl;
  //cout << input.is_open() << endl;
  cout << fixed;
  while(!input.eof())
  {
    input >> s;
    cout.precision(3);
    cout.width(3);
    cout << s << endl;
  }
  input.close();
  return 0;
}
