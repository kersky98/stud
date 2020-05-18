#ifndef STRATEGY_STRATEGY_H
#define STRATEGY_STRATEGY_H
/* Драйвер предоставляет функции обмена сообщениями как с устройством,
 * так и с системой управления. В общем случае это взаимодействие может
 * происходить по разным интерфейсам, например, драйвер общается с ячейкой
 * по шине VME, а с системой управления по Ethernet. Так как драйвер может
 * взаиможействовать не напрямую с устройством, а с другим драйвером, то
 * функциональную схему обменов можно предствить следующим образом:
 *            (Up layer) B221
 *             /|\       |
 *              |       Read
 *            Write      |
 *              |       \|/
 *             (driver Ya001)
 *             /|\       |
 *              |      Write
 *             Read      |
 *              |       \|/
 *           (Down layer) device Ya001
 * Назовем поведение обменов:
 * IExchBehavior - интерфейс(абстрактный класс) поведения записи/чтения
 * IExchBehavior* exchUpBehavior - наверх в вышестоящий драйвер или систему управления,
 * IExchBehavior* exchBehavior   - вниз в устройство или нижестоящий драйвер
*/

#include <iostream>
#include "serv_info.h"
/**
  @class IExchBehavior
  @brief интерфейс(абстрактный класс) поведения записи/чтения
*/
class IExchBehavior{
public:
  virtual bool Write() = 0;   //!< виртуальный метод записи
  virtual bool Read() = 0;    //!< виртуальный метод чтения
  virtual ~IExchBehavior(){}; //!< виртуальный деструктор класса
};

/**
  @class ExchVme
  @brief класс для реализации метода записи/чтения по интерфейсу VME
*/
class ExchVme: public IExchBehavior{
public:
/**
  @fn Write
  @brief ф-я реазлизации записи по VME
  @param без параметров
  @return true в случае успешной записи
*/
  bool Write(){
    std::cout << "WriteVme [ok]" << std::endl;
    return true;
  }
  /**
  @fn Read
  @brief ф-я реазлизации чтения по VME
  @param без параметров
  @return true в случае успешного чтения
*/
  bool Read(){
    std::cout << "ReadVme [ok]" << std::endl;
    return true;
  }
};

/**
  @class ExchEthernet
  @brief класс для реализации метода записи/чтения по интерфейсу Ethernet
*/
class ExchEthernet: public IExchBehavior{
public:
  /**
  @fn Write
  @brief ф-я реазлизации записи по Ethernet
  @param без параметров
  @return true в случае успешной записи
*/
  bool Write(){
    std::cout << "WriteEthernet [ok]" << std::endl;
    return true;
  }
  /**
  @fn Read
  @brief ф-я реазлизации чтения по Ethernet
  @param без параметров
  @return true в случае успешного чтения
*/
  bool Read()
  {
    std::cout << "ReadEthernet [ok]" << std::endl;
    return true;
  }
};

/**
  @class ExchImitator
  @brief класс для реализации метода записи/чтения к имитатору
*/
class ExchImitator: public IExchBehavior{
public:
/**
  @fn Write
  @brief ф-я реазлизации записи в имитатор
  @param без параметров
  @return true в случае успешной записи
*/
  bool Write(){
    std::cout << "WriteImitator [ok]" << std::endl;
    return true;
  }
  /**
  @fn Read
  @brief ф-я реазлизации чтения из имитатора
  @param без параметров
  @return true в случае успешного чтения
*/
  bool Read(){
    std::cout << "ReadImitator [ok]" << std::endl;
    return true;
  }
};

