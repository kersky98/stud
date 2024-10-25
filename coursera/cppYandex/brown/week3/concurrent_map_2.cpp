/*В заготовке решения задачи «Шаблон Synchronized» мы уже слегка коснулись идеи
о том, что уменьшение размера критической секции позволяет повысить скорость работы
многопоточной программы. В этой задаче мы разовьём её больше.

Давайте представим, что у нас есть map, к которому обращаются несколько потоков.
Чтобы синхронизировать доступ к нему, мы можем каждое обращение к этому map'у
защитить мьютексом (например, завернув наш map в шаблон Synchronized).
Теперь давайте представим, что у нас есть Synchronized<map<int, int>>, в котором
хранятся все ключи от 1 до 10000. Интуитивно кажется, что когда из одного потока
мы обращаемся к ключу 10, а из другого — например, к ключу 6712, то нет смысла
защищать эти обращения одним и тем же мьютексом. Это отдельные области памяти,
а внутреннюю структуру словаря мы никак не изменяем. При этом, если мы будем
обращаться к ключу 6712 одновременно из нескольких потоков, то синхронизация,
несомненно, понадобится.

Отсюда возникает идея — разбить наш словарь на нескольких подсловарей с непересекающимся
набором ключей и защитить каждый из них отдельным мьютексом. Тогда при обращении
разных потоков к разным ключам они нечасто будут попадать в один и тот же подсловарь,
а значит, смогут параллельно его обрабатывать. Эту идею вам предстоит реализовать
в этой задаче. Вам надо написать шаблон класса ConcurrentMap вот с таким интерфейсом:

static_assert в начале класса говорит, что в данной задаче предполагается, что ключами
ConcurrentMap'а могут быть только целые числа.

Конструктор класса ConcurrentMap<K, V> принимает количество подсловарей, на которые
надо разбить всё пространство ключей.

operator[] должен вести себя так же, как аналогичный оператор у map — если ключ key
присутствует в словаре, он должен возвращать объект класса Access, содержащий ссылку на
соответствующее ему значение; если же key отсутствует в словаре, в него надо добавить
пару (key, V()) и вернуть объект класса Access, содержащий ссылку на только
что добавленное значение.

Структура Access, должна вести себя так же, как и в шаблоне Synchronized, — предоставлять
ссылку на значение словаря и обеспечивать синхронизацию доступа к нему.

Метод BuildOrdinaryMap должен сливать вместе части словаря и возвращать весь словарь
целиком. При этом он должен быть потокобезопасным, то есть корректно работать,
когда другие потоки выполняют операции с ConcurrentMap.

Эта задача — продолжение задачи «ConcurrentMap» из «Красного пояса по C++».
Ниже приведено её полное условие с необходимыми изменениями. Так что если вы не проходили 
«Красный пояс», можете просто решать эту задачу с нуля. Дополнительные требования по 
сравнению с «Красным поясом по С++»:

    внутри класса надо использовать unordered-контейнер вместо std::map

    необходимо поддержать ключи произвольного типа, а не только целочисленные

    нужно добавить константные методы Has и At

    нужно сделать метод BuildOrdinaryMap константным

*/

#include <algorithm>
#include <future>
#include <memory>
#include <mutex>
#include <random>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

#include "profile.h"
#include "test_runner.h"
using namespace std;

template <typename K, typename V, typename Hash = std::hash<K>>
class ConcurrentMap {
 public:
  using MapType = unordered_map<K, V, Hash>;

  struct WriteAccess {
    unique_ptr<lock_guard<mutex>> guard;
    V& ref_to_value;
  };

  struct ReadAccess {
    unique_ptr<lock_guard<mutex>> guard;
    const V& ref_to_value;
  };

  explicit ConcurrentMap(size_t bucket_count) : bc(bucket_count) {}

  WriteAccess operator[](const K& key) {
    size_t index = hasher(key) % bc;
    unique_ptr<lock_guard<mutex>> lock = make_unique<lock_guard<mutex>>(m[index]);
    if (v[index].count(key) == 0) {
      v[index][key] = V();
    }
    return {move(lock), v[index][key]};
  }
  ReadAccess At(const K& key) const {
    size_t index = hasher(key) % bc;
    unique_ptr<lock_guard<mutex>> lock = make_unique<lock_guard<mutex>>(m[index]);
    return {move(lock), v[index].at(key)};
  }

  bool Has(const K& key) const {
    size_t index = hasher(key) % bc;
    std::lock_guard<std::mutex> lock(m[index]);
    return v[index].count(key) > 0;
  }

  MapType BuildOrdinaryMap() const {
    MapType mres;
    size_t index = 0;
    for (const auto& item : v) {
      std::lock_guard<std::mutex> lock(m[index++]);
      mres.insert(begin(item), end(item));
    }
    return mres;
  }

 private:
  Hash hasher;
  size_t bc;
  vector<MapType> v = vector<MapType>(bc);
  mutable vector<mutex> m = vector<mutex>(bc);
};

