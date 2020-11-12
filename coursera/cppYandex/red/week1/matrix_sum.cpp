/*В лекциях мы рассмотрели пример, в котором сначала выполнялась генерация квадратной
матрицы, а затем находилась сумма элементов в ней. При этом нам удалось ускорить
генерацию матрицы за счёт применения многопоточности. В этой задаче вам нужно сделать
то же самое для суммирования элементов матрицы.

Вам нужно написать функцию int64_t CalculateMatrixSum(const vector<vector<int>>& matrix),
которая получает на вход квадратную матрицу и возвращает сумму элементов в ней.

Ваша реализация будет тестироваться следующим образом:

на вход вашей функции будут подаваться квадратные матрицы размером до 9000
(в данном случае размер матрицы — это количество строк в ней);
для одной и той же матрицы функция CalculateMatrixSum будет запускаться несколько раз;
среднее время работы одного вызова в нашей тестирующей системе не должно превышать 15 мс;
*/
#include "test_runner.h"
#include <vector>
#include <future>
#include <numeric>
#include <algorithm>
using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
    , size_(distance(first, last))
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

  size_t size() const {
    return size_;
  }

private:
  Iterator first, last;
  size_t size_;
};

template <typename Iterator>
class Paginator {
private:
  vector<IteratorRange<Iterator>> pages;

public:
  Paginator(Iterator begin, Iterator end, size_t page_size) {
    for (size_t left = distance(begin, end); left > 0; ) {
      size_t current_page_size = min(page_size, left);
      Iterator current_page_end = next(begin, current_page_size);
      pages.push_back({begin, current_page_end});

      left -= current_page_size;
      begin = current_page_end;
    }
  }

  auto begin() const {
    return pages.begin();
  }

  auto end() const {
    return pages.end();
  }

  size_t size() const {
    return pages.size();
  }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(begin(c), end(c), page_size);
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  // Реализуйте эту функцию
  vector<future<int64_t>> futures;
  int64_t res = 0;
  for(auto page: Paginate(matrix, 2000)){
    futures.push_back(
        async([page]{
      int64_t res1 = 0;
      for(const auto page1 : page){
        res1 += accumulate(begin(page1), end(page1), 0L);
      }
      return res1;
    })
    );
  }
  for(auto& item : futures){
    res += item.get();
  }
  return res;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

void TestCalculateMatrixSum9000() {
  vector<vector<int>> matrix(9000);
  for(auto& item: matrix){
    item.resize(9000);
    vector<int> line(9000);
    fill(begin(line), end(line), 0);
    iota(begin(line), begin(line)+5, 1);
    move(begin(line), end(line), begin(item));
  }
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  //RUN_TEST(tr, TestCalculateMatrixSum);
  RUN_TEST(tr, TestCalculateMatrixSum9000);
}
