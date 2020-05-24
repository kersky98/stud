#include "decorator.h"
#include <vector>
#include <memory>
#include <typeinfo>
#include <string>
using namespace std;

int main()
{
  cout << "Presentation of the DECORATOR pattern!" << std::endl;
  Beverage* beverage = new Espresso();
  cout << beverage->GetDescription() << " $" << beverage->cost() << endl;

  Mocha* beverage1 = new Mocha(beverage);
  Soy* beverage2 = new Soy(beverage1);
  cout << beverage2->GetDescription() << " $" << beverage2->cost() << endl;
  cout << "My description:" << beverage2->GetMyDescription() << endl;

  cout << "-----Signal-----:" << endl;
  IBaseSignal* base = new Signal();
  //cout << signal->GetDescription() << " data: " << signal->Calculate() << endl;
  base = new Fdn(base);
  base = new Sa(base);
  base = new Plo(base);
  base = new Tzk(base);
  cout << base->GetDescription() << ". data: " <<
      base->Calculate() << endl;
  return 0;
}
