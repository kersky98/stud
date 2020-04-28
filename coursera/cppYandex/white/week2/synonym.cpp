/*Два слова называются синонимами друг друга, если они имеют похожие значения.
Реализуйте следующие операции над словарём синонимов:
ADD word1 word2 — добавить в словарь пару синонимов (word1, word2).
COUNT word — узнать количество синонимов слова word.
CHECK word1 word2 — проверить, являются ли слова word1 и word2 синонимами.
Слова word1 и word2 считаются синонимами, если среди запросов ADD был хотя бы один
запрос ADD word1 word2 или ADD word2 word1.

Замечание
Для упрощения, будем считать, что синонимы не обладают транзитивностью, то есть,
если A - синоним B, а B - синоним C, то из этого НЕ следует, что A - синоним C.

Формат ввода
Сначала вводится количество запросов Q, затем Q строк с описаниями запросов.
Гарантируется, что в каждом запросе CHECK и ADD слова word1 и word2 различны.
Все слова состоят лишь из латинских букв, цифр и символов подчёркивания.

Формат вывода
Для каждого запроса в соответствующей строке выведите ответ на него:
В ответ на запрос COUNT word выведите единственное целое число — количество синонимов
слова word.
В ответ на запрос CHECK word1 word2 выведите строку YES, если word1 и word2 являются
синонимами, и NO в противном случае.
*/
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main1()
{
  map<string, int> m = {{"one", 1}, {"one", 2}};

  cout << m.count("one") << endl;
  return 0;
}

int main()
{
  int q;
  cin >> q;
  map<string, set<string>> m1;
  map<string, set<string>> m2;
  vector<string> messages;

  auto start= steady_clock::now();

  for(int i=0; i<q; i++)
  {
    string command;
    cin >> command;
    if(command == "ADD")
    {
      string word1, word2;
      cin >> word1 >> word2;
      m1[word1].insert(word2);
      m2[word2].insert(word1);
    }
    else if(command == "COUNT")
    {
      string word;
      cin >> word;
      set<string> tmp = m1[word];
      tmp.insert(m2[word].begin(), m2[word].end());
      int count = tmp.size();
      //messages.push_back(std::to_string(count));
      cout << std::to_string(count) << endl;
    }
    else if(command == "CHECK")
    {
      string word1, word2;
      cin >> word1 >> word2;
      int count = m1[word1].count(word2) + m2[word1].count(word2);
      if(count > 0)
        //messages.push_back("YES");
        cout << "YES" << endl;
      else
        //messages.push_back("NO");
        cout << "NO" << endl;
    }
  }

  //for(const string& s: messages)
    //cout << s << endl;

  auto finish= steady_clock::now();
  //cout<< "Time "<< duration_cast<microseconds>(finish- start).count()<< " us"<< endl;
  return 0;
}
