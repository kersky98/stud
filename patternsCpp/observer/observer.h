#ifndef OBSERVER_H
#define OBSERVER_H
/**
  @note: паттерн Наблюдатель определяет отношение "один-ко-многим".
*/

#include <iostream>
#include <memory>
#include <list>
#include <algorithm>
#include <iomanip>

/**
  @strust TNC_TABLE
  @brief структура управления
*/
struct TNC_TABLE{
  double time = 0.0; //!< абсолютное время применения команды
  double ti = 0.0;   //!< абсолютное время длительности интервала излучения
  double tp = 0.0;   //!< абсолютное время длительности интревала приема
};

/**
  @strust CTRL_7EP
  @brief структура управления 7EP
*/
struct CTRL_7EP{
  /**абсолютное время применения команды, выраженное в количестве тактов
  внутреннего генератора ПЛИС*/
  long long unsigned int time = 0;
  /**абсолютное время время длительности интревала приема, выраженное в
  количестве тактов внутреннего генератора ПЛИС*/
  long long unsigned int tp = 0;
};

/**
  @strust CTRL_7EM
  @brief структура управления 7EM
*/
struct CTRL_7EM{
  /**абсолютное время применения команды, выраженное в количестве тактов
  внутреннего генератора ПЛИС*/
  long long unsigned int time = 0;
  /**абсолютное время время длительности интревала приема, выраженное в
  количестве тактов внутреннего генератора ПЛИС*/
  long long unsigned int ti = 0;
};

/**
  @class IObserver
  @brief интерфейс наблюдателя
*/
class IObserver{
public:
  /**
    @fn Update
    @brief виртуальный метод обновления состояния
    @param[in] TNC_TABLE - температура окружающей среды
    @return none
  */
  virtual void Update(const TNC_TABLE& tnc){
    std::cout << "Virtual Update " << name << std::endl;
  };
  //!< виртуальный деструктор класса
  virtual ~IObserver(){
    std::cout << "IObserver destructor. ";
    std::cout << p->name << ", "  << p.get() << ", " << p.use_count() << std::endl;
    //p.reset();
  };
  //! имя объекта наблюдателя
  std::string name;
  std::shared_ptr<IObserver> p;
};

/**
  @class ISubject
  @brief интерфейс субъекта
*/
class ISubject{
public:
  /**
    @fn RegisterObserver
    @brief виртуальный метод регистрации нового наблюдателя
    @param[in] o - указатель на наблюдателя, которого требуется зарегистрировать
    @return none
  */
  virtual void RegisterObserver(const std::shared_ptr<IObserver> o){
  //virtual void RegisterObserver(IObserver& o){
    std::cout << "Virtual RegisterObserver" << std::endl;
  };
  /**
    @fn RemoveObserver
    @brief виртуальный метод удаления наблюдателя
    @param[in] o - указатель на наблюдателя, которого требуется удалить из списка наблюдателей
    @return none
  */
  virtual void RemoveObserver(const std::shared_ptr<IObserver> o){};
  //! виртуальный метод уведомления наблюдателя о событии
  virtual void NotifyObserver(){
    std::cout << "Virtual NotifyObserver" << std::endl;
  };
  //! виртуальный деструктор класса
  virtual ~ISubject(){
    std::cout << "ISubject destructor. " << std::endl;
  };
};

/**
  @class IDisplay
  @brief интерфейс(абстрактный класс) наблюдателя отображения визуального элемента
*/
class IDisplay{
public:
  virtual void Display() = 0;  //!< виртуальный метод отображения визуального элемента
  virtual ~IDisplay(){};       //!< виртуальный деструктор класса
};

/**
  @class Sau
  @brief класс субъекта ("один")
*/
class Sau: public ISubject{
public:
  void RegisterObserver(const std::shared_ptr<IObserver> o){
    observers.push_back(o);
    std::cout << o->name << " is registered" << std::endl;
  }

  void RemoveObserver(const std::shared_ptr<IObserver> o){
    std::list<std::shared_ptr<IObserver>>::iterator it =
        std::find(std::begin(observers), std::end(observers), o);
    //std::cout << "found: " << (*it)->name << ", " << *it << std::endl;
    if(it != end(observers)){
      observers.erase(it);
      std::cout << o->name << " is deleted" << std::endl;
    }
    else{
      std::cout << o->name << " not found" << std::endl;
    }
  }

  void NotifyObserver(){
    for(const auto& item : observers){
      item->Update(tnc);
    }
  }
  //! оповещение наблюдателей о появлении новых данных
  void CtrlChanged(){
    NotifyObserver();
  }

  void SetCtrl(const TNC_TABLE& t){
    tnc = t;
    CtrlChanged();
  }

  ~Sau(){
    std::cout << "Sau destructor: " << std::endl;
    for(auto& item : observers){
      std::cout << item->name << ", "  << item.get() << ", " << item.use_count() << std::endl;
      //item.reset();
    }
    observers.clear();
  }
public:
  TNC_TABLE tnc;
  std::list<std::shared_ptr<IObserver>> observers;
};

/**
  @class Device7EP
  @brief класс объекта-наблюдателя приемного устройства 7ЕП ("многие")
*/
class Device7EP: public IObserver, IDisplay, std::enable_shared_from_this<Device7EP>{
public:
  Device7EP(ISubject& s): sau(s){
    name = "Device7EP";
    clockFrequency = 100'000'000;
    //p = std::shared_ptr<IObserver>(std::shared_from_this());
    p = std::shared_ptr<IObserver>(this);
    sau.RegisterObserver(p);
  }

  ~Device7EP(){
    std::cout << "Device7EP destructor. " << std::endl;
  }

  void Update(const TNC_TABLE& tnc){
    ctrl7ep.time = tnc.time * clockFrequency;
    ctrl7ep.tp = tnc.tp * clockFrequency;
    Display();
  }

  void Display(){
    std::cout << "Current ctrl "<< name << ": " <<
        "time " << std::setw(12) << ctrl7ep.time << " clocks, " <<
        "tp " << std::setw(6) << ctrl7ep.tp << " clocks." << std::endl;
  }
public:
  CTRL_7EP ctrl7ep; //!< структура управления 7ЕП
  ISubject& sau;     //!< ссылка на субъект САУ
  unsigned int clockFrequency = 0;  //!< тактовая частота ПЛИС
};

/**
  @class Device7EM
  @brief класс объекта-наблюдателя передающего устройства 7ЕМ ("многие")
*/
class Device7EM: public IObserver, IDisplay{
public:
  Device7EM(ISubject& s): sau(s){
    name = "Device7EM";
    clockFrequency = 50'000'000;
    p = std::shared_ptr<IObserver>(this);
    sau.RegisterObserver(p);
  }

  ~Device7EM(){
    std::cout << "Device7EM destructor. " << std::endl;
  }

  void Update(const TNC_TABLE& tnc){
    ctrl7em.time = tnc.time * clockFrequency;
    ctrl7em.ti = tnc.ti * clockFrequency;
    Display();
  }

  void Display(){
    std::cout << "Current ctrl " << name << ": " <<
        "time " << std::setw(12) << ctrl7em.time << " clocks, " <<
        "ti " << std::setw(6) << ctrl7em.ti << " clocks." << std::endl;
  }
public:
  CTRL_7EM ctrl7em; //!< структура управления 7ЕМ
  ISubject& sau;     //!< ссылка на субъект САУ
  unsigned int clockFrequency;  //!< тактовая частота ПЛИС
};

#endif //OBSERVER_H
