/*Дан вектор токенов. Напишите функцию, разбивающую токены на предложения:

Token — шаблонный тип, про который известно лишь то, что он имеет константный метод
IsEndSentencePunctuation, возвращающий true, если токен является знаком пунктуации, заканчивающим
предложение, и false в противном случае. Объекты этого типа запрещено копировать.
При наличии копирования этих объектов вы получите ошибку компиляции.

Sentence — синоним для типа vector, объявленный следующим образом:

Предложением считается последовательность токенов, заканчивающаяся подряд идущими токенами,
являющимися знаками пунктуации конца предложения. Иными словами, любое предложение должно состоять
из двух частей:

токены, для которых IsEndSentencePunctuation возвращает false (такие токены обязаны присутствовать
в предложении за исключением, возможно, первого предложения);

токены, для которых IsEndSentencePunctuation возвращает true (такие токены обязаны присутствовать
в предложении за исключением, возможно, последнего предложения).

Ограничения
Максимальное количество токенов — 10^6. Время выполнения одного вызова функции ограничено 1 секундой.
*/
#include "test_runner.h"

#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
  // Напишите реализацию функции, не копируя объекты типа Token
  vector<Sentence<Token>> vv;
  Sentence<Token> v;
  for(size_t i = 0; i < tokens.size(); i++){
    v.push_back(move(tokens[i]));
    if(i<tokens.size()-1 &&
        tokens[i].IsEndSentencePunctuation() &&
        !tokens[i+1].IsEndSentencePunctuation()){
      vv.push_back(move(v));
      v.clear();
    }
  }

  if(v.size() > 0){
    vv.push_back(move(v));
  }
  return vv;
}


struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  return 0;
}
