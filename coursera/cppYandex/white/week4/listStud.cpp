/*Определите структуру «Студент» со следующими полями: имя, фамилия, день, месяц и
 * год рождения. Создайте вектор из таких структур, заполните его из входных данных и
 * затем по запросам выведите нужные поля.

Формат ввода
Первая строка содержит одно целое число N от 0 до 10000 — число студентов.
Далее идут N строк, каждая из которых содержит две строки длиной от 1 до 15 символов —
имя и фамилию очередного студента, и три целых числа от 0 до 1000000000 — день,
месяц и год рождения.
Следующая строка содержит одно целое число M от 0 до 10000 — число запросов.
Следующие M строк содержат строку длиной от 1 до 15 символов — запрос, и целое число от
0 до 1000000000 — номер студента (нумерация начинается с 1).

Формат вывода
Для запроса вида name K, где K от 1 до N, выведите через пробел имя и фамилию K-го студента.
Для запроса вида date K, где K от 1 до N, выведите через точку день, месяц и год рождения
K-го студента.
Для остальных запросов выведите bad request.

Пример ввода
3
Ivan Ivanov 1 1 1901
Petr Petrox 2 2 1902
Alexander Sidorov 3 3 1903
3
name 1
date 3
mark 5

Пример вывода
Ivan Ivanov
3.3.1903
bad request
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

struct Stud{
  string firstName;
  string lastName;
  unsigned int year;
  unsigned int month;
  unsigned int day;
};

void PrintStud(const vector<Stud>& v)
{
  for(Stud item : v)
  {
    cout << item.firstName << " " << item.lastName << " " << item.day << " " <<
        item.month << " " << item.year << endl;
  }
}

int main()
{
  unsigned int n;
  cin >> n;
  vector<Stud> stud(n);
  for(unsigned int i=0; i < stud.size(); i++)
  {
    cin >> stud[i].firstName >> stud[i].lastName >> stud[i].day >> stud[i].month >>
    stud[i].year;
  }
  //PrintStud(stud);
  unsigned int m;
  cin >> m;
  for(unsigned int i=0; i < m; i++)
  {
    string request;
    int k;
    cin >> request >> k;
    if(request == "name" && k > 0 && k <= int(stud.size()))
    {
      cout << stud[k-1].firstName << " " << stud[k-1].lastName << endl;
    }
    else if(request == "date" && k > 0 && k <= int(stud.size()))
    {
      cout << stud[k-1].day << "." << stud[k-1].month << "." << stud[k-1].year << endl;
    }
    else
    {
      cout << "bad request" << endl;
    }
  }

  return 0;
}
