/*В первой строке файла input.txt записаны два числа N и M. Далее в файле находится
 * таблица из N строк и M столбцов, представленная в формате CSV (comma-separated values).
 * Такой формат часто используется для текстового представления таблиц с данными: в
 * файле несколько строк, значения из разных ячеек внутри строки отделены друг от друга
 * запятыми. Ваша задача — вывести данные на экран в виде таблицы. Формат таблицы:
1) размер ячейки равен 10,
2) соседние ячейки отделены друг от друга пробелом,
3) последняя ячейка в строке НЕ оканчивается пробелом,
4) последняя строка НЕ оканчивается символом перевода строки. Гарантируется, что в
таблице будет ровно N строк и M столбцов, значение каждой из ячеек — целое число.
Пример ввода
2 3
1,2,3
4,5,6
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
  ifstream input("input.txt");
  int m, n;
  //cout << fixed;
  //cout.precision(3);
  //cout.width(3);
  input >> m; input.ignore(1);
  input >> n; input.ignore(1);

  //cout << m << " " << n << endl;
  //cout << fixed;
  for(int i=0; i<m; i++)
  {
    string str;
    getline(input, str);
    stringstream s(str);
    for(int j=0; j<n; j++)
    {
      string word;
      getline(s, word, ',');
      cout.width(10);
      //cout.fill('.');
      //cout.precision(3);
      cout << word << right;
      if(j != n-1)
        cout << " ";
    }
    if(i != m-1)
      cout << endl;
  }

  input.close();
  return 0;
}
