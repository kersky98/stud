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
  string s;
  //cout << bool(input) << endl;
  //cout << input.is_open() << endl;
  while(getline(input, s))
  {
    //input >> s;
    cout << s << endl;
  }
  input.close();
  return 0;
}
