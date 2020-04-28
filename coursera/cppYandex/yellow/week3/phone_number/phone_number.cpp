#include "phone_number.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;


PhoneNumber::PhoneNumber(const string &international_number){
  istringstream ss(international_number);
  bool ok = true;
  ok = ok & (ss.peek() == '+');
  ss.ignore(1);
  ok = ok & static_cast<bool>(getline(ss, country_code_, '-'));
  ok = ok & static_cast<bool>(getline(ss, city_code_, '-'));
  ok = ok & static_cast<bool>(getline(ss, local_number_));

  if(!ok){
    throw invalid_argument(international_number);
  }

}

string PhoneNumber::GetCountryCode() const{ return country_code_; };

string PhoneNumber::GetCityCode() const{ return city_code_; };

string PhoneNumber::GetLocalNumber() const{ return local_number_; };

string PhoneNumber::GetInternationalNumber() const{
  return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}