void RunConcurrentUpdates(ConcurrentMap<int, int>& cm, size_t thread_count,
                          int key_count) {
  auto kernel = [&cm, key_count](int seed) {
    vector<int> updates(key_count);
    iota(begin(updates), end(updates), -key_count / 2);
    shuffle(begin(updates), end(updates), default_random_engine(seed));

    for (int i = 0; i < 2; ++i) {
      for (auto key : updates) {
        cm[key].ref_to_value++;
      }
    }
  };

  vector<future<void>> futures;
  for (size_t i = 0; i < thread_count; ++i) {
    futures.push_back(async(kernel, i));
  }
}

void TestConcurrentUpdate() {
  const size_t thread_count = 3;
  const size_t key_count = 50000;

  ConcurrentMap<int, int> cm(thread_count);
  RunConcurrentUpdates(cm, thread_count, key_count);

  const auto result = std::as_const(cm).BuildOrdinaryMap();
  ASSERT_EQUAL(result.size(), key_count);
  for (auto& [k, v] : result) {
    AssertEqual(v, 2 * thread_count, "Key = " + to_string(k));
  }
}

void TestReadAndWrite() {
  ConcurrentMap<size_t, string> cm(5);

  auto updater = [&cm] {
    for (size_t i = 0; i < 50000; ++i) {
      cm[i].ref_to_value += 'a';
    }
  };
  auto reader = [&cm] {
    vector<string> result(50000);
    for (size_t i = 0; i < result.size(); ++i) {
      result[i] = cm[i].ref_to_value;
    }
    return result;
  };

  auto u1 = async(updater);
  auto r1 = async(reader);
  auto u2 = async(updater);
  auto r2 = async(reader);

  u1.get();
  u2.get();

  for (auto f : {&r1, &r2}) {
    auto result = f->get();
    ASSERT(all_of(result.begin(), result.end(), [](const string& s) {
      return s.empty() || s == "a" || s == "aa";
    }));
  }
}

void TestSpeedup() {
  {
    ConcurrentMap<int, int> single_lock(1);

    LOG_DURATION("Single lock");
    RunConcurrentUpdates(single_lock, 4, 50000);
  }
  {
    ConcurrentMap<int, int> many_locks(100);

    LOG_DURATION("100 locks");
    RunConcurrentUpdates(many_locks, 4, 50000);
  }
}

void TestConstAccess() {
  const unordered_map<int, string> expected = {
      {1, "one"},
      {2, "two"},
      {3, "three"},
      {31, "thirty one"},
      {127, "one hundred and twenty seven"},
      {1598, "fifteen hundred and ninety eight"}};

  const ConcurrentMap<int, string> cm = [&expected] {
    ConcurrentMap<int, string> result(3);
    for (const auto& [k, v] : expected) {
      result[k].ref_to_value = v;
    }
    return result;
  }();

  vector<future<string>> futures;
  for (int i = 0; i < 10; ++i) {
    futures.push_back(async([&cm, i] {
      try {
        return cm.At(i).ref_to_value;
      } catch (exception&) {
        return string();
      }
    }));
  }
  futures.clear();

  ASSERT_EQUAL(cm.BuildOrdinaryMap(), expected);
}

void TestStringKeys() {
  const unordered_map<string, string> expected = {
      {"one", "ONE"},
      {"two", "TWO"},
      {"three", "THREE"},
      {"thirty one", "THIRTY ONE"},
  };

  const ConcurrentMap<string, string> cm = [&expected] {
    ConcurrentMap<string, string> result(2);
    for (const auto& [k, v] : expected) {
      result[k].ref_to_value = v;
    }
    return result;
  }();

  ASSERT_EQUAL(cm.BuildOrdinaryMap(), expected);
}

struct Point {
  int x, y;
};

struct PointHash {
  size_t operator()(Point p) const {
    std::hash<int> h;
    return h(p.x) * 3571 + h(p.y);
  }
};

bool operator==(Point lhs, Point rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

void TestUserType() {
  ConcurrentMap<Point, size_t, PointHash> point_weight(5);

  vector<future<void>> futures;
  for (int i = 0; i < 1000; ++i) {
    futures.push_back(async([&point_weight, i] {
      point_weight[Point{i, i}].ref_to_value = i;
    }));
  }

  futures.clear();

  for (int i = 0; i < 1000; ++i) {
    ASSERT_EQUAL(point_weight.At(Point{i, i}).ref_to_value, i);
  }

  const auto weights = point_weight.BuildOrdinaryMap();
  for (int i = 0; i < 1000; ++i) {
    ASSERT_EQUAL(weights.at(Point{i, i}), i);
  }
}

void TestHas() {
  ConcurrentMap<int, int> cm(2);
  cm[1].ref_to_value = 100;
  cm[2].ref_to_value = 200;

  const auto& const_map = std::as_const(cm);
  ASSERT(const_map.Has(1));
  ASSERT(const_map.Has(2));
  ASSERT(!const_map.Has(3));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConcurrentUpdate);
  RUN_TEST(tr, TestReadAndWrite);
  RUN_TEST(tr, TestSpeedup);
  RUN_TEST(tr, TestConstAccess);
  RUN_TEST(tr, TestStringKeys);
  RUN_TEST(tr, TestUserType);
  RUN_TEST(tr, TestHas);
}
