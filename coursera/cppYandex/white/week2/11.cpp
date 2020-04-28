/*Слова называются анаграммами друг друга, если одно из них можно получить
 * перестановкой букв в другом. Например, слово «eat» можно получить перестановкой
 * букв слова «tea», поэтому эти слова являются анаграммами друг друга. Даны пары
 * слов, проверьте для каждой из них, являются ли слова этой пары анаграммами друг друга.
Указание
Один из способов проверки того, являются ли слова анаграммами друг друга,
заключается в следующем. Для каждого слова с помощью словаря подсчитаем, сколько
раз в нём встречается каждая буква. Если для обоих слов эти словари равны
(а это проверяется с помощью обычного оператора ==), то слова являются анаграммами
друг друга, в противном случае не являются.
При этом построение такого словаря по слову удобно вынести в отдельную функцию
BuildCharCounters.
Формат ввода
Сначала дано число пар слов N, затем в N строках содержатся пары слов, которые
необходимо проверить. Гарантируется, что все слова состоят лишь из строчных латинских букв.
Формат вывода
Выведите N строк: для каждой введённой пары слов YES, если эти слова являются
анаграммами, и NO в противном случае.
*/
#include <iostream>
#include <vector>
#include <map>
using namespace std;

map<char, int> BuildCharCounters(const string& s)
{
  map<char, int> ch;
  for(auto item : s)
    ++ch[item];

  return ch;
}

void PrintCharCounters(map<char, int>& ch)
{
  cout << "Size = " << ch.size() << endl;
  for (auto item : ch)
    cout << item.first << " " << item.second << endl;
}

int main()
{
  string str = "master",
      str1 = "stream";
  map<char, int> ch;
  map<char, int> ch1;
  int q;
  vector<bool> result;

  cin >> q;
  for (int i = 0; i < q; i++)
  {
    cin >> str >> str1;
    ch = BuildCharCounters(str);
    //PrintCharCounters(ch);

    ch1 = BuildCharCounters(str1);
    //PrintCharCounters(ch1);

    result.push_back(ch == ch1);
  }

  for(auto item : result)
  {
    if(item == true)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
  return 0;
}
