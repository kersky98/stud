
#include <iostream>
#include <sstream>
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

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

istream& operator>>(istream& stream, Rational& r)
{
  int p, q;
  if(stream && !stream.bad() && !stream.fail()){
    stream >> p;
    if(stream && !stream.bad() && !stream.fail()){
      char tmp;
      //getline(stream, tmp, '/');
      //stream.ignore(' ');
      stream >> tmp;
      if(tmp == '/' && stream && !stream.bad() && !stream.fail()){
        stream >> q;
        if(!stream.bad() && !stream.fail()){
          Rational tmp(p, q);
          r = tmp;
        }
      }
    }
  }
  return stream;
}

int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5__OMG!___/4");
        //istringstream input("-5 / -7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    cout << "OK" << endl;
    return 0;
}

