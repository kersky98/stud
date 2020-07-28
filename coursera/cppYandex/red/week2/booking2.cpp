/*Разработайте систему бронирования отелей, позволяющую бронировать номера клиентами
и контролировать спрос владельцами отелей. Ваша программа должна обрабатывать следующие события:

BOOK time hotel_name client_id room_count — забронировать клиентом client_id room_count
номеров в отеле hotel_name в момент времени time. Время измеряется в секундах, отсчитываемых
от некоторого момента.

CLIENTS hotel_name — вывести количество различных клиентов, бронировавших номера в отеле
hotel_name за последние сутки. Более формально интересующий диапазон времени описывается
следующим образом: пусть current_time — время последнего события BOOK, тогда в данном запросе
нужно учесть все события с current_time − 86400 < time ⩽ current_time,
где 86400 — количество секунд в сутках. Обратите внимание, что последнее бронирование должно
учитываться, а бронирование, случившееся ровно за сутки до него, учитываться не должно.

ROOMS hotel_name — вывести количество номеров, забронированных за последние сутки в отеле hotel_name.

Формат входных данных
В первой строке вводится количество запросов Q — натуральное число, не превосходящее 10^5.
В следующих Q строках в соответствии с описанным выше форматом вводятся запросы. Гарантируется, что:

time — целое число в диапазоне от −10^18 до 10^18 и не убывает от события к событию.
hotel_name — строка из латинских букв и цифр, имеющая длину не более 12 символов.
client_id — натуральное число, не превосходящее 10^9.
room_count — целое положительное число, не превосходящее 1000.

Формат выходных данных
Для каждого запроса CLIENTS и ROOMS выведите единственное целое число — ответ на запрос.
Если указанный в запросе отель пока не имеет ни одного бронирования, выведите 0.

Ограничения
1 секунда на выполнение всех запросов. Все описанные в условии гарантии действительно справедливы
для всех тестов, на которых будет запускаться ваша программа. Проверять корректность тестов не нужно.
 * */

#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <numeric>
#include <stdint.h>
#include <algorithm>
#include <deque>

using namespace std;

class Booking2{
public:
  void Book(int64_t time, string hotel_name, unsigned int client_id, int room_count){
    tuple<int64_t, string, unsigned int, int> t =
        make_tuple(time, hotel_name, client_id, room_count);
    d.push_back(t);
    auto it_rem = upper_bound(begin(d), end(d), make_tuple(time - 86400+1, "", 0, 0));
    AddNew( prev(end(d)) );
    RemOld(begin(d), it_rem);
    if(it_rem != end(d)){
      d.erase(begin(d), it_rem);
    }
  }

  void AddNew(deque<tuple<int64_t, string, unsigned int, int >>::iterator it){
    tuple<int64_t, string, unsigned int, int>& t = *it;
    //int64_t time = get<0>(t);
    string hotel_name = get<1>(t);
    unsigned int client_id = get<2>(t);
    int room_count = get<3>(t);
    hotel_map[hotel_name][client_id]+=room_count;
    rooms_map[hotel_name] += room_count;
  }

  void RemOld(deque<tuple<int64_t, string, unsigned int, int >>::iterator lhs,
    deque<tuple<int64_t, string, unsigned int, int >>::iterator rhs){
    //int64_t time = get<0>(t);
    while(lhs != rhs){
      string hotel_name = get<1>(*lhs);
      unsigned int client_id = get<2>(*lhs);
      int room_count = get<3>(*lhs);
      hotel_map[hotel_name][client_id]-=room_count;
      rooms_map[hotel_name] -= room_count;
      if(hotel_map[hotel_name][client_id] <= 0){
        hotel_map[hotel_name].erase(client_id);
      }
      if(rooms_map[hotel_name] <= 0){
        rooms_map.erase(hotel_name);
      }
      lhs++;
    }
  }

  void Print(){
    cout << endl;
    for(auto item: d){
      cout << get<0>(item) << ", " << get<1>(item) << endl;
    }
  }
  int Clients(string hotel_name){
     return hotel_map[hotel_name].size();
  }

  int Rooms(string hotel_name){
    /*int rooms_count = 0;
    for(const auto& item : hotel_map[hotel_name]){
      rooms_count += item.second;
    }*/

    return rooms_map[hotel_name];
  }
private:
  deque<tuple<int64_t, string, unsigned int, int >> d;
  map<string, map<unsigned int, int>> hotel_map;
  map<string, int> rooms_map;
};

int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  Booking2 book;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;

    if (query_type == "BOOK") {
      uint64_t time;
      string hotel_name;
      unsigned int client_id;
      int room_count;
      cin >> time >> hotel_name >> client_id >> room_count;
      book.Book(time, hotel_name, client_id, room_count);

    }
    else if (query_type == "CLIENTS") {
      string hotel_name;
      cin >> hotel_name;
      cout << book.Clients(hotel_name) << endl;
    }
    else if (query_type == "ROOMS") {
      string hotel_name;
      cin >> hotel_name;
      cout << book.Rooms(hotel_name) << endl;
    }
  }
  //book.Print();
  return 0;
}
