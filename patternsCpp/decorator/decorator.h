#ifndef DECORATOR_H
#define DECORATOR_H
/*
*/

#include <iostream>
#include <string>
#include <complex>

/**
  @class IBaseSignal
  @brief интерфейс(абстрактный класс) Сигнал
*/
class IBaseSignal{
public:
  //! получение дескриптора
  virtual std::string GetDescription(){
    return description;
  }
  //! выполенение обработки сигнальной информации
  virtual std::complex<double> Calculate() = 0;
  virtual ~IBaseSignal(){
    //std::cout << "~IBaseSignal Destructor" << std::endl;
  };
protected:
  //!< дескриптор класса
  std::string description;
};

/**
  @class Signal
  @brief класс Сигнал
*/
class Signal: public IBaseSignal{
public:
  Signal(){
    signal = std::complex<double>(2, 3);
    description = "Signal";
  }

  ~Signal(){
    std::cout << "~Signal Destructor" << std::endl;
  }

  std::complex<double> Calculate(){
    signal += std::complex<double>(1, 1);
    return signal;
  }
private:
  //! комплексный сигнал
  std::complex<double> signal;
};

/**
  @class IDecorator
  @brief интерфейс(абстрактный класс) декоратор, нужен что бы пользователь обязательно в
  дочерних классах переопределил метод GetDescription()
*/
class IDecorator: public IBaseSignal{
  virtual std::string GetDescription() = 0;
};

/**
  @class Fdn
  @brief класс ФДН, возможное использование:
  1) как декоратор над классом Signal, в случае последовательности Signal->Fdn->Sa-Plo
  2) как декоратор над классом Sa, в случае последовательности Signal->Sa->Fdn-Plo
*/
class Fdn: public IDecorator{
public:
  Fdn(IBaseSignal* base){
    this->base = base;
    description = "Fdn";
    fdn = std::complex<double>(0, 0);
  }

  ~Fdn(){
    delete base;
    std::cout << "~Fdn Destructor" << std::endl;
  }

  std::string GetDescription(){
    return base->GetDescription() + ", " + description;
  }

  //! выполенение вычисления диаграмм направленности
  std::complex<double> Calculate(){
    fdn = base->Calculate() + std::complex<double>(1, 1);
    return fdn;
  }
private:
  //! указатель на декорируемый (базовый) класс, в данном случае на Signal или Sa
  IBaseSignal* base;
  //! диаграммы направленности
  std::complex<double> fdn;
};

/**
  @class Sa
  @brief класс СА, возможное использование:
  1) как декоратор над классом Fdn, в случае последовательности Signal->Fdn->Sa-Plo
  2) как декоратор над классом Signal, в случае последовательности Signal->Sa->Fdn-Plo
*/
class Sa: public IDecorator{
public:
  Sa(IBaseSignal* base){
    this->base = base;
    description = "Sa";
    spectrum = std::complex<double>(0, 0);
  }

  ~Sa(){
    delete base;
    std::cout << "~Sa Destructor" << std::endl;
  }

  std::string GetDescription(){
    return base->GetDescription() + ", " + description;
  }

  //! выполнение вычислений спектров по диаграммам
  std::complex<double> Calculate(){
    spectrum = base->Calculate() + std::complex<double>(1, 1);
    return spectrum;
  }
private:
  //! указатель на декорируемый (базовый) класс, в данном случае на Signal или Fdn
  IBaseSignal* base;
  //! спектральные отсчеты по диаграммам направленности или сигналам с приемника
  std::complex<double> spectrum;
};

/**
  @class Plo
  @brief класс ПЛО, возможное использование:
  1) как декоратор над классом Sa, в случае последовательности Signal->Fdn->Sa->Plo (целевой канал)
  2) как декоратор над классом Fdn, в случае последовательности Signal->Fdn->Plo (помеховый канал)
*/
class Plo: public IDecorator{
public:
  Plo(IBaseSignal* base){
    this->base = base;
    description = "Plo";
    plo = std::complex<double>(0, 0);
  }

  ~Plo(){
    delete base;
    std::cout << "~Plo Destructor" << std::endl;
  }

  std::string GetDescription(){
    return base->GetDescription() + ", " + description;
  }

  std::complex<double> Calculate(){
    plo = base->Calculate() + std::complex<double>(1, 1);
    return plo;
  }
private:
  //! указатель надекорируемый (базовый) класс, в данном случае на Signal, Fdn или Sa
  IBaseSignal* base;
  //! результат пороговой обработки
  std::complex<double> plo;
};

/**
  @class Tzk
  @brief класс ТЗК, возможное использование как декоратор над классом Plo
*/
class Tzk: public IDecorator{
public:
  Tzk(IBaseSignal* base){
    this->base = base;
    description = "Tzk";
    tzk = std::complex<double>(0, 0);
  }

  ~Tzk(){
    delete base;
    std::cout << "~Tzk Destructor" << std::endl;
  }
  std::string GetDescription(){
    return base->GetDescription() + ", " + description;
  }

  std::complex<double> Calculate(){
    tzk = base->Calculate() + std::complex<double>(1, 1);
    return tzk;
  }
private:
  //! указатель на декорируемый (базовый) класс, в данном случае на Plo
  IBaseSignal* base;
  //! текущие замеры координат
  std::complex<double> tzk;
};

#endif //DECORATOR_H
