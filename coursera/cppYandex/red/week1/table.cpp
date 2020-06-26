/*Вам надо написать шаблонный класс Table для электронной таблицы. Для простоты
 * будем считать, что все ячейки таблицы имеют один и тот же тип данных T.
 * Таблица должна уметь менять свой размер по требованию пользователя. Вновь
 * созданные ячейки должны заполняться значениями по умолчанию типа T.

Требования к классу такие:

Класс должен называться Table.
У класса должен быть шаблонный параметр T - тип элемента в ячейке.
У класса должен быть конструктор, получающий на входе два числа типа size_t,
- количество строк и столбцов соответственно.
У класса должны быть константная и неконстантная версии оператора [],
возвращающего нечто такое, к чему снова можно было бы применить оператор [].
То есть, должны работать конструкции вида cout << table[i][j];и table[i][j] = value;.
Проверять корректность индексов при этом не нужно.
У класса должна быть функция Resize, получающая на вход два параметра типа size_t и
меняющая размер таблицы. Старые данные, умещающиеся в новый размер, должны при этом сохраниться.
У класса должен быть константный метод Size, возвращающий pair<size_t, size_t> размер
таблицы (в том же порядке, в котором эти аргументы передавались в конструктор).
 *
 */

#include "test_runner.h"
#include <algorithm>
#include <utility>
using namespace std;

// Реализуйте здесь шаблонный класс Table
template <typename T>
class Table{
public:
  Table(const size_t rows, const size_t cols):t(rows, vector<T>(cols)){
    m = rows;
    n = cols;
    T fillval;
    for(auto& item: t)
      fill(begin(item), end(item), fillval);
  }
  void Print()const {
    cout << t << endl;
  }
  const vector<T>& operator[](const size_t index) const{
    return t[index];
  }
  vector<T>& operator[](const size_t index){
    return t[index];
  }
  pair<size_t, size_t> Size()const{
    return make_pair(m, n);
  }
  void Resize(const size_t rows, const size_t cols){
    t.resize(rows);
    for(auto& item: t){
      item.resize(cols);
    }
    m = rows;
    n = cols;
  }
private:
  size_t m, n;
  vector<vector<T>> t;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  /*Table<int>t(3, 3);
  t.Print();
  //cout << t[1][1] << endl;
  //t[1][1] = 0;
  //cout << t[1][1] << endl;
  cout << t.Size().first << ", " << t.Size().second << endl;
  t.Resize(2, 2);
  t.Print();
  //cout << t[1][1] << endl;
  //t[1][1] = 0;
  //cout << t[1][1] << endl;
  cout << t.Size().first << ", " << t.Size().second << endl;
  */

  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
