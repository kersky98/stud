/*Итак, теперь у нас с вами есть полноценный тип для представления обыкновенных
 * дробей: класс Rational интегрирован в язык с помощью перегрузки операторов и
 * не позволяет выполнять некорректные операции за счёт выбрасывания исключений.
 * Давайте на основе класса Rational создадим простой калькулятор для обыкновенных
 * дробей.
Вам надо написать программу, которая считывает из стандартного ввода одну строку
в формате ДРОБЬ_1 операция ДРОБЬ_2. ДРОБЬ_1 и ДРОБЬ_2 имеют формат X/Y,
где X — целое, а Y — целое неотрицательное число. операция — это один из символов
'+', '-', '*', '/'.
Если ДРОБЬ_1 или ДРОБЬ_2 является некорректной обыкновенной дробью, ваша программа
должна вывести в стандартный вывод сообщение "Invalid argument". Если считанная
операция — это деление на ноль, выведите в стандартный вывод сообщение
"Division by zero". В противном случае выведите результат операции.
*/

#include <iostream>
#include <exception>
using namespace std;

class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
      if(denominator == 0)
        throw invalid_argument("Invalid argument");
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
  if(denom == 0)
    throw domain_error("Division by zero");
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
  int p, q;
  if(stream && !stream.bad() && !stream.fail()){
    stream >> p;
    if(stream && !stream.bad() && !stream.fail()){
      char tmp;
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
    try {
      Rational r1, r2;
      char op;
      cin >> r1 >> op >> r2;
      if(op == '+')
        cout << r1 + r2;
      else if(op == '-')
        cout << r1 - r2;
      if(op == '*')
        cout << r1 * r2;
      if(op == '/')
        cout << r1 / r2;
    }
    catch (invalid_argument& arg) {
      cout << arg.what() << endl;
    }
    catch (domain_error& arg) {
      cout << arg.what() << endl;
    }


    return 0;
}
