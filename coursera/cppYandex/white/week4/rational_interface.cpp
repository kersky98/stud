/*Часть 1
В первой части Вам надо реализовать класс Rational, который представляет собой
рациональное число вида p/q, где p — целое, а q — натуральное и диапазоны
возможных значений p, q таковы, что могут быть представлены типом int. При
этом, класс Rational должен иметь следующий интерфейс:
Класс Rational должен гарантировать, что p/q — это несократимая дробь. Например, код
должен выводить «2/3» — именно поэтому мы делаем Rational классом, а не структурой.
Структура позволила бы нарушить этот инвариант:
Список требований, предъявляемых к реализации интерфейса класса Rational:
Конструктор по умолчанию должен создавать дробь с числителем 0 и знаменателем 1.
При конструировании объека класса Rational с параметрами p и q должно выполняться
сокращение дроби p/q (здесь вам может пригодиться решение задачи «Наибольший общий делитель»).
Если дробь p/q отрицательная, то объект Rational(p, q) должен иметь отрицательный
числитель и положительный знаменатель.
Если дробь p/q положительная, то объект Rational(p, q) должен иметь положительные числитель
и знаменатель (обратите внимание на случай Rational(-2, -3)).
Если числитель дроби равен нулю, то знаменатель должен быть равен 1.
 *
 */
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

int main1()
{
  Rational r;
  cout << r.Numerator() << " " << r.Denominator() << endl;
  Rational r1(0, -6);
  cout << r1.Numerator() << " " << r1.Denominator() << endl;

  return 0;
}

int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}
