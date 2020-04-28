#include <iostream>
using namespace std;

int main()
{
  string a, b, c;
  string smin;
  cin >> a >> b >> c;

  if (a < b)
  {
    smin = a;
  }else
  {
    smin = b;
  }

  if (smin > c)
    smin = c;

  cout << smin << endl;

  return 0;
}
