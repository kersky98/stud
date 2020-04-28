/*Условие
Дополните класс из предыдущей задачи «Имена и фамилии — 1» методом GetFullNameWithHistory:
В отличие от метода GetFullName, метод GetFullNameWithHistory должен вернуть не только
последние имя и фамилию к концу данного года, но ещё и все предыдущие имена и фамилии
в обратном хронологическом порядке. Если текущие факты говорят о том, что человек два
раза подряд изменил фамилию или имя на одно и то же, второе изменение при формировании
истории нужно игнорировать.
*/
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    // добавить факт изменения имени на first_name в год year
    mFirst[year] = first_name;
    firstName = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    // добавить факт изменения фамилии на last_name в год year
    mLast[year] = last_name;
    lastName = last_name;
  }
  string GetFullName(int year) {
    string message;
    //Если к данному году не случилось ни одного изменения фамилии и имени,
    //верните строку "Incognito".
    if(mFirst.begin()->first > year || mLast.begin()->first > year)
    {
      message = "Incognito";
    }//Если к данному году случилось изменение фамилии, но не было ни одного изменения имени,
    //верните "last_name with unknown first name".
    if((mLast.size() > 0 && mLast.begin()->first <= year) &&
        (mFirst.begin()->first > year || mFirst.size() == 0))
    {
      message =  (--mLast.upper_bound(year))->second + " with unknown first name";
    }//Если к данному году случилось изменение имени, но не было ни одного изменения фамилии,
    //верните "first_name with unknown last name".
    if((mFirst.size() > 0 && mFirst.begin()->first <= year) &&
        (mLast.begin()->first > year || mLast.size() == 0))
    {
      message =  (--mFirst.upper_bound(year))->second + " with unknown last name";
    }

    if(mFirst.size() > 0 && mLast.size() > 0 &&
        mFirst.begin()->first <= year && mLast.begin()->first <= year)
    {
      message = (--mFirst.upper_bound(year))->second + " " +
          (--mLast.upper_bound(year))->second;
    }
    return message;
  }
  string GetFullNameWithHistory(int year)
  {
    string message;
    if(mFirst.begin()->first > year || mLast.begin()->first > year)
    {
      message = "Incognito";
    }
    if((mLast.size() > 0 && mLast.begin()->first <= year) &&
        (mFirst.begin()->first > year || mFirst.size() == 0))
    {
      auto ilast = --mLast.upper_bound(year);
      message =  ilast->second + " ";

      message += getPrev(mLast, year);

      /*string prev = ilast->second;
      bool roundBrackets = false;
      message += "(";
      while(ilast-- != mLast.begin())
      {
        string curr = ilast->second;
        if(curr != prev){
          message += ilast->second + ", ";
          roundBrackets = true;
        }
        prev = curr;
      }
      if(roundBrackets){ message.pop_back(); message.pop_back(); message += ") ";}
      else {message.pop_back();}
*/
      message += "with unknown first name";
    }
    if((mFirst.size() > 0 && mFirst.begin()->first <= year) &&
        (mLast.begin()->first > year || mLast.size() == 0))
    {
      auto ifirst = --mFirst.upper_bound(year);
      message =  ifirst->second + " ";

      message += getPrev(mFirst, year);

      /*string prev = ifirst->second;
      bool roundBrackets = false;
      message += "(";
      while(ifirst-- != mFirst.begin())
      {
        string curr = ifirst->second;
        if(curr != prev){
          message += ifirst->second + ", ";
          roundBrackets = true;
        }
        prev = curr;
      }
      if(roundBrackets){ message.pop_back(); message.pop_back(); message += ") ";}
      else {message.pop_back();}*/

      message += "with unknown last name";
    }

    if(mFirst.size() > 0 && mLast.size() > 0 &&
        mFirst.begin()->first <= year && mLast.begin()->first <= year)
    {
      auto ifirst = --mFirst.upper_bound(year);
      message =  ifirst->second + " ";

      message += getPrev(mFirst, year);

      auto ilast = --mLast.upper_bound(year);
      message += ilast->second + " ";

      message += getPrev(mLast, year);
      message.pop_back();

    }
    return message;
  }
private:
  // приватные поля
  string firstName;
  string lastName;
  map<int, string> mFirst;
  map<int, string> mLast;
  string getPrev(map<int, string> m, int year)
  {
    string message;
    auto ilast = --m.upper_bound(year);
    string prev = ilast->second;
    bool roundBrackets = false;
    message += "(";
    while(ilast-- != m.begin())
    {
      string curr = ilast->second;
      if(curr != prev){
        message += ilast->second + ", ";
        roundBrackets = true;
      }
      prev = curr;
    }
    if(roundBrackets){ message.pop_back(); message.pop_back(); message += ") ";}
    else {message.pop_back();}
    return message;
  }
};

int main2() {
  Person person;
  //person.ChangeLastName(1900, "Sokolov");
  //person.ChangeLastName(1910, "Sokolov");
  //person.ChangeLastName(1930, "Sokolov");

  person.ChangeFirstName(1900, "Ivan");
  person.ChangeFirstName(1910, "Ivan1");
  person.ChangeFirstName(1930, "Ivan2");
  cout << person.GetFullNameWithHistory(1940) << endl;

  return 0;
}

int main() {
  Person person;

  person.ChangeFirstName(1900, "Eugene");
  person.ChangeLastName(1900, "Sokolov");
  person.ChangeLastName(1910, "Sokolov");
  person.ChangeFirstName(1920, "Evgeny");
  person.ChangeLastName(1930, "Sokolov");
  cout << person.GetFullNameWithHistory(1940) << endl;

  return 0;
}

int main3() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  person.ChangeFirstName(1990, "Polina");
  person.ChangeLastName(1990, "Volkova-Sergeeva");
  cout << person.GetFullNameWithHistory(1990) << endl;

  person.ChangeFirstName(1966, "Pauline");
  cout << person.GetFullNameWithHistory(1966) << endl;

  person.ChangeLastName(1960, "Sergeeva");
  for (int year : {1960, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  person.ChangeLastName(1961, "Ivanova");
  cout << person.GetFullNameWithHistory(1967) << endl;

  return 0;
}

int main1() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeFirstName(1965, "Appolinaria");

  person.ChangeLastName(1965, "Sergeeva");
  person.ChangeLastName(1965, "Volkova");
  person.ChangeLastName(1965, "Volkova-Sergeeva");

  for (int year : {1964, 1965, 1966}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  return 0;
}

int main2017()
{
  cout.precision(9);
  cout <<
      23452.05 +
      29080.55 +
      28015.32 +
      28808.09 +
      27749.25 << endl;
  return 0;
}
