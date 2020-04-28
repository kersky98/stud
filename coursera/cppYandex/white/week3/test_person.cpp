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

void TestGetEmpty(){
  //Person p;
  AssertEqual(p.GetFullName(2222), "", "Get empty0");
}

void TestGetIncognito(){
  //Person p;
  p.ChangeFirstName(2223, "AAA");
  AssertEqual(p.GetFullName(2222), "Incognito", "Get Incognito1");
  p.ChangeLastName(2224, "BBB");
  AssertEqual(p.GetFullName(2222), "Incognito", "Get Incognito2");
}

void TestFirstName(){
  //Person p;
  p.ChangeFirstName(2222, "AAA");
  AssertEqual(p.GetFullName(2223), "AAA with unknown last name", "TestFirsName1");
  p.ChangeFirstName(2225, "aaa");
  AssertEqual(p.GetFullName(2223), "AAA with unknown last name", "TestFirsName2");
  AssertEqual(p.GetFullName(2226), "aaa with unknown last name", "TestFirsName3");
}

void TestLastName(){
  //Person p;
  p.ChangeLastName(2222, "AAA");
  AssertEqual(p.GetFullName(2223), "AAA with unknown first name", "TestLastName1");
  p.ChangeLastName(2225, "aaa");
  AssertEqual(p.GetFullName(2223), "AAA with unknown first name", "TestLastName2");
  AssertEqual(p.GetFullName(2226), "aaa with unknown first name", "TestLastName3");
}

void TestFullName(){
  //Person p;
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
  runner.RunTest(TestFullName, "TestFullName");

  return 0;
}
