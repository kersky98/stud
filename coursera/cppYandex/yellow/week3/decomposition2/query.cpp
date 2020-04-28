#include "query.h"

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
