#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};

// Реализуйте этот класс
class Database {
public:
  bool Put(const Record& record){
    pair<map<string, Record>::iterator, bool> result = m.insert(make_pair(record.id, record));
    if(result.second){
      t2i.insert(make_pair(record.timestamp, result.first));
      k2i.insert(make_pair(record.karma, result.first));
      u2i.insert(make_pair(record.user, result.first));
    }
    return result.second;
  }

  const Record* GetById(const string& id) const{
    map<string, Record>::const_iterator iter = m.find(id);
    if(iter == m.end()){
      return nullptr;
    }else{
      return &(iter->second);
    }
  }

  bool Erase(const string& id){
    map<string, Record>::iterator iter = m.find(id);
    if(iter == m.end()){
      return false;
    }else{
      t2i.erase(t2i.find(iter->second.timestamp));
      k2i.erase(k2i.find(iter->second.karma));
      u2i.erase(u2i.find(iter->second.user));
      m.erase(iter);
      return true;
    }
  }

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const{
    auto it_begin = t2i.lower_bound(low);
    auto it_end = t2i.upper_bound(high);
    while(it_begin != it_end){
      if(false == callback(it_begin->second->second)){
        return;
      }
      it_begin++;
    }
  }

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const{
    auto it_begin = k2i.lower_bound(low);
    auto it_end = k2i.upper_bound(high);
    while(it_begin != it_end){
      if(false == callback(it_begin->second->second)){
        return;
      }
      it_begin++;
    }
  }

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const{
    auto it_begin = u2i.lower_bound(user);
    auto it_end = u2i.upper_bound(user);
    while(it_begin != it_end){
      if(false == callback(it_begin->second->second)){
        return;
      }
      it_begin++;
    }
  }
private:
  map<string, Record> m;
  multimap<int, map<string, Record>::iterator> t2i;
  multimap<int, map<string, Record>::iterator> k2i;
  multimap<string, map<string, Record>::iterator> u2i;
};

void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
  return 0;
}
