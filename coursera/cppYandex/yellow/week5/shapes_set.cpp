/*Вам дана функция main, которая считывает из стандартного ввода команды по работе с
 * набором геометрических фигур:
 *Как видно из кода, есть два вида команд:

ADD — добавить фигуру в набор;
PRINT — для каждой фигуры в наборе распечатать название, периметр и площадь.

Программа поддерживает три вида фигур: прямоугольник, треугольник и круг. Их добавление описывается так:

ADD RECT width height — добавить прямоугольник с размерами widthи height(например, ADD RECT 2 3).
ADD TRIANGLE a b c — добавить треугольник со сторонами a, b и c (например, ADD TRIANGLE 3 4 5).
ADD CIRCLE r — добавить круг радиуса r (например, ADD CIRCLE 5).

Не меняя функцию main, реализуйте недостающие функции и классы:

базовый класс Figure с чисто виртуальными методами Name, Perimeter и Area;
классы Triangle, Rect и Circle, которые являются наследниками класса Figure и переопределяют его виртуальные методы;
функцию CreateFigure, которая в зависимости от содержимого входного потока
создаёт shared_ptr<Rect>, shared_ptr<Triangle> или shared_ptr<Circle>.

Гарантируется, что все команды ADD корректны; размеры всех фигур — это натуральные числа не больше 1000.
В качестве значения π используйте 3,14.
 *   */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

class Figure{
public:
  virtual string Name() = 0;
  virtual double Perimeter() = 0;
  virtual double Area() = 0;
  virtual ~Figure(){};
};

class Triangle: public Figure{
public:
  Triangle(int a, int b, int c): a(a), b(b), c(c){

  }
  string Name()override{
    return name;
  }
  double Perimeter()override{
    return a + b + c;
  }
  double Area()override{
    //√ (p * (p - a)*(p - b)*(p - c)) ,где
    double p = Perimeter() / 2;
    return sqrt(p * (p - a)*(p - b)*(p - c));
  }
private:
  int a, b, c;
  const string name = "TRIANGLE";
};

class Rect: public Figure{
public:
  Rect(int a, int b): a(a), b(b){

  }
  string Name()override{
    return name;
  }
  double Perimeter()override{
    return 2*(a + b);
  }
  double Area()override{
    return a * b;
  }
private:
  int a, b;
  const string name = "RECT";
};

class Circle: public Figure{
public:
  Circle(int r): r(r){

  }
  string Name()override{
    return name;
  }
  double Perimeter()override{
    return 3.14 * 2 * r;
  }
  double Area()override{
    return 3.14 * r*r;
  }
private:
  int r;
  const string name = "CIRCLE";
};

shared_ptr<Figure> CreateFigure(istringstream& is){

  string figType;
  is >> figType;
  if(figType == "TRIANGLE"){
    int a, b, c;
    is >> a >> b >> c;
    return make_shared<Triangle>(a, b, c);
  }
  else if(figType == "RECT"){
    int a, b;
    is >> a >> b;
    return make_shared<Rect>(a, b);
  }
  else {
    int r;
    is >> r;
    return make_shared<Circle>(r);
  }
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
