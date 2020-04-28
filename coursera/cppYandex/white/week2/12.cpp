/*Реализуйте справочник столиц стран.
На вход программе поступают следующие запросы:
CHANGE_CAPITAL country new_capital — изменение столицы страны country на new_capital,
либо добавление такой страны с такой столицей, если раньше её не было.
RENAME old_country_name new_country_name — переименование страны из old_country_name
в new_country_name.
ABOUT country — вывод столицы страны country.
DUMP — вывод столиц всех стран.

Формат ввода
В первой строке содержится количество запросов Q, в следующих Q строках — описания запросов. Все названия стран и столиц состоят лишь из латинских букв, цифр и символов подчёркивания.

Формат вывода
Выведите результат обработки каждого запроса:
В ответ на запрос CHANGE_CAPITAL country new_capital выведите
Introduce new country country with capital new_capital, если страны country раньше
не существовало;
Country country hasn't changed its capital, если страна country до текущего
момента имела столицу new_capital;
Country country has changed its capital from old_capital to new_capital, если
страна country до текущего момента имела столицу old_capital, название которой не
совпадает с названием new_capital.

В ответ на запрос RENAME old_country_name new_country_name выведите
Incorrect rename, skip, если новое название страны совпадает со старым, страна
old_country_name не существует или страна new_country_name уже существует;
Country old_country_name with capital capital has been renamed to new_country_name,
если запрос корректен и страна имеет столицу capital.

В ответ на запрос ABOUT country выведите
Country country doesn't exist, если страны с названием country не существует;
Country country has capital capital, если страна country существует и имеет столицу capital.

В ответ на запрос DUMP выведите
There are no countries in the world, если пока не было добавлено ни одной страны;
последовательность пар вида country/capital, описывающую столицы всех стран, если в мире
уже есть хотя бы одна страна. При выводе последовательности пары указанного вида
необходимо упорядочить по названию страны и разделять между собой пробелом.
*/
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main1()
{
  map<string, vector<string>> m = { {"one", {"new", "old"}} };

  cout << "Size = " << m.size() << endl;
  m["two"] = {"", ""};
  cout << "Size = " << m.size() << endl;
  for(auto item: m)
    cout << item.first << " " << item.second[0] << " " << item.second[1] << endl;

  return 0;
}

int main()
{
  int q;
  map<string, string> catalog;
  string command;
  cin >> q;
  vector<string> messages;

  for(int i=0; i<q; i++)
  {
    cin >> command;
    string message;
    if(command == "CHANGE_CAPITAL")
    {
      string country, newCapital;
      cin >> country >> newCapital;
      if(catalog.count(country) == 0)
      {
        catalog[country] = newCapital;
        message = "Introduce new country " + country + " with capital " + newCapital;
      }
      else if (catalog[country] == newCapital)
      {
        message = "Country " + country + " hasn't changed its capital";
      }
      else if(catalog[country] != newCapital)
      {
        string oldCapital = catalog[country];
        catalog[country] = newCapital;
        message = "Country " + country + " has changed its capital from " +
            oldCapital + " to " + newCapital;
      }
      messages.push_back(message);
    } // if(command == "CHANGE_CAPITAL")
    else if(command == "RENAME")
    {
      string oldCountryName,  newCountryName;
      cin >> oldCountryName >> newCountryName;
      if(oldCountryName == newCountryName || catalog.count(oldCountryName) == 0 ||
          catalog.count(newCountryName) > 0)
      {
        message = "Incorrect rename, skip";
      }
      else
      {
        message = "Country " + oldCountryName + " with capital " +
            catalog[oldCountryName] + " has been renamed to " + newCountryName;
        string tmpCapital = catalog[oldCountryName];
        catalog.erase(oldCountryName);
        catalog[newCountryName] = tmpCapital;
      }
      messages.push_back(message);
    } // if(command == "RENAME")
    else if(command == "ABOUT")
    {
      string country;
      cin >> country;
      if(catalog.count(country) == 0 )
      {
        message = "Country " + country + " doesn't exist";
      }
      else
      {
        message = "Country " + country + " has capital " + catalog[country];
      }
      messages.push_back(message);
    } // if(command == "RENAME")
    else if(command == "DUMP")
    {
      message = "";
      if(catalog.size() == 0)
      {
        message = "There are no countries in the world";
      }
      else
      {
        for(auto item : catalog)
        {
          message += item.first + "/" + item.second + " ";
        }
      }
      messages.push_back(message);
    } // if(command == "RENAME")
  }

  for (const string& item : messages)
    cout << item << endl;

  return 0;
}
