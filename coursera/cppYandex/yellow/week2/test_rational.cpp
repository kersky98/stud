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

#if 0
class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
      if(denominator == 0)
        throw invalid_argument("Invalid argument");
      if(numerator != 0)
      {
        int a = max(abs(numerator), abs(denominator));
        int b = min(abs(numerator), abs(denominator));
        int nod;
        while(a % b != 0)
        {
          int tmp = b;
          b = a % b;
          a = tmp;
        }
        nod = b;
        //cout << nod << endl;
        p = numerator/nod;
        q = denominator/nod;
        if (q < 0){
          p = -p;
          q = -q;
        }
      }else
      {
        p = 0;
        q = 1;
      }
    }

    int Numerator() const {
        return p;
    }

    int Denominator() const {
        return q;
    }

private:
    int p, q;
};
#endif

void TestEmpty(){
  Rational r;
  AssertEqual(r.Numerator(), 0, "Numerator == 0");
  AssertEqual(r.Denominator(), 1, "Denoninator == 1");
}

void TestNumerator0(){
  Rational r(0, 23);
  AssertEqual(r.Numerator(), 0, "Numerator == 0");
  AssertEqual(r.Denominator(), 1, "Denoninator == 1");
}

void TestDenominator0(){
  try{
    Rational r(1, 0);
  }catch(invalid_argument &arg){
    string s = arg.what();
    AssertEqual(s, "Invalid argument", "TestDenominator == 0");
  }
}

void TestRational(){
  Rational r(1, 2);
  AssertEqual(r.Numerator(), 1, "Numerator == 1");
  AssertEqual(r.Denominator(), 2, "Denoninator == 2");
  Rational r1(2, 4);
  AssertEqual(r1.Numerator(), 1, "Numerator == 1");
  AssertEqual(r1.Denominator(), 2, "Denoninator == 2");
  Rational r2(-2, 4);
  AssertEqual(r2.Numerator(), -1, "Numerator == -1");
  AssertEqual(r2.Denominator(), 2, "Denoninator == 2");
  Rational r3(3, -9);
  AssertEqual(r3.Numerator(), -1, "Numerator == -1");
  AssertEqual(r3.Denominator(), 3, "Denoninator == 3");
}

int main() {
  TestRunner runner;
  // добавьте сюда свои тесты
  runner.RunTest(TestEmpty, "TestEmpty");
  runner.RunTest(TestNumerator0, "TestNumerator0");
  runner.RunTest(TestDenominator0, "TestDenominator0");
  runner.RunTest(TestRational, "TestRational");

  return 0;
}
