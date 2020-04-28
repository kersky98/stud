#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

/*
class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    // добавить факт изменения имени на first_name в год year
    mFirst[year] = first_name;
    firstName = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    // добавить факт изменения фамилии на last_name в год year
    mLast[year] = last_name;
    lastName = last_name;
  }
  string GetFullName(int year) {
    string message;
    //Если к данному году не случилось ни одного изменения фамилии и имени,
    //верните строку "Incognito".
    if(mFirst.begin()->first > year || mLast.begin()->first > year)
    {
      message = "Incognito";
    }//Если к данному году случилось изменение фамилии, но не было ни одного изменения имени,
    //верните "last_name with unknown first name".
    if((mLast.size() > 0 && mLast.begin()->first <= year) &&
        (mFirst.begin()->first > year || mFirst.size() == 0))
    {
      message =  (--mLast.upper_bound(year))->second + " with unknown first name";
    }//Если к данному году случилось изменение имени, но не было ни одного изменения фамилии,
    //верните "first_name with unknown last name".
    if((mFirst.size() > 0 && mFirst.begin()->first <= year) &&
        (mLast.begin()->first > year || mLast.size() == 0))
    {
      message =  (--mFirst.upper_bound(year))->second + " with unknown last name";
    }

    if(mFirst.size() > 0 && mLast.size() > 0 &&
        mFirst.begin()->first <= year && mLast.begin()->first <= year)
    {
      message = (--mFirst.upper_bound(year))->second + " " +
          (--mLast.upper_bound(year))->second;
    }
    return message;
  }
private:
  // приватные поля
  string firstName;
  string lastName;
  map<int, string> mFirst;
  map<int, string> mLast;
};
*/
void TestGetEmpty(){
  Person p;
  AssertEqual(p.GetFullName(2222), "Incognito", "Get empty0");
}

void TestGetIncognito(){
  Person p;
  p.ChangeFirstName(2223, "AAA");
  AssertEqual(p.GetFullName(2222), "Incognito", "Get Incognito1");
  p.ChangeLastName(2224, "BBB");
  AssertEqual(p.GetFullName(2222), "Incognito", "Get Incognito2");
}

void TestFirstName(){
  Person p;
  p.ChangeFirstName(2222, "AAA");
  AssertEqual(p.GetFullName(2223), "AAA with unknown last name", "TestFirsName1");
  p.ChangeFirstName(2225, "aaa");
  AssertEqual(p.GetFullName(2223), "AAA with unknown last name", "TestFirsName2");
  AssertEqual(p.GetFullName(2226), "aaa with unknown last name", "TestFirsName3");
}

void TestLastName(){
  Person p;
  p.ChangeLastName(2222, "AAA");
  AssertEqual(p.GetFullName(2223), "AAA with unknown first name", "TestLastName1");
  p.ChangeLastName(2225, "aaa");
  AssertEqual(p.GetFullName(2223), "AAA with unknown first name", "TestLastName2");
  AssertEqual(p.GetFullName(2226), "aaa with unknown first name", "TestLastName3");
}

void TestFullName(){
  Person p;
  p.ChangeFirstName(2222, "AAA");
  p.ChangeLastName(2222, "BBB");
  AssertEqual(p.GetFullName(2221), "Incognito", "TestFullName1");
  AssertEqual(p.GetFullName(2222), "AAA BBB", "TestFullName2");

  p.ChangeFirstName(2223, "aaa");
  AssertEqual(p.GetFullName(2224), "aaa BBB", "TestFullName3");
  p.ChangeLastName(2225, "bbb");
  AssertEqual(p.GetFullName(2224), "aaa BBB", "TestFullName4");
  AssertEqual(p.GetFullName(2225), "aaa bbb", "TestFullName5");
}

int main() {
  TestRunner runner;
  // добавьте сюда свои тесты
  runner.RunTest(TestGetEmpty, "TestGetEmpty");
  runner.RunTest(TestGetIncognito, "TestGetIncognito");
  runner.RunTest(TestFirstName, "TestFirsName");
  runner.RunTest(TestLastName, "TestLastName");
  runner.RunTest(TestFullName, "TestLastName");

  return 0;
}
