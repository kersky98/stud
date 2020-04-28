/*
 * printStats.cpp
 *
 *  Created on: 25 апр. 2020 г.
 *      Author: user
 */



#include "printStats.h"
#include "computeMedianAge.cpp"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void PrintStats(vector<Person> persons){
  int age = ComputeMedianAge(begin(persons), end(persons));
  cout << "Median age = " << age << endl;

  auto it = partition(begin(persons), end(persons), [](const Person& p){
    return p.gender == Gender::FEMALE;
  });
  age = ComputeMedianAge(begin(persons), it);
  cout << "Median age for females = " << age << endl;

  it = partition(begin(persons), end(persons), [](const Person& p){
    return p.gender == Gender::MALE;
  });
  age = ComputeMedianAge(begin(persons), it);
  cout << "Median age for males = " << age << endl;

  it = partition(begin(persons), end(persons), [](const Person& p){
    return p.gender == Gender::FEMALE && p.is_employed == true;
  });
  age = ComputeMedianAge(begin(persons), it);
  cout << "Median age for employed females = " << age << endl;

  it = partition(begin(persons), end(persons), [](const Person& p){
    return p.gender == Gender::FEMALE && p.is_employed == false;
  });
  age = ComputeMedianAge(begin(persons), it);
  cout << "Median age for unemployed females = " << age << endl;

  it = partition(begin(persons), end(persons), [](const Person& p){
    return p.gender == Gender::MALE && p.is_employed == true;
  });
  age = ComputeMedianAge(begin(persons), it);
  cout << "Median age for employed males = " << age << endl;

  it = partition(begin(persons), end(persons), [](const Person& p){
    return p.gender == Gender::MALE && p.is_employed == false;
  });
  age = ComputeMedianAge(begin(persons), it);
  cout << "Median age for unemployed males = " << age << endl;
}

void PrintStats_yandex(vector<Person> persons) {
    // Преобразуем порядок людей к следующему:
    //                  persons
    //                 /      \
    //          females        males
    //         /       \     /      \
    //      empl.  unempl. empl.   unempl.
    auto females_end = partition(
        begin(persons), end(persons), [](const Person& p) {
            return p.gender == Gender::FEMALE;
        }
    );
    auto employed_females_end = partition(
        begin(persons), females_end, [](const Person& p) {
            return p.is_employed;
        }
    );
    auto employed_males_end = partition(
        females_end, end(persons), [](const Person& p) {
            return p.is_employed;
        }
    );

    // Теперь интересующие нас группы находятся в векторе непрерывно
    cout << "Median age = "
         << ComputeMedianAge(begin(persons), end(persons))          << endl;
    cout << "Median age for females = "
         << ComputeMedianAge(begin(persons), females_end)           << endl;
    cout << "Median age for males = "
         << ComputeMedianAge(females_end, end(persons))             << endl;
    cout << "Median age for employed females = "
         << ComputeMedianAge(begin(persons),  employed_females_end) << endl;
    cout << "Median age for unemployed females = "
         << ComputeMedianAge(employed_females_end, females_end)     << endl;
    cout << "Median age for employed males = "
         << ComputeMedianAge(females_end, employed_males_end)       << endl;
    cout << "Median age for unemployed males = "
         << ComputeMedianAge(employed_males_end, end(persons))      << endl;
}
