/*В этой задаче вам нужно присваивать номера автобусным маршрутам.
А именно, для каждого маршрута, заданного множеством названий остановок, нужно либо
выдать новый номер (первому маршруту — 1, второму — 2 и т. д.), либо вернуть номер
существующего маршрута, которому соответствует такое множество остановок.

В отличие от задачи «Автобусные остановки — 2», наборы остановок, которые можно получить
друг из друга перестановкой элементов или добавлением/удалением повторяющихся,
следует считать одинаковыми.

Формат ввода
Сначала вводится количество запросов Q, затем Q описаний запросов.
Каждый запрос представляет собой положительное количество остановок N, за которым
следуют разделённые пробелом N названий остановок соответствующего маршрута
(не обязательно различных). Названия остановок состоят лишь из латинских букв и
символов подчёркивания.

Формат вывода
Выведите ответ на каждый запрос в отдельной строке.
Если маршрут с данным набором остановок уже существует, в ответ на соответствующий
запрос выведите Already exists for i, где i — номер маршрута с таким набором остановок.
В противном случае нужно выделить введённому набору остановок новый номер i и вывести
его в формате New bus i.
 *
*/
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main1()
{
  map<string, int> m = {{"one", 1}, {"one", 2}};

  cout << m.count("one") << endl;
  return 0;
}

int main()
{
  int q;
  cin >> q;
  map<set<string>, int> m;

  //auto start= steady_clock::now();

  for(int i=0; i<q; i++)
  {
    int n;
    cin >> n;
    string busStation;
    set<string> busStations;
    for(int j=0; j<n; j++)
    {
      cin >> busStation;
      busStations.insert(busStation);
    }
    unsigned int sz = m.count(busStations);
    if(sz > 0)
    {
      cout << "Already exists for " + std::to_string(m[busStations]) << endl;
    }else
    {
      unsigned int busCount = m.size();
      m[busStations] = busCount + 1;
      cout << "New bus " + std::to_string(m[busStations]) << endl;
    }
  }

  //for(const string& s: messages)
    //cout << s << endl;

  //auto finish= steady_clock::now();
  //cout<< "Time "<< duration_cast<microseconds>(finish- start).count()<< " us"<< endl;
  return 0;
}
