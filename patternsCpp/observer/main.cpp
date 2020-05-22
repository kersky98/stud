#include "observer.h"
#include <vector>
#include <memory>
#include <typeinfo>
#include <string>
using namespace std;

int main()
{
  cout << "Presentation of the OBSERVER pattern!" << endl;

  //! создание субъекта, об изменении его стояния будут оповещаться зарегистрированные наблюдатели
  Sau sau;

  /**создание устройств-наблюдателей Device7EM, Device7EP. Подписка на оповещения
  от субъекта по умолчанию в конструкторе*/
  shared_ptr<Device7EM> device7em = make_shared<Device7EM>(sau);
  shared_ptr<Device7EP> device7ep = make_shared<Device7EP>(sau);

/*  cout << "Observers count = " << sau.observers.size() << endl;
  for(auto item : sau.observers){
    cout << "Observer name = " << item->name << endl;
  }*/

  /** САУ оповещает устройства-наблюдатели о том, что пришли новые данные*/
  cout << "SAU SetCtrl:" << endl;
  sau.SetCtrl({100., .001, .001});
  //sau.SetCtrl({200., .002, .002});

  /** Удаление устройства-наблюдателя из списка оповещения САУ*/
  sau.RemoveObserver(device7ep);
  sau.RemoveObserver(device7em);

  cout << "After remove:" << endl;
  sau.SetCtrl({300., .003, .003});

  sau.RegisterObserver(device7em);
  sau.RegisterObserver(device7ep);
  cout << "After register:" << endl;
  sau.SetCtrl({300., .003, .003});

  cout << endl << "!!!---------Destroy truble(((----------!!!" << endl;
  cout << "use_count: " << device7em.use_count() << ", " << device7ep.use_count() << endl;
  //cout << "use_count: " << device7em.use_count() << ", " << device7ep.use_count() << endl;

  return 0;
}
