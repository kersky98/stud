#include "strategy.h"
#include <vector>
#include <memory>
#include <typeinfo>
#include <string>
using namespace std;

int main()
{
  cout << "Presentation of the STRATEGY pattern!" << std::endl;
  vector<Device*> devices;

  // инициализируем классы поведения для Write и Read по VME и Ethernet
  ExchVme exchVme;
  ExchEthernet exchEthernet;
  ExchImitator exchImitator;

  // ------------------------создаем объект Я400----------------------------
  Ya400 ya400; // по умолчанию exchVme
  ya400.Display();
  // определяем поведение Write и Read
  cout << "Ya400 set exchEthernet:" << endl;
  ya400.SetExchBehavior(&exchEthernet);
  // выводим в консоль результаты записи и чтения
  ya400.PerformWrite();
  ya400.PerformRead();
  //ya400.CommonFunction();

  // !!!---переопределяем---!!! поведение Write и Read для Я400
  cout << "Ya400 set exchVme:" << endl;
  ya400.SetExchBehavior(&exchVme);
  // выводим в консоль результаты записи и чтения
  ya400.PerformWrite();
  ya400.PerformRead();

  cout << "Ya400 set exchImitator:" << endl;
  ya400.SetExchBehavior(&exchImitator);
  // выводим в консоль результаты записи и чтения
  ya400.PerformWrite();
  ya400.PerformRead();

  devices.push_back(&ya400);

  // ------------------------создаем объект Б221----------------------------
  B221 b221; // по умолчанию exchEthernet
  b221.Display();
  // определяем поведение Write и Read для Б221
  b221.SetExchBehavior(&exchEthernet);
  b221.PerformWrite();
  b221.PerformRead();
  //b221.CommonFunction();

  devices.push_back(&b221);

  // ------------а теперь что-то в цикле делаем для всех устройств----------
  cout << endl << "Conveyor for all devices:" << endl;
  for(const auto& item : devices){
    cout << endl;
    cout << typeid(*item).name();
    item->Display();
    //item->PerformRead();
    //item->PerformWrite();
  }

  return 0;
}
