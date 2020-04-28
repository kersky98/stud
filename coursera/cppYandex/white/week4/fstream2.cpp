/*Часть 1. Ваша программа должна считать содержимое файла input.txt и напечатать его на
 * экран без изменений. Гарантируется, что содержимое файла input.txt заканчивается
 * переводом строки.
 * Часть 2. Снова считайте все содержимое файла input.txt, но на этот раз выведите его
 * в файл output.txt . Точно так же гарантируется, что содержимое файла input.txt
 * заканчивается переводом строки.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main()
{
  ifstream input("input.txt");
  ofstream output("output.txt");
  string s;
  while(getline(input, s))
  {
    output << s << endl;
  }
  input.close();
  output.close();
  return 0;
}
