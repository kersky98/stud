#include "responses.h"

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
