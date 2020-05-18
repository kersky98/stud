#include "strategy.h"
#include <vector>
#include <memory>
#include <typeinfo>
#include <string>
using namespace std;

int main()
{
  cout << "Presentation of the STRATEGY pattern!" << std::endl;
  vector<shared_ptr<Device>> devices;

  // инициализируем классы поведения для Write и Read по VME и Ethernet
  ExchVme exchVme;
  ExchEthernet exchEthernet;
  ExchImitator exchImitator;

  // ------------------------создаем объект Я400----------------------------
  Ya400 ya400; // по умолчанию exchVme
  // определяем поведение Write и Read
  ya400.SetExchBehavior(&exchEthernet);
  // выводим в консоль результаты записи и чтения
  //ya400.Display();
  //ya400.PerformWrite();
  //ya400.PerformRead();
  //ya400.CommonFunction();

  // !!!---переопределяем---!!! поведение Write и Read для Я400
  ya400.SetExchBehavior(&exchVme);
  ya400.SetExchBehavior(&exchImitator);
  // выводим в консоль результаты записи и чтения
  //ya400.Display();
  //ya400.PerformWrite();
  //ya400.PerformRead();
  //ya400.CommonFunction();
  devices.push_back(make_shared<Ya400>(ya400));

  // ------------------------создаем объект Б221----------------------------
  B221 b221; // по умолчанию exchEthernet
  //b221.Display();
  // определяем поведение Write и Read для Б221
  b221.SetExchBehavior(&exchEthernet);
  //b221.PerformWrite();
  //b221.PerformRead();
  //b221.CommonFunction();
  devices.push_back(make_shared<B221>(b221));

  // ------------а теперь что-то в цикле делаем для всех устройств----------
  for(const auto& item : devices){
    cout << endl;
    cout << typeid(*item).name();
    item->Display();
    item->PerformRead();
    item->PerformWrite();
  }

  return 0;
}
