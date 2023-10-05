/*Требования:
В любой момент времени в вашей хеш-таблице должно быть ровно num_buckets корзин.
Рехеширование выполнять не нужно.
Метод Add не должен менять содержимое таблицы, если элемент, равный данному, уже есть в таблице.
Метод Has должен возвращать true тогда и только тогда, когда элемент, равный данному, есть в таблице.
Метод Erase должен стирать элемент, равный данному, из таблицы, если он там есть,
в противном случае он не должен менять содержимое таблицы.
Метод GetBucket должен возвращать ссылку на бакет, который содержал бы данный элемент,
вне зависимости от того, есть он в таблице или нет.
*/
#include "test_runner.h"

#include <forward_list>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

template <typename Type, typename Hasher>
class HashSet {
public:
  using BucketList = forward_list<Type>;
  size_t buckets_;
  Hasher hasher_;
  vector<BucketList> v;

public:
  explicit HashSet(
      size_t num_buckets,
      const Hasher& hasher = {}
  ):buckets_(num_buckets), hasher_(hasher), v(num_buckets){
  }

  void Add(const Type& value){
    if(!Has(value)){
      size_t index = hasher_(value) % buckets_;
      v[index].push_front(value);
    }
  }
  bool Has(const Type& value) const{
    size_t index = hasher_(value) % buckets_;
    return find(v[index].begin(), v[index].end(), value) != v[index].end();
  }
  void Erase(const Type& value){
    size_t index = hasher_(value) % buckets_;
    v[index].remove(value);
  }
  const BucketList& GetBucket(const Type& value) const{
    size_t index = hasher_(value) % buckets_;
    return v[index];
  }
};

struct IntHasher {
  size_t operator()(int value) const {
    // Это реальная хеш-функция из libc++, libstdc++.
    // Чтобы она работала хорошо, std::unordered_map
    // использует простые числа для числа бакетов
    return value;
  }
};

struct TestValue {
  int value;

  bool operator==(TestValue other) const {
    return value / 2 == other.value / 2;
  }
};

struct TestValueHasher {
  size_t operator()(TestValue value) const {
    return value.value / 2;
  }
};

void TestSmoke() {
  HashSet<int, IntHasher> hash_set(2);
  hash_set.Add(3);
  hash_set.Add(4);

  ASSERT(hash_set.Has(3));
  ASSERT(hash_set.Has(4));
  ASSERT(!hash_set.Has(5));

  hash_set.Erase(3);

  ASSERT(!hash_set.Has(3));
  ASSERT(hash_set.Has(4));
  ASSERT(!hash_set.Has(5));

  hash_set.Add(3);
  hash_set.Add(5);

  ASSERT(hash_set.Has(3));
  ASSERT(hash_set.Has(4));
  ASSERT(hash_set.Has(5));
}

void TestEmpty() {
  HashSet<int, IntHasher> hash_set(10);
  for (int value = 0; value < 10000; ++value) {
    ASSERT(!hash_set.Has(value));
  }
}

void TestIdempotency() {
  HashSet<int, IntHasher> hash_set(10);
  hash_set.Add(5);
  ASSERT(hash_set.Has(5));
  hash_set.Add(5);
  ASSERT(hash_set.Has(5));
  hash_set.Erase(5);
  ASSERT(!hash_set.Has(5));
  hash_set.Erase(5);
  ASSERT(!hash_set.Has(5));
}

void TestEquivalence() {
  HashSet<TestValue, TestValueHasher> hash_set(10);
  hash_set.Add(TestValue{2});
  hash_set.Add(TestValue{3});

  ASSERT(hash_set.Has(TestValue{2}));
  ASSERT(hash_set.Has(TestValue{3}));

  const auto& bucket = hash_set.GetBucket(TestValue{2});
  const auto& three_bucket = hash_set.GetBucket(TestValue{3});
  ASSERT_EQUAL(&bucket, &three_bucket);

  ASSERT_EQUAL(1, distance(begin(bucket), end(bucket)));
  ASSERT_EQUAL(2, bucket.front().value);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSmoke);
  RUN_TEST(tr, TestEmpty);
  RUN_TEST(tr, TestIdempotency);
  RUN_TEST(tr, TestEquivalence);
  return 0;
}
