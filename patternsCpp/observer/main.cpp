#include "observer.h"
#include <vector>
#include <memory>
#include <typeinfo>
#include <string>
using namespace std;

int main()
{
  cout << "Presentation of the OBSERVER pattern!" << endl;
  WeatherData weatherData;

  CurrentConditionsDisplay currentDisplay(weatherData);
  StatisticsDisplay statisticsDisplay(weatherData);

  cout << "Observers count = " << weatherData.observers.size() << endl;
  for(auto item : weatherData.observers){
    cout << "Observers name = " << item->name << endl;
  }

  weatherData.SetMeasurements(10.f, 100.f, 100.0f);
  weatherData.SetMeasurements(15.f, 90.f, 99.0f);
  weatherData.SetMeasurements(20.f, 80.f, 98.0f);

  //delete weatherData;
  return 0;
}
