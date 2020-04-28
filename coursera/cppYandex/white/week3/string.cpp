/*Реализуйте класс ReversibleString, хранящий строку и поддерживающий методы Reverse
 * для переворота строки и ToString для получения строки.
*/
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class ReversibleString
{
public:
  ReversibleString()
  {
    str = "";
  }
  ReversibleString(const string& s)
    {
      str = s;
    }
  void Reverse()
  {
    reverse(str.begin(), str.end());
  }
  string ToString() const
  {
    return str;
  }
private:
string str;
};

int main() {
  ReversibleString s("live");
  s.Reverse();
  cout << s.ToString() << endl;

  s.Reverse();
  const ReversibleString& s_ref = s;
  string tmp = s_ref.ToString();
  cout << tmp << endl;

  ReversibleString empty;
  cout << '"' << empty.ToString() << '"' << endl;

  return 0;
}
