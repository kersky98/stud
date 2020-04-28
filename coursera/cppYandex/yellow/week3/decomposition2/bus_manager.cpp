#include "bus_manager.h"


void BusManager::AddBus(const string& bus, const vector<string>& stops) {
  // Реализуйте этот метод
  buses_to_stops[bus] = stops;
  for (const string& stop : stops) {
    stops_to_buses[stop].push_back(bus);
  }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
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

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
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

