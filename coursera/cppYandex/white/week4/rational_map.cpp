#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Rational {
public:
    Rational(int numerator = 0, int denominator = 1) {
      if(numerator != 0)
      {
        int a = max(abs(numerator), abs(denominator));
        int b = min(abs(numerator), abs(denominator));
        int nod;
        while(a % b != 0)
        {
          int tmp = b;
          b = a % b;
          a = tmp;
        }
        nod = b;
        //cout << nod << endl;
        p = numerator/nod;
        q = denominator/nod;
        if (q < 0){
          p = -p;
          q = -q;
        }
      }else
      {
        p = 0;
        q = 1;
      }
    }

    int Numerator() const {
        return p;
    }

    int Denominator() const {
        return q;
    }

    void SetNumerator(int numerator){
        p = numerator;
    }

    void SetDenominator(int denominator){
        q = denominator;
    }
private:
    int p, q;
};

// Реализуйте для класса Rational операторы ==, + и -
bool operator==(const Rational& lhs, const Rational& rhs)
{
  return lhs.Numerator() == rhs.Numerator() &&
      lhs.Denominator() == rhs.Denominator();
}

Rational operator+(const Rational& lhs, const Rational& rhs)
{
  int num = lhs.Numerator()*rhs.Denominator() +
      rhs.Numerator()*lhs.Denominator();
  int denom = lhs.Denominator()*rhs.Denominator();
  Rational result(num, denom);
  return result;
}

Rational operator-(const Rational& lhs, const Rational& rhs)
{
  int num = lhs.Numerator()*rhs.Denominator() -
        rhs.Numerator()*lhs.Denominator();
  int denom = lhs.Denominator()*rhs.Denominator();
  Rational result(num, denom);
  return result;
}

Rational operator*(const Rational& lhs, const Rational& rhs)
{
  int num = lhs.Numerator() * rhs.Numerator();
  int denom = lhs.Denominator()*rhs.Denominator();
  Rational result(num, denom);
  return result;
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
  int num = lhs.Numerator() * rhs.Denominator();
  int denom = lhs.Denominator() * rhs.Numerator();
  Rational result(num, denom);
  return result;
}

// Реализуйте для класса Rational операторы << и >>
ostream& operator<<(ostream& stream, const Rational& r)
{
  stream << r.Numerator() << "/" << r.Denominator();
  return stream;
}

istream& operator>>(istream& stream, Rational& r)
{
  int p = r.Numerator(), q = r.Denominator();
  if(!stream.eof()){
    stream >> p;
    if(!stream.eof())
      stream.ignore(1);
    if(!stream.eof()){
      stream >> q;
    }
    Rational tmp(p, q);
    r = tmp;
  }
  return stream;
}

// Реализуйте для класса Rational оператор(ы), необходимые для использования его
// в качестве ключа map'а и элемента set'а
bool operator<(const Rational& lhs, const Rational& rhs)
{
  bool result = lhs.Numerator() * rhs.Denominator() <
      lhs.Denominator() * rhs.Numerator();
  return result;
}


int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
