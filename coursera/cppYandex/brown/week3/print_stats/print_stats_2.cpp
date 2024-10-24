#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>

using namespace std;

template <typename Iterator>
class IteratorRange {
 public:
  IteratorRange(Iterator begin, Iterator end) : first(begin), last(end) {}

  Iterator begin() const { return first; }

  Iterator end() const { return last; }

 private:
  Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top) {
  return IteratorRange{v.begin(), next(v.begin(), min(top, v.size()))};
}

struct Person {
  string name;
  int age, income;
  bool is_male;
};

vector<Person> ReadPeople(istream& input) {
  int count;
  input >> count;

  vector<Person> result(count);
  for (Person& p : result) {
    char gender;
    input >> p.name >> p.age >> p.income >> gender;
    p.is_male = gender == 'M';
  }

  return result;
}

int main() {
  vector<Person> people = ReadPeople(cin);

  vector<Person> people_sorted_by_name(people);
  sort(begin(people_sorted_by_name), end(people_sorted_by_name),
       [](const Person& lhs, const Person& rhs) { return lhs.age < rhs.age; });

  vector<Person> people_sorted_by_income(people);
  sort(people_sorted_by_income.begin(), people_sorted_by_income.end(),
       [](const Person& lhs, const Person& rhs) {
         return lhs.income > rhs.income;
       });

  vector<Person> people_sorted_by_gender(people);
  vector<Person>::iterator it_mf =
      partition(begin(people_sorted_by_gender), end(people_sorted_by_gender),
                [](Person& p) { return p.is_male; });
  IteratorRange mrange{begin(people_sorted_by_gender), it_mf};
  IteratorRange wrange{it_mf, end(people_sorted_by_gender)};

  uint64_t mcount_max = 0;
  map<string, uint64_t> mname2count;
  map<uint64_t, set<string>> count2mname;
  for (const Person& item : mrange) {
    mname2count[item.name]++;
  }

  for (auto [key, value] : mname2count) {
    count2mname[value].insert(key);
    mcount_max = max(mcount_max, value);
  }

  uint64_t wcount_max = 0;
  map<string, uint64_t> wname2count;
  map<uint64_t, set<string>> count2wname;
  for (const Person& item : wrange) {
    wname2count[item.name]++;
  }

  for (auto [key, value] : wname2count) {
    count2wname[value].insert(key);
    wcount_max = max(wcount_max, value);
  }

  for (string command; cin >> command;) {
    if (command == "AGE") {
      int adult_age;
      cin >> adult_age;

      auto adult_begin = lower_bound(
          begin(people_sorted_by_name), end(people_sorted_by_name), adult_age,
          [](const Person& lhs, int age) { return lhs.age < age; });

      cout << "There are "
           << std::distance(adult_begin, end(people_sorted_by_name))
           << " adult people for maturity age " << adult_age << '\n';
    } else if (command == "WEALTHY") {
      int count;
      cin >> count;

      auto head = Head(people_sorted_by_income, count);

      uint64_t total_income =
          accumulate(head.begin(), head.end(), 0ULL,
                     [](uint64_t cur, Person& p) { return cur += p.income; });
      cout << "Top-" << count << " people have total income " << total_income
           << '\n';
    } else if (command == "POPULAR_NAME") {
      char gender;
      cin >> gender;

      const string* most_popular_name;
      if (gender == 'M') {
        if (mrange.begin() == mrange.end()) {
          cout << "No people of gender " << gender << '\n'; continue;
        } else {
          most_popular_name = &(*count2mname[mcount_max].begin());
        }
      } else {
        if (wrange.begin() == wrange.end()) {
          cout << "No people of gender " << gender << '\n'; continue;
        } else {
          most_popular_name = &(*count2wname[wcount_max].begin());
        }
      }

      cout << "Most popular name among people of gender " << gender << " is "
           << *most_popular_name << '\n';
    }
  }
}
