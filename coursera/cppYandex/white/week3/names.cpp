/*Условие
Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии
и имени.
Считайте, что в каждый год может произойти не более одного изменения фамилии и не более
одного изменения имени. При этом с течением времени могут открываться всё новые факты из
прошлого человека, поэтому года́ в последовательных вызовах методов ChangeLastName и
ChangeFirstName не обязаны возрастать.
Гарантируется, что все имена и фамилии непусты.
Строка, возвращаемая методом GetFullName, должна содержать разделённые одним пробелом
имя и фамилию человека по состоянию на конец данного года.
Если к данному году не случилось ни одного изменения фамилии и имени,
верните строку "Incognito".
Если к данному году случилось изменение фамилии, но не было ни одного изменения имени,
верните "last_name with unknown first name".
Если к данному году случилось изменение имени, но не было ни одного изменения фамилии,
верните "first_name with unknown last name".
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
private:
  // приватные поля
  string firstName;
  string lastName;
  map<int, string> mFirst;
  map<int, string> mLast;
};


int main3() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }

  return 0;
}

int main2()
{
  Person person;

  person.ChangeFirstName(1965, "Polina");
  cout << person.GetFullName(1964) << endl;
  cout << person.GetFullName(1966) << endl;
  return 0;
}

int main1()
{
  Person person;

  person.ChangeFirstName(65, "p");
  person.ChangeLastName(67, "s");
  person.ChangeFirstName(70, "a");
  cout << person.GetFullName(66) << endl;

  return 0;
}

int main4(){
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }

  cout << "=============================================\n\n";
  person.ChangeFirstName(1900, "Solnishko");
  for (int year : {1941, 1965, 1967, 1969, 1970, 1990}) {
    cout << person.GetFullName(year) << endl;
  }

  cout << "=============================================\n\n";
  person.ChangeLastName(1900, "Lesnoe");
  for (int year : {1941, 1965, 1967, 1969, 1970, 1990}) {
    cout << person.GetFullName(year) << endl;
  }


  return 0;
}

int main()
{
  Person person;
  //case 1
  person.ChangeLastName(3, "3_2nd");
  person.ChangeLastName(6, "6_2nd");

  for (int year : {3, 4, 5, 6}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeFirstName(-1, "-1_1st");
  person.ChangeFirstName(2, "2_1st");

  for (int year : {-1, 0, 1, 2, 3, 6}) {
    cout << person.GetFullName(year) << endl;
  }

  //case 2
 person.ChangeLastName (1, "1_second");
 person.ChangeFirstName(0, "0_first");
 person.ChangeFirstName(1, "1_first");
 person.ChangeFirstName(0, "3_first");

 cout << person.GetFullName(0) << endl;
 cout << person.GetFullName(1)<< endl;
 cout << person.GetFullName(2)<< endl;
 cout << person.GetFullName(0) << endl;

 //3 case
  cout << person.GetFullName(2000) << endl;

  person.ChangeLastName(1968, "1968_2nd");
  person.ChangeLastName(1967, "1967_2nd");
  person.ChangeLastName(1965, "1965_2nd");
  person.ChangeLastName(1966, "1966_2nd");

  for (int year : {1900, 1920, 1950, 1965, 1966, 1967, 1968}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeFirstName(1920, "1920_1st");
  person.ChangeFirstName(1900, "1900_1st");
  person.ChangeFirstName(1965, "1965_1st");
  person.ChangeFirstName(1950, "1950_1st");

  for (int year : {1900, 1920, 1950, 1965, 1966, 1967, 1968}) {
    cout << person.GetFullName(year) << endl;
  }
  return 0;
}
