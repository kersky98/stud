#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  string operation_code;
  is >> operation_code;
  if(operation_code == "NEW_BUS"){
    q.type = QueryType::NewBus;
  }
  else if(operation_code == "BUSES_FOR_STOP"){
    q.type = QueryType::BusesForStop;
  }
  else if(operation_code == "STOPS_FOR_BUS"){
    q.type = QueryType::StopsForBus;
  }
  else if (operation_code == "ALL_BUSES"){
    q.type = QueryType::AllBuses;
  }

  q.bus.clear();
  q.stop.clear();
  q.stops.clear();

  switch (q.type) {
  case QueryType::NewBus:
    cin >> q.bus;
    int stop_count;
    cin >> stop_count;
    q.stops.resize(stop_count);
    for (string& stop : q.stops) {
      cin >> stop;
    }
    break;
  case QueryType::BusesForStop:
    cin >> q.stop;
    break;
  case QueryType::StopsForBus:
    cin >> q.bus;
    break;
  case QueryType::AllBuses:

    break;
  }
  return is;
}

struct BusesForStopResponse {
  // Наполните полями эту структуру
  int count;
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  // Реализуйте эту функцию
  if (r.count == 0) {
    os << "No stop";
  } else {
    for (const string& bus : r.buses) {
      os << bus << " ";
    }
  }
  return os;
}

struct StopsForBusResponse {
  // Наполните полями эту структуру
  int count;
  vector<pair<string, BusesForStopResponse>> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  // Реализуйте эту функцию
  if (r.count == 0) {
    os << "No bus";
  } else {
    bool flag_first = true;
    for (const auto& stop : r.stops) {
      if(!flag_first){
        os << endl;
      }
      flag_first = false;
      os << "Stop " << stop.first << ": ";
      if (stop.second.count == 0) {
        os << "no interchange";
      } else {
        for (const string& other_bus : stop.second.buses) {
          os << other_bus << " ";
        }
      }
    }
  }
  return os;
}

struct AllBusesResponse {
  // Наполните полями эту структуру
  int count;
  vector<pair<string, vector<string>>> all_buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  // Реализуйте эту функцию
  if (r.count == 0) {
    os << "No buses";
  } else {
    bool flag_first = true;
    for (const auto& bus_item : r.all_buses) {
      if(!flag_first){
        os << endl;
      }
      flag_first = false;
      os << "Bus " << bus_item.first << ": ";
      for (const string& stop : bus_item.second) {
        os << stop << " ";
      }
    }
  }
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    // Реализуйте этот метод
    buses_to_stops[bus] = stops;
    for (const string& stop : stops) {
      stops_to_buses[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    // Реализуйте этот метод
    BusesForStopResponse b;
    b.count = stops_to_buses.count(stop);
    if (b.count > 0) {
      for (const string& bus : stops_to_buses.at(stop)) {
        b.buses.push_back(bus);
      }
    }
    return b;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    // Реализуйте этот метод
    StopsForBusResponse s;
    s.count = buses_to_stops.count(bus);
    if (s.count > 0) {
      //s.stops.resize(s.count);
      for (const string& stop : buses_to_stops.at(bus)) {
        pair<string, BusesForStopResponse> b;
        //cout << "Stop " << stop << ": ";
        b.first = stop;
       if (stops_to_buses.at(stop).size() == 1) {
         //cout << "no interchange";
         b.second.count = 0;
       } else {
         for (const string& other_bus : stops_to_buses.at(stop)) {
           if (bus != other_bus) {
             b.second.count++;
             //cout << other_bus << " ";
             b.second.buses.push_back(other_bus);
           }
         }
       }
       s.stops.push_back(b);
     }
    }

    return s;
  }

  AllBusesResponse GetAllBuses() const {
    // Реализуйте этот метод
    AllBusesResponse all;
    all.count = buses_to_stops.size();

    if (all.count > 0) {
      for (const auto& bus_item : buses_to_stops) {
        all.all_buses.push_back(bus_item);
      }
    }

    return all;
  }
private:
  map<string, vector<string>> stops_to_buses;
  map<string, vector<string>> buses_to_stops;
};

// Не меняя тела функции main, реализуйте функции и классы выше


int main() {
  int query_count;
  Query q;
  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
