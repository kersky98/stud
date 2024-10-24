#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
//#include "mySqrt.cpp"

using namespace std;

vector<double> mySqrt(double a, double b, double c);

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

int GetDistinctRealRootCount(double a, double b, double c) {
  // Вы можете вставлять сюда различные реализации функции,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
  if (a != 0)
    {
      double d = b*b - 4*a*c;
      if (d > 0)
      {
        return 2;
      }else if(d == 0)
      {
        return 1;
      }else if (d < 0)
      {
        return 0;
      }
    }else if(b != 0)
    {
      return 1;
    }

  return 0;
}

void Test0() {
    AssertEqual(GetDistinctRealRootCount(10, 2, 1), 0, "(10, 2, 1)");
    AssertEqual(GetDistinctRealRootCount(10, 2, 2), 0, "(10, 2, 2)");
    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "(0, 0, 1)");
}

void Test1() {
    AssertEqual(GetDistinctRealRootCount(1, 2, 1), 1, "(1, 2, 1)");
    AssertEqual(GetDistinctRealRootCount(2, 4, 2), 1, "(2, 4, 2)");
    AssertEqual(GetDistinctRealRootCount(0, 2, 0), 1, "(0, 2, 0)");
}

void Test2() {
    AssertEqual(GetDistinctRealRootCount(1, -4, 1), 2, "(1, -2, 1)");
}

int main() {
  TestRunner runner;
  // добавьте сюда свои тесты
  runner.RunTest(Test0, "Test0");
  runner.RunTest(Test1, "Test1");
  runner.RunTest(Test2, "Test2");


  //vector<double> v = mySqrt(1, -2, -3);
  //cout << v;

  return 0;
}
