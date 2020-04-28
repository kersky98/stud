/*У каждого из нас есть повторяющиеся ежемесячные дела, каждое из которых нужно
 * выполнять в конкретный день каждого месяца: оплата счетов за электричество,
 * абонентская плата за связь и пр. Вам нужно реализовать работу со списком таких
 * дел на месяц, а именно, реализовать набор следующих операций:
ADD i s
Назначить дело с названием s на день i текущего месяца.

DUMP i
Вывести все дела, запланированные на день i текущего месяца.

NEXT
Перейти к списку дел на новый месяц. При выполнении данной команды вместо текущего
(старого) списка дел на текущий месяц создаётся и становится активным (новый) список
дел на следующий месяц: все дела со старого списка дел копируются в новый список.
После выполнения данной команды новый список дел и следующий месяц становятся текущими,
а работа со старым списком дел прекращается. При переходе к новому месяцу необходимо
обратить внимание на разное количество дней в месяцах:
если следующий месяц имеет больше дней, чем текущий, «дополнительные» дни необходимо
оставить пустыми (не содержащими дел);
если следующий месяц имеет меньше дней, чем текущий, дела со всех «лишних» дней
необходимо переместить на последний день следующего месяца.

Замечания
Историю списков дел хранить не требуется, работа ведется только с текущим списком дел
текущего месяца. Более того, при создании списка дел на следующий месяц, он «перетирает»
предыдущий список.
Обратите внимание, что количество команд NEXT в общей последовательности команд при
работе со списком дел может превышать 11.
Начальным текущим месяцем считается январь.
Количества дней в месяцах соответствуют Григорианскому календарю с той лишь разницей,
что в феврале всегда 28 дней.

Формат ввода
Сначала число операций Q, затем описания операций.

Названия дел s уникальны и состоят только из латинских букв, цифр и символов
подчёркивания. Номера дней i являются целыми числами и нумеруются от 1 до размера
текущего месяца.

Формат вывода
Для каждой операции типа DUMP в отдельной строке выведите количество дел в
соответствующий день, а затем их названия, разделяя их пробелом. Порядок вывода дел в
рамках каждой операции значения не имеет.
*/
#include <iostream>
#include <vector>
using namespace std;

int main1()
{
  vector<int> a = {1, 2, 3};
  vector<int> b = {4, 5, 6};

  a.insert(begin(a), begin(b), end(b));
  a.emplace(--end(a), 11);
  for (auto i : a)
    cout << i << " ";

  return 0;
}

int main() {
  int q,
  currentMonth = 0,
  nextMonth = 0;
  vector<int> yearDays = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  string command;

  cin >> q;
  //q = 1;

  vector<vector<string>> busineses(31);
  vector<vector<string>> businesesDump;
  //cout << busineses.size() << endl;
  //for(auto i : business)
    //cout << i << ", ";
  for(int i=0; i<q; i++)
  {
      cin >> command;
      if(command == "ADD")
	{
	  int day;
	  string business;
	  cin >> day >> business;
	  busineses[day-1].push_back(business);
	}
      else if(command == "DUMP")
      	{
      	  int day;
      	  string business;
      	  cin >> day;
      	  businesesDump.push_back(busineses[day-1]);
      	}
      if(command == "NEXT")
      	{
	  currentMonth = currentMonth % 12;
	  nextMonth = (currentMonth+1) % 12;
      	  unsigned int currentMonthDays = yearDays[currentMonth];
      	  unsigned int nextMonthDays = yearDays[nextMonth];

      	  vector<vector<string>> nextBusineses(nextMonthDays);
      	  if(nextMonthDays < currentMonthDays)
      	    {
      	      for (unsigned int i = 0; i < nextMonthDays; i++)
      	        nextBusineses[i] = busineses[i];
      	      for (unsigned int i = 0; i < currentMonthDays - nextMonthDays; i++)
      		{
      		  for(auto b : busineses[currentMonthDays - 1 - i])
      		    {
      		      nextBusineses[nextMonthDays-1].push_back(b);
      		    }
      		}
      	    }
      	  else
      	    {
      	      for (unsigned int i = 0; i < currentMonthDays; i++)
      		nextBusineses[i] = busineses[i];
      	    }
      	busineses = nextBusineses;
      	currentMonth = nextMonth;
      	}
  }

  for(auto iday : businesesDump)
    {

      cout << iday.size() << " ";
      for(auto i : iday)
	{
	  cout << i << " ";
	}
      cout << endl;
    }

  return 0;
}
