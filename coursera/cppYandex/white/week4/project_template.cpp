#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;
// Реализуйте функции и методы классов и при необходимости добавьте свои

class Date {
public:
  Date(int year=0, int month=0, int day=0)
  {
    this->year = year;
    this->month = month;
    this->day = day;
  }
  int GetYear() const {return year;};
  int GetMonth() const {return month;};
  int GetDay() const {return day;};
  void SetYear(int value) {year = value;};
  void SetMonth(int value) {month = value;};
  void SetDay(int value) {day = value;};
  string GetString() const
  {
    stringstream ss;
    string s1 = (month>0) ? "" : "-";
    string s2 = (day>0) ? "" : "-";
    ss << setw(4) << setfill('0') << year << "-" <<
        s1 << setw(2) << setfill('0') << abs(month) << "-" <<
        s2 << setw(2) << setfill('0') << abs(day);
    return ss.str();
  }
  void Print() const
  {
    cout << GetString();
  }
private:
  int year;
  int month;
  int day;
};

bool operator<(const Date& lhs, const Date& rhs){
  if(lhs.GetYear() == rhs.GetYear()){
    if(lhs.GetMonth() == rhs.GetMonth()){
      return lhs.GetDay() < rhs.GetDay();
    }else{
      return lhs.GetMonth() < rhs.GetMonth();
    }
  }else{
    return lhs.GetYear() < rhs.GetYear();
  }
}

bool CreateDate(const string& sdate, Date& date){
  stringstream ss(sdate);
  int year, month, day;
  ss >> year;
  if(ss && ss.peek() == '-'){
    ss.ignore(1);
    ss >> month;
    if(ss && ss.peek() == '-'){
      ss.ignore(1);
      ss >> day;
      if(ss && !ss.bad() && !ss.fail() && ss.eof()){
        if(month < 1 || month > 12){
          //cout << "Month value is invalid: " << month << endl;
          throw runtime_error("Month value is invalid: " + std::to_string(month));
          return false;
        }
        if(day < 1 || day > 31){
          //cout << "Day value is invalid: " << day << endl;
          throw runtime_error("Day value is invalid: " + std::to_string(day));
          return false;
        }
        Date d(year, month, day);
        date = d;
        return true;
      }else{
        throw runtime_error("Wrong date format: " + sdate);
      }
    }else{
      throw runtime_error("Wrong date format: " + sdate);
    }
  }else{
    throw runtime_error("Wrong date format: " + sdate);
  }
  return false;
}

class Database {
public:
  void AddEvent(const Date& date, const string& event){
    m[date].insert(event);
  }

  bool DeleteEvent(const Date& date, const string& event){
    bool flag = false;
    if(m.count(date) > 0 && m[date].count(event) > 0){
      m[date].erase(event);
      flag = true;
    }
    return flag;
  }

  int DeleteDate(const Date& date){
    int n = 0;
    if(m.count(date) > 0){
      n = m[date].size();
      m.erase(date);
    }
    return n;
  }

  vector<string> Find(const Date& date) const{
    vector<string> v;
    if(m.count(date) > 0){
      for(auto& item : m.at(date))
        v.push_back(item);
    }
    return v;
  }
  
  void Print() const{
    for(auto& item: m){
      string s = item.first.GetString();
      for(auto& event: item.second){
        cout << s << " " << event << endl;
      }
    }
  }
private:
  map<Date, set<string>> m;
};

int main1()
{
  Database db;
  db.AddEvent({2020, 4, 3}, "qwe");
  db.AddEvent({-2019, -13, -3}, "zxc");
  db.AddEvent({2019, 3, 3}, "asd");
  db.AddEvent({2018, 3, 3}, "qaz");
  db.AddEvent({2018, 3, 3}, "qaz");
  db.Print();

  cout << boolalpha << db.DeleteEvent({2019, 3, 3}, "asdd") << endl;
  db.Print();

  cout << boolalpha << db.DeleteDate({2020, 4, 3}) << endl;
  db.Print();

  for(auto& item : db.Find({2019, 4, 3}))
    cout << item << endl;

  Date date;
  cout << boolalpha << CreateDate("2020-04-02", date) << " ";
  date.Print();
  //cout << boolalpha << bool(ss) << " " << year << endl;
  return 0;
}

int main() {
  Database db;
    
  string command;
  try{
  while (getline(cin, command)) {
    // Считайте команды с потока ввода и обработайте каждую
    stringstream ss(command);
    string cmd;
    ss >> cmd;
    if(cmd == "")
      continue;
    if(cmd == "Add"){
      string sdate;
      ss >> sdate;
      Date date;
      if(CreateDate(sdate, date)){
        string event;
        while(ss){
          ss >> event;
          db.AddEvent(date, event);
        }
      }
    }
    else if(cmd == "Print"){
      db.Print();
    }
    else if(cmd == "Find"){
      string sdate;
      ss >> sdate;
      Date date;
      if(CreateDate(sdate, date)){
        vector<string> sfind = db.Find(date);
        for(auto& item : sfind)
          cout << item << endl;
      }
    }
    else if(cmd == "Del"){
      string sdate;
      ss >> sdate;
      Date date;
      if(CreateDate(sdate, date)){
        if(ss && ss.eof()){
          int n = db.DeleteDate(date);
          cout << "Deleted " << n << " events" << endl;
        }else{
          string event;
          ss >> event;
          if(db.DeleteEvent(date, event))
            cout << "Deleted successfully" << endl;
          else
            cout << "Event not found" << endl;
        }
      }
    }
    else{
      //cout << "Unknown command: " << cmd << endl;
      throw runtime_error("Unknown command: " + cmd);
    }
  }//while (getline(cin, command))
  }catch(exception& ex){
    cout << ex.what();
  }

  return 0;
}
