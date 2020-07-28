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

using namespace std;

class Booking{
public:
  void Book(int64_t time, string hotel_name, unsigned int client_id, int room_count){
    time_.push_back(time);
    hotel_name_.push_back(hotel_name);
    client_id_.push_back(client_id);
    room_count_.push_back(room_count);
    current_time = time;
    begin_time = time - 86400;
    it_time = upper_bound(begin(time_), end(time_), begin_time);
  }
  int Clients(string hotel_name){
    size_t index = it_time - begin(time_);
    auto it_hotel = begin(hotel_name_) + index;
    auto it_client = begin(client_id_) + index;
    vector<unsigned int> clients;
    while(it_hotel != end(hotel_name_)){
      if(*it_hotel == hotel_name){
        clients.push_back(*it_client);
      }
      it_hotel++;
      it_client++;
    }
    set<unsigned int> s(begin(clients), end(clients));
    return s.size();
  }

  int Rooms(string hotel_name){
      size_t index = it_time - begin(time_);
      auto it_hotel = begin(hotel_name_) + index;
      auto it_room = begin(room_count_) + index;
      unsigned int rooms_count = 0;
      while(it_hotel != end(hotel_name_)){
        if(*it_hotel == hotel_name){
          rooms_count += *it_room;
        }
        it_hotel++;
        it_room++;
      }
      return rooms_count;
    }
private:
  int64_t current_time;
  int64_t begin_time;
  vector<int64_t> time_;
  vector<string> hotel_name_;
  vector<unsigned int> client_id_;
  vector<int> room_count_;
  vector<int64_t>::iterator it_time;
};

int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  Booking book;

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

  return 0;
}
