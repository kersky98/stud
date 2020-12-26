/*Крупная IT-компания Янгл проводит исследование упоминаемости своего бренда в блогах
и социальных сетях. Аналитики компании уже выгрузили интересующие их публикации и
сформировали набор ключевых слов. Их интересует, сколько раз каждое ключевое слово
входит в набор публикаций.

Помогите им это сделать — напишите функцию
Stats ExploreKeyWords(const set<string>& key_words, istream& input). Её параметры:

key_words — множество ключевых слов
input — входной поток, содержащий исследуемые публикации в блогах и соц. сетях,
одна строка — одна публикация.

Функция ExploreKeyWords должна возвращать структуру Stats, в которой хранится, сколько
раз каждое слово из key_words суммарно встретилось в потоке input:

При подсчёте вхождения ключевых слов в текст нужно учитывать только вхождения в виде
отдельных слов. Слова друг от друга отделяются одним или несколькими пробелами.
В качестве примера допустим, что key_words = {"yangle", "rocks", "sucks", "all"} и у
нас есть публикация из соц. сети Switter: "Goondex really sucks, but yangle rocks ! Use yangle".
Слово «yangle» входит в неё 2 раза, «rocks» — один раз, а слова «all» и «sucks» — ни разу.
Слово «sucks» не входит ни разу, потому что в данном примере оно является префиксом
слова «sucks,» (по условию, слова друг от друга отделяются только пробелами).
Несмотря на то, что слово «all» является частью слова «really», его вхождение тоже
нельзя засчитывать, так как это не отдельное слово.

Чтобы уложиться в Time Limit, подумайте, можно ли эту задачу распараллелить.
Замечание

До этого в лекциях мы показывали, как использовать функцию async для асинхронного запуска
лямбда-функций без параметров. Однако её можно использовать и для запуска функций, у которых
есть параметры. Например,

Как видите, чтобы передать параметры в функцию, запускаемую асинхронно, их надо указать в
качестве параметров функции async после самой функции. Важно отметить, что при таком вызове
будут созданы копии фактических параметров (т.е. в нашем примере выше строки a и b будут скопированы).
Это не всегда желательно. Например, если у нас есть константный объект, который
потоки только читают, у нас нет необходимости создавать его копию, и можно передать
его по ссылке. Для этого надо воспользоваться функцией ref из заголовочного файла <functional>.
*/

#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <algorithm>
#include <sstream>
#include <future>
#include <functional>

using namespace std;

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other)
  {
    for(const auto& item : other.word_frequences){
      word_frequences[item.first] += item.second;
    }

    /*using WordFrequences = std::map<std::string, int>;
    for (const WordFrequences::value_type& value : other.word_frequences) {
      std::pair<WordFrequences::iterator, bool> v = word_frequences.emplace(value);
      if (! v.second) {
        v.first->second += value.second;
      }
    }*/
  }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
  Stats s;
  vector<string_view> v;

  auto it1 = begin(line);
  auto it2 = begin(line);
  while(it2 != end(line)){
//    string_view sv(&(*it1), (it2 - it1));
    it2 = find(it1, end(line), ' ');
    v.emplace_back(&(*it1), (it2 - it1));
    it1 = next(it2);
  }
  sort(begin(v), end(v));
/*  for(const auto& item : v){
    cout << item << endl;
  }
  cout << endl;*/

  for(const auto& item : key_words){
    //auto it = find(begin(v), end(v), item);
    //auto it = lower_bound(begin(v), end(v), item);
    auto its = equal_range(begin(v), end(v), item);
    while(its.first != its.second){
      s.word_frequences[item]++;
      //it = find(next(it), end(v), item);
      its.first++;
    }
  }
  return s;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWordsSingleThread1(
  const set<string>& key_words, const string& input
) {
  Stats result;
  result = ExploreLine(key_words, input);
  return result;
}

Stats ExploreKeyWordsMultiThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  vector<stringstream> v;
  stringstream s;
  int count = 0;
  for (string line; getline(input, line); ) {
    s << line << "\n";
    if(count > 20'000){
      v.push_back(move(s));
      count = 0;
      s.clear();
    }
    count++;
  }
  v.push_back(move(s));
  count = 0;
  s.clear();
  vector<future<Stats>> f;
  for(auto& item : v){
    //cout << item.str() << endl;
    //result += ExploreKeyWordsSingleThread(ref(key_words), ref(item));
    //result += ExploreLine(key_words, item.str());
    //result += async(ExploreKeyWordsSingleThread, ref(key_words), ref(item)).get();
    f.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(item)));
  }

  for(auto& item : f){
      result += item.get();
    }

  return result;
}

Stats ExploreKeyWordsMultiThread1(
  const set<string>& key_words, istream& input
) {
  Stats result;
  vector<string> v;
  string s;
  int count = 0;
  for (string line; getline(input, line); ) {
    s += line + " ";
    if(count > 100'000){
      v.push_back(move(s));
      count = 0;
      s.clear();
    }
    count++;
  }
  v.push_back(move(s));
  count = 0;
  s.clear();
  vector<future<Stats>> f;
  for(auto& item : v){
    //cout << item.str() << endl;
    //result += ExploreKeyWordsSingleThread(ref(key_words), ref(item));
    //result += ExploreLine(key_words, item.str());
    //result += async(ExploreKeyWordsSingleThread, ref(key_words), ref(item)).get();
    f.push_back(async(ExploreLine, ref(key_words), ref(item)));
  }

  for(auto& item : f){
      result += item.get();
    }

  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  // Реализуйте эту функцию
  return ExploreKeyWordsMultiThread1(key_words, input);
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}
