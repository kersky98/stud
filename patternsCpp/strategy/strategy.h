//
// Created by user on 13.03.18.
//

#ifndef STRATEGY_STRATEGY_H
#define STRATEGY_STRATEGY_H

/**
  @class IWriteBehavior
  @brief интерфейс(абстрактный класс) поведения записи
*/
class IWriteBehavior
{
public:
  virtual bool Write() = 0;    //!< виртуальный метод записи
  virtual ~IWriteBehavior(){}; //!< виртуальный деструктор класса
};

/**
  @class IReadBehavior
  @brief интерфейс(абстрактный класс) поведения чтения
*/
class IReadBehavior
{
public:
  virtual bool Read() = 0;    //!< виртуальный метод чтения
  virtual ~IReadBehavior(){}; //!< виртуальный деструктор класса
};

/**
  @class Write2Vme
  @brief класс для реализации метода записи по интерфейсу VME
*/
class Write2Vme: public IWriteBehavior
{
public:
/**
  @fn Write
  @brief ф-я реазлизации записи по VME
  @param без параметров
  @return true в случае успешной записи
*/
  bool Write()
  {
    std::cout << "Write2Vme [ok]" << std::endl;
    return true;
  }
};

/**
  @class Write2Ethernet
  @brief класс для реализации метода записи по интерфейсу Ethernet
*/
class Write2Ethernet: public IWriteBehavior
{
public:
  /**
  @fn Write
  @brief ф-я реазлизации записи по Ethernet
  @param без параметров
  @return true в случае успешной записи
*/
  bool Write()
  {
    std::cout << "Write2Ethernet [ok]" << std::endl;
    return true;
  }
};

/**
  @class ReadFromVme
  @brief класс для реализации метода чтения по интерфейсу VME
*/
class ReadFromVme: public IReadBehavior
{
public:
  /**
  @fn Read
  @brief ф-я реазлизации чтения по VME
  @param без параметров
  @return true в случае успешного чтения
*/
  bool Read()
  {
    std::cout << "ReadFromVme [ok]" << std::endl;
    return true;
  }
};

/**
  @class ReadFromEthernet
  @brief класс для реализации метода чтения по интерфейсу Ethernet
*/
class ReadFromEthernet: public IReadBehavior
{
public:
  /**
  @fn Read
  @brief ф-я реазлизации чтения по Ethernet
  @param без параметров
  @return true в случае успешного чтения
*/
  bool Read()
  {
    std::cout << "ReadFromEthernet [ok]" << std::endl;
    return true;
  }
};


/**
  @class IDevice
  @brief интерфейс(абстрактный класс) устройства из состава изделия
*/
class PredIDevice
{
public:
  virtual ~PredIDevice(){}; //!< виртуальный деструктор
  /**
  @fn PerformWrite
  @brief ф-я выполнения записи по Ethernet или VME, для самой ф-ии это уже прозрачно
  @param без параметров
  @return true в случае успешной записи
*/
  virtual bool PerformWrite() = 0;
  /**
  @fn PerformRead
  @brief ф-я выполнения чтения по Ethernet или VME, для самой ф-ии это уже прозрачно
  @param без параметров
  @return true в случае успешного чтения
*/
  virtual bool PerformRead() = 0;


  virtual void Display()=0;
  virtual void CommonFunction() = 0;
};

/**
  @class IDevice
  @brief интерфейс(абстрактный класс) устройства из состава изделия
*/
class IDevice : public PredIDevice
{
protected:
  IReadBehavior  *readBehavior;  //!< Указатель на метод чтения
  IWriteBehavior *writeBehavior; //!< Указатель на метод записи
public:
  virtual ~IDevice(){}; //!< виртуальный деструктор
  /**
  @fn PerformWrite
  @brief ф-я выполнения записи по Ethernet или VME, для самой ф-ии это уже прозрачно
  @param без параметров
  @return true в случае успешной записи
*/
  bool PerformWrite(){return writeBehavior->Write();}
  /**
  @fn PerformRead
  @brief ф-я выполнения чтения по Ethernet или VME, для самой ф-ии это уже прозрачно
  @param без параметров
  @return true в случае успешного чтения
*/
  bool PerformRead(){return readBehavior->Read();}
  /**
  @fn SetWriteBehavior
  @brief ф-я устновки метода записи (поведения) по Ethernet или VME
  @param iw - указатель на интерфейс записи
*/
  void SetWriteBehavior(IWriteBehavior *iw){writeBehavior = iw;}
  /**
  @fn SetReadBehavior
  @brief ф-я устновки метода чтения (поведения) по Ethernet или VME
  @param ir - указатель на интерфейс чтения
*/
  void SetReadBehavior(IReadBehavior *ir){readBehavior = ir;}

  void CommonFunction(){ std::cout << "I'm CommonFunction for all Devices." << std::endl; }
};

/**
  @class Ya400
  @brief класс конкретного устройства Я400(ФДН)
*/
class Ya400: public IDevice
{
private:
  Write2Vme   write2Vme;   //!< поведение записи по дефолту - VME
  ReadFromVme readFromVme; //!< поведение чтения по дефолту - VME
  int a;
public:
  Ya400()
  {
    readBehavior = &readFromVme;
    writeBehavior = &write2Vme;
    a = 5;
  }
  /**
  @fn Display
  @brief ф-я вывода информации об устройстве
*/
  void Display(){std::cout << std::endl << "I'm Ya400." << a << std::endl;}
};

/**
  @class B420
  @brief класс конкретного устройства Б420(ФДН)
*/
class B420: public IDevice
{
private:
  Write2Ethernet write2Ethernet;     //!< поведение записи по дефолту - Ethernet
  ReadFromEthernet readFromEthernet; //!< поведение чтения по дефолту - Ethernet
  float b;
public:
  B420()
  {
    writeBehavior = &write2Ethernet;
    readBehavior = &readFromEthernet;
    b = 5.5;
  }
  /**
  @fn Display
  @brief ф-я вывода информации об устройстве
  */
  void Display(){std::cout << std::endl << "I'm B420." << b << std::endl;}
};

#endif //STRATEGY_STRATEGY_H