/**
  @class Device
  @brief базовый класс устройства из состава изделия
*/
class Device
{
protected:
  IExchBehavior* exchUpBehavior; //!< Указатель на методы записи/чтения вверх
  IExchBehavior* exchBehavior;   //!< Указатель на метод записи/чтения вниз
public:
  /**
  @fn PerformWriteUp
  @brief ф-я выполнения записи по Ethernet или VME, для самой ф-ии это уже прозрачно
  @param без параметров
  @return true в случае успешной записи
*/
  bool PerformWriteUp(){
    return exchUpBehavior->Write();
  }
  /**
  @fn PerformReadUp
  @brief ф-я выполнения чтения по Ethernet или VME, для самой ф-ии это уже прозрачно
  @param без параметров
  @return true в случае успешного чтения
*/
  bool PerformReadUp(){
    return exchUpBehavior->Read();
  }

  /**
  @fn PerformWrite
  @brief ф-я выполнения записи по Ethernet или VME, для самой ф-ии это уже прозрачно
  @param без параметров
  @return true в случае успешной записи
*/
  bool PerformWrite(){
    return exchBehavior->Write();
  }
  /**
  @fn PerformRead
  @brief ф-я выполнения чтения по Ethernet или VME, для самой ф-ии это уже прозрачно
  @param без параметров
  @return true в случае успешного чтения
*/
  bool PerformRead(){
    return exchBehavior->Read();
  }
  /**
  @fn SetExchUpBehavior
  @brief ф-я устновки метода записи/чтения (поведения) вверх по Ethernet или VME
  @param ie - указатель на интерфейс интерфейс поведения записи/чтения
*/
  void SetExchUpBehavior(IExchBehavior *ie){
    exchUpBehavior = ie;
  }
  /**
  @fn SetExchBehavior
  @brief ф-я устновки метода записи/чтения (поведения) по Ethernet или VME
  @param ie - указатель на интерфейс поведения записи/чтения
*/
  void SetExchBehavior(IExchBehavior *ie){
    exchBehavior = ie;
  }

  // общая для всех устройств функция
  void CommonFunction(){
    std::cout << "I'm CommonFunction for all Devices." << std::endl;
  }

  void SetInfo(const ServInfo& info ){
    this->info = info;
  }

  virtual ~Device(){};

  void ViewServInfo(){
    std::cout << "ServInfo: " <<
        "vid: " << unsigned(info.vid) << "; " <<
        "did: " << unsigned(info.did) << "; " <<
        "unique_number: " << unsigned(info.unique_number) << "; " <<
        "sw_ver: " << unsigned(info.sw_ver) << "; " <<
        "hw_ver: " << unsigned(info.hw_ver) << "; " <<
        "time_cnt: " << unsigned(info.time_cnt) << "; " <<
        "mem_sz: " << unsigned(info.mem_sz) << "; " << std::endl;
  }

  virtual void Display(){
    std::cout << std::endl << "I'm Virtual Device. " << std::endl;
  }
private:
  ServInfo info;
};

/**
  @class Ya400
  @brief класс конкретного устройства Я400(ФДН)
*/
class Ya400: public Device{
private:
  //WriteVme write2Vme;  //!< поведение записи по дефолту - VME
  //ReadVme readFromVme; //!< поведение чтения по дефолту - VME
  int a;
public:
  Ya400(){
    //exchBehavior = new ExchVme();
    //exchUpBehavior = new ExchEthernet();
    a = 5;
    Device::SetInfo({1, 2, 3, 4, 5, 6, 7});
    a = 5;
  }
  ~Ya400(){
  }
  /**
  @fn Display
  @brief ф-я вывода информации об устройстве
*/
  void Display() override{
    std::cout << std::endl << "I'm Ya400. " << "a = " << a << std::endl;
    Device::ViewServInfo();
  }
};

/**
  @class B221
  @brief класс конкретного устройства Б221(БУС)
*/
class B221: public Device
{
private:
  float b;
public:
  B221(){
    b = 5.5;
    Device::SetInfo({11, 12, 13, 14, 15, 16, 17});
  }
  ~B221(){
  }
  /**
  @fn Display
  @brief ф-я вывода информации об устройстве
  */
  void Display()override{
    std::cout << std::endl << "I'm B221. " << "b = " << b << std::endl;
    ViewServInfo();
  }
};

#endif //STRATEGY_STRATEGY_H
