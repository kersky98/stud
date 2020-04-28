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

}

vector<string> CreateMessagesAllBuses(const vector<string>& buses,
                                      const vector<vector<string>>& stops)
{
  vector<string> messages;
  string message;
  map<string, vector<string>> m1;

  for(unsigned int i=0; i < buses.size(); i++)
  {
    for(const string&st : stops[i])
    m1[buses[i]].push_back(st);
  }

  for (const auto& item : m1)
  {
    message = "Bus " + item.first + ": ";
    for (const string& item1 : item.second)
      message += item1 + " ";
    messages.push_back(message);
  }

  /*for(unsigned int i=0; i < buses.size(); i++)
  {
    message = "Bus " + buses[i] + ": ";
    for(const auto& st : stops[i])
    {
      message += st + " ";
    }
    messages.push_back(message);
  }*/

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
  int q, ibus=0;
  // map<string, vector<string>> buses;
  vector<vector<string>> vStops;
  vector<string> vBuses;
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
      vector<string> busStopTmp;
      int stopCount;
      cin >> bus >> stopCount;
      vBuses.push_back(bus);
      for(int j=0; j < stopCount; j++)
      {
        cin >> busStop;
        busStopTmp.push_back(busStop);
      }
      vStops.push_back(busStopTmp);
      ibus++;
    } // if(command == "NEW_BUS")
    else if(command == "BUSES_FOR_STOP")
    {
      string stop;
      vector<string> busesForStop;
      cin >> stop;
      for (unsigned int i=0; i<vStops.size(); i++)
      {
        for (const auto& item : vStops[i])
        {
          if(stop == item)
            busesForStop.push_back(vBuses[i]);
        }
      }
      messages.push_back(CreateMessageBusesForStop(busesForStop));
    } // if(command == "BUSES_FOR_STOP")
    else if(command == "STOPS_FOR_BUS")
    {
      string bus;
      vector<string> stopsForBus;
      cin >> bus;
      message = "";
      for(unsigned int i=0; i < vBuses.size(); i++)
      {
        if(bus == vBuses[i])
        {
          for(unsigned int j=0; j < vStops[i].size(); j++)
          {
            message = "";
            for(unsigned int k=0; k < vBuses.size(); k++)
              for(unsigned int m=0; m < vStops[k].size(); m++)
              {
                if(vStops[k][m] == vStops[i][j] && vBuses[k] != vBuses[i])
                  message += vBuses[k] + " ";
              }
            if(message.empty())
              message = "Stop " + vStops[i][j] + ": " + "no interchange";
            else
              message = "Stop " + vStops[i][j] + ": " + message;
            messages.push_back(message);
          }
        }
      }
      if(message.empty())
        messages.push_back("No bus");
    } // if(command == "STOPS_FOR_BUS")
    else if(command == "ALL_BUSES")
    {
      vector<string> messagesTmp;
      messagesTmp = CreateMessagesAllBuses(vBuses, vStops);
      if(!messagesTmp.empty())
      {
        messages.insert(messages.end(), messagesTmp.begin(), messagesTmp.end());
      }else
      {
        messages.push_back("No buses");
      }
    } // if(command == "ALL_BUSES")
  }

  //cout << "Size = " << vBuses.size() << " " << vStops.size() << endl;
  PrintAllMessages(messages);
  //PrintAllBuses(buses);

  return 0;
}
