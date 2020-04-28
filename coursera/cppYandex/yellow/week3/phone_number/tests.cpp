  /* Принимает строку в формате +XXX-YYY-ZZZZZZ
     Часть от '+' до первого '-' - это код страны.
     Часть между первым и вторым символами '-' - код города
     Всё, что идёт после второго символа '-' - местный номер.
     Код страны, код города и местный номер не должны быть пустыми.
     Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument.
     Проверять, что номер содержит только цифры, не нужно.

     Примеры:
     * +7-495-111-22-33
     * +7-495-1112233
     * +323-22-460002
     * +1-2-coursera-cpp
     * 1-2-333 - некорректный номер - не начинается на '+'
     * +7-1233 - некорректный номер - есть только код страны и города
  */
#include "phone_number.h"
#include "test_runner.h"

void TestPositive(){
  PhoneNumber p("+7-495-111-22-33");
  AssertEqual(p.GetCountryCode(), "7", "CountryCode: 7");
  AssertEqual(p.GetCityCode(), "495", "CityCode: 495");
  AssertEqual(p.GetLocalNumber(), "111-22-33", "LocalNumber: 111-22-33");
  AssertEqual(p.GetInternationalNumber(), "+7-495-111-22-33", "InternationalNumber: +7-495-111-22-33");

  PhoneNumber p1("+7-495-1112233");
  AssertEqual(p1.GetCountryCode(), "7", "CountryCode: 7");
  AssertEqual(p1.GetCityCode(), "495", "CityCode: 495");
  AssertEqual(p1.GetLocalNumber(), "1112233", "LocalNumber: 1112233");
  AssertEqual(p1.GetInternationalNumber(), "+7-495-1112233", "InternationalNumber: +7-495-1112233");

  PhoneNumber p2("+323-22-460002");
  AssertEqual(p2.GetCountryCode(), "323", "CountryCode: 323");
  AssertEqual(p2.GetCityCode(), "22", "CityCode: 22");
  AssertEqual(p2.GetLocalNumber(), "460002", "LocalNumber: 460002");
  AssertEqual(p2.GetInternationalNumber(), "+323-22-460002", "InternationalNumber: +323-22-460002");

  PhoneNumber p3("+1-2-coursera-cpp");
  AssertEqual(p3.GetCountryCode(), "1", "CountryCode: 1");
  AssertEqual(p3.GetCityCode(), "2", "CityCode: 2");
  AssertEqual(p3.GetLocalNumber(), "coursera-cpp", "LocalNumber: coursera-cpp");
  AssertEqual(p3.GetInternationalNumber(), "+1-2-coursera-cpp", "InternationalNumber: +1-2-coursera-cpp");
}


void TestNegative(){
  bool flag = false;
  try{
    flag = false;
    PhoneNumber p("1-2-333");
  }catch(invalid_argument &arg){
    flag = true;
  }
  Assert(flag, "TestNegative");

  try{
    flag = false;
    PhoneNumber p1("+7-1233");
  }catch(invalid_argument &arg){
    flag = true;
  }
  Assert(flag, "TestNegative");
}
