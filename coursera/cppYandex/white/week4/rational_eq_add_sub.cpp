#include <iostream>
using namespace std;

class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
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

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
