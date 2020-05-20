/*Определите до конца тела классов, соблюдая следующие требования:
Класс Dog должен являться наследником класса Animal.
Конструктор класса Dog должен принимать параметр типа string и инициализировать
им поле Name в классе Animal.
 * */

#include <iostream>

using namespace std;

class Animal {
public:
    // ваш код
    Animal(const string& s): Name(s){

    }
    const string Name;
};


class Dog : public Animal{
public:
    // ваш код
    Dog(const string& s): Animal(s){

    }
    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};

int main(){
  Dog d("Dog");
  d.Bark();
  return 0;
}
