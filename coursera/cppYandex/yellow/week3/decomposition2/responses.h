#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct BusesForStopResponse {
  // Наполните полями эту структуру
  int count;
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
  // Наполните полями эту структуру
  int count;
  vector<pair<string, BusesForStopResponse>> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
  // Наполните полями эту структуру
  int count;
  vector<pair<string, vector<string>>> all_buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r);
