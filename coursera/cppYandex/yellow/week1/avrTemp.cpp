/*Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней.
 * Найдите номера дней (в нумерации с нуля) со значением температуры выше
 * среднего арифметического за все N дней.
Гарантируется, что среднее арифметическое значений температуры является целым числом.

Формат ввода
Вводится число N, затем N целых чисел — значения температуры в 0-й, 1-й,
... (N−1)-й день. Гарантируется, что N не превышает миллиона (10^6), а значения
температуры, измеряющиеся в миллионных долях градусов по Цельсию, лежат в диапазоне
от −10^8 до 10^8. Проверять соблюдение этих ограничений не нужно: вы можете
ориентироваться на них при выборе наиболее подходящих типов для переменных.

Формат вывода
Первое число K — количество дней, значение температуры в которых выше среднего
арифметического. Затем K целых чисел — номера этих дней.
*/

#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
  long long int avrg = 0;
  vector<int> temp;
  vector<int> upTemp;
  int n;

  cin >> n;
  for(int i=0; i<n; i++){
    int t;
    cin >> t;
    temp.push_back(t);
    avrg += t;
  }
  avrg /= n;

  //std::for_each(temp.begin(), temp.end(), [upTemp, avrg](int& t){ if(t > avrg) upTemp.push_back(t); });
  for(int i=0; i<static_cast<int>(temp.size()); i++){
    if(temp[i] > avrg){
      upTemp.push_back(i);
    }
  }

  cout << upTemp.size() << endl;
  for(auto& item : upTemp)
    cout << item << " ";
  return 0;
}
