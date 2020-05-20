#ifndef OBSERVER_H
#define OBSERVER_H
/**
  @note: паттерн Наблюдатель определяет отношение "один-ко-многим".
*/

#include <iostream>
#include <memory>
#include <list>
#include <algorithm>

/**
  @class IObserver
  @brief интерфейс наблюдателя
*/
class IObserver{
public:
  /**
    @fn Update
    @brief виртуальный метод обновления состояния
    @param[in] temp - температура окружающей среды
    @param[in] humidity - влажность окружающей среды
    @param[in] pressure - давление окружающей среды
    @return none
  */
  virtual void Update(float temp, float humidity, float pressure){
    std::cout << "Virtual Update " << name << std::endl;
  };
  virtual ~IObserver(){};     //!< виртуальный деструктор класса
  std::string name;
};

/**
  @class IExchBehavior
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
  virtual ~ISubject(){};
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
  @class WeatherData
  @brief класс субъекта ("один")
*/
class WeatherData: public ISubject{
public:
  void RegisterObserver(const std::shared_ptr<IObserver> o){
    observers.push_back(o);
  }

  void RemoveObserver(const std::shared_ptr<IObserver> o){
    std::list<std::shared_ptr<IObserver>>::iterator it =
        std::find(std::begin(observers), std::end(observers), o);
    if(it != end(observers)){
      observers.erase(it);
    }
  }

  void NotifyObserver(){
    for(const auto item : observers){
      item->Update(temperature, humidity, pressure);
    }
  }
  //! оповещение наблюдателей о появлении новых данных
  void measurementChanged(){
    NotifyObserver();
  }

  void SetMeasurements(float temp, float humidity, float pressure){
    this->temperature = temp;
    this->humidity = humidity;
    this->pressure = pressure;
    measurementChanged();
  }
public:
  float temperature;
  float humidity;
  float pressure;
  std::list<std::shared_ptr<IObserver>> observers;
};

/**
  @class CurrentConditionsDisplay
  @brief класс объекта-наблюдателя ("многие")
*/
class CurrentConditionsDisplay: public IObserver, IDisplay{
public:
  CurrentConditionsDisplay(ISubject& wData): weatherData(wData){
    name = "CurrentConditionsDisplay";
    wData.RegisterObserver(std::make_shared<CurrentConditionsDisplay>(*this));
  }

  void Update(float temp, float humidity, float pressure){
    this->temperature = temp;
    this->humidity = humidity;
    this->pressure = pressure;
    Display();
  }

  void Display(){
    std::cout << "Current conditions: " << temperature << "C degrees, " <<
        humidity << "% humidity and pressure " <<
        pressure << " kPa" << std::endl;
  }
public:
  float temperature;
  float humidity;
  float pressure;
  ISubject& weatherData;
};

/**
  @class StatisticsDisplay
  @brief класс объекта-наблюдателя ("многие")
*/
class StatisticsDisplay: public IObserver, IDisplay{
public:
  StatisticsDisplay(ISubject& wData): weatherData(wData){
    name = "StatisticsDisplay";
    wData.RegisterObserver(std::make_shared<StatisticsDisplay>(*this));
  }

  void Update(float temp, float humidity, float pressure){
    meanTemperature = (meanTemperature*n + temp) / (n+1);
    meanHumidity = (meanHumidity*n + humidity) / (n+1);
    meanPressure = (meanPressure*n + pressure) / (n+1);
    n++;
    Display();
  }

  void Display(){
    std::cout << "Mean temperature/humidity/pressure: " << meanTemperature << " / " <<
        meanHumidity << " / " << meanPressure << std::endl;
  }
public:
  float meanTemperature = 0;
  float meanHumidity = 0;
  float meanPressure = 0;
  int n = 0;
  ISubject& weatherData;
};

#endif //OBSERVER_H
