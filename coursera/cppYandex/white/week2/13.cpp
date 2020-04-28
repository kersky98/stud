/*Реализуйте систему хранения автобусных маршрутов. Вам нужно обрабатывать
 * следующие запросы:
NEW_BUS busstop_countstop1stop2 ... — добавить маршрут автобуса с названием bus и
stop_count остановками с названиями stop1, stop2, ...
BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через
остановку stop.
STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком автобусов,
на которые можно пересесть на каждой из остановок.
ALL_BUSES — вывести список всех маршрутов с остановками.

Формат ввода
В первой строке ввода содержится количество запросов Q, затем в Q строках следуют
описания запросов.

Гарантируется, что все названия маршрутов и остановок состоят лишь из латинских букв,
цифр и знаков подчёркивания.

Для каждого запроса NEW_BUS bus stop_count stop1stop2 ... гарантируется, что маршрут
bus отсутствует, количество остановок больше 0, а после числа stop_count следует именно
такое количество названий остановок, причём все названия в каждом списке различны.

Формат вывода
Для каждого запроса, кроме NEW_BUS, выведите соответствующий ответ на него:

На запрос BUSES_FOR_STOP stop выведите через пробел список автобусов, проезжающих через
эту остановку, в том порядке, в котором они создавались командами NEW_BUS. Если
остановка stop не существует, выведите No stop.

На запрос STOPS_FOR_BUS bus выведите описания остановок маршрута bus в отдельных строках
в том порядке, в котором они были заданы в соответствующей команде NEW_BUS. Описание
каждой остановки stop должно иметь вид Stop stop: bus1bus2 ..., где bus1bus2 ... —
список автобусов, проезжающих через остановку stop, в порядке, в котором они создавались
командами NEW_BUS, за исключением исходного маршрута bus. Если через остановку stop не
проезжает ни один автобус, кроме bus, вместо списка автобусов для неё выведите no
interchange. Если маршрут bus не существует, выведите No bus.

На запрос ALL_BUSES выведите описания всех автобусов в алфавитном порядке. Описание
каждого маршрута bus должно иметь вид Bus bus: stop1stop2 ..., где stop1stop2 ... —
список остановок автобуса bus в порядке, в котором они были заданы в соответствующей
команде NEW_BUS. Если автобусы отсутствуют, выведите No buses.
*/
#include <iostream>
#include <vector>
#include <map>
using namespace std;

void PrintAllBuses(const map<vector<string>, vector<string>>& m)
{
  if(m.size() > 0)
  {
    for (const auto& item : m)
      {
        cout << "Bus " << item.first[1] << ": ";
        for (const string& item1 : item.second)
          cout << item1 << " ";
        cout << endl;
      }
  }else
  {
    cout << "No buses" << endl;
  }
}

vector<string> CreateMessagesAllBuses(const map<vector<string>, vector<string>>& m)
{
  vector<string> messages;
  string message;
  map<string, vector<string>> m1;

  for(const auto& i : m)
  {
    m1[i.first[1]] = i.second;
  }

  for (const auto& item : m1)
  {
    message = "Bus " + item.first + ": ";
    for (const string& item1 : item.second)
      message += item1 + " ";
    messages.push_back(message);
  }

  return messages;
}

string CreateMessageBusesForStop(vector<string>& m)
{
  string message;

  if(m.size() > 0)
  {
    for (const auto& item : m)
    {
      message += item + " ";
    }
  }else
  {
    message = "No stop";
  }
  return message;
}

void PrintAllMessages(const vector<string>& m)
{
  if(m.size() > 0)
  {
    for (const auto& item : m)
    {
      cout << item << endl;
    }
  }else
  {
    cout << "No buses" << endl;
  }
}

int main1()
{
  map<vector<string>, vector<string>> m = { {{"1", "501"}, {"new", "old"}},
      {{"2", "5"}, {"new", "old", "qwe"}}};

  cout << "Size = " << m.size() << endl;
  PrintAllBuses(m);

  return 0;
}

int main()
{
  int q;
  map<vector<string>, vector<string>> buses;
  string command;
  cin >> q;
  vector<string> messages;

  for(int i=0; i<q; i++)
  {
    cin >> command;
    string message;
    if(command == "NEW_BUS")
    {
      string bus, busStop;
      int stopCount;
      cin >> bus >> stopCount;
      for(int j=0; j < stopCount; j++)
      {
        cin >> busStop;
        buses[{std::to_string(i), bus}].push_back(busStop);
      }
    } // if(command == "NEW_BUS")
    else if(command == "BUSES_FOR_STOP")
    {
      string stop;
      vector<string> busesForStop;
      cin >> stop;
      for(auto item : buses)
      {
        for (const string& item1 : item.second)
        {
          if(item1 == stop){
            busesForStop.push_back(item.first[1]);
            break;
          }
        }
      }
      messages.push_back(CreateMessageBusesForStop(busesForStop));
    } // if(command == "BUSES_FOR_STOP")
    else if(command == "STOPS_FOR_BUS")
    {
      string bus;
      vector<string> stopsForBus;
      bool busExist = false;
      cin >> bus;
      message = "";
      for(auto item : buses) // цикл по всем маршрутам
      {
        if(item.first[1] == bus) // если нужный маршрут
        {
          busExist = true;
          for(auto item1 : item.second) // цикл по остановкам выбранного маршрута
          {
            message = "";
            for(auto item2 : buses) // цикл по всем маршрутам для поиска номера автобуса, делающего остановку на остановке item1
            {
              if(item2.first[1] == bus) // если наш же маршрут
                continue;
              for(auto item3 : item2.second) // цикл по остановкам выбранного маршрута
              {
                if(item3 == item1)
                {
                  message += item2.first[1] + " ";
                }
              }
            } // for(auto item2 : buses)
            if(!message.empty())
            {
              message = "Stop " + item1 + ": " + message;
            }else
            {
              message = "Stop " + item1 + ": " + "no interchange";
            }
            messages.push_back(message);
          }
        }
      }

      if(busExist)
      {
        if (message.empty())
        {
          messages.push_back("no interchange");
        }
      }else
      {
        messages.push_back("No bus");
      }
    } // if(command == "STOPS_FOR_BUS")
    else if(command == "ALL_BUSES")
    {
      vector<string> messagesTmp;
      messagesTmp = CreateMessagesAllBuses(buses);
      if(!messagesTmp.empty())
      {
        //messages.insert(messages.end(), messagesTmp.begin(), messagesTmp.end());
        for(auto i : messagesTmp)
          messages.push_back(i);
      }else
      {
        messages.push_back("No buses");
      }
    } // if(command == "ALL_BUSES")
  }

  //cout << "Size = " << buses.size() << endl;
  PrintAllMessages(messages);
  //PrintAllBuses(buses);

  return 0;
}
