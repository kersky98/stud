/*Рассмотрим упрощённый текстовый редактор, поддерживающий следующий набор команд:

Перемещение курсора влево (Left) и вправо (Right) на одну позицию.
Ввод символа в текущую позицию курсора (Insert).
Копирование фрагмента текста, начинающегося в текущей позиции курсора, в буфер обмена (Copy).
Вырезание фрагмента текста аналогично копированию с последующим удалением скопированных
символов из текста (Cut).
Вставка содержимого буфера обмена в текущую позицию курсора (Paste).

Эти команды действительно поддерживаются практически любым текстовым редактором.
Также для команд действуют стандартные правила, определяющие их эффект:

Если редактор содержит текст длиной n символов, то курсор может находиться в одной
из (n + 1) возможных позиций. Например, обозначим курсор вертикальной чертой |
(это обозначение мы будем использовать в дальнейшем), тогда в тексте abc курсор может
располагаться в 4 позициях: |abc, a|bc, ab|c, abc|. Поэтому команда Left не имеет эффекта,
когда курсор расположен в начале текста, а Right не имеет эффекта, когда курсор находится
в конце. В частности, ни Left, ни Right не имеют эффекта, когда редактор не содержит текста.
Введённый символ располагается в позиции курсора, сдвигая курсор и весь текст справа от него
на одну позицию вправо. Аналогично, при вставке фрагмента длиной n курсор и текст справа от
него смещаются на n позиций вправо. В таблице ниже приведены примеры, демонстрирующие данное правило.

До вставки  Вводимый символ/вставляемый фрагмент  После вставки
| a a|
ab| c abc|
|bc a a|bc
|world  hello_  hello_|world
hello_| world hello_world|
123|78  456 123456|78

Буфер обмена изначально пуст. Вставка пустого фрагмента не имеет эффекта. Содержимое буфера
не сбрасывается после вставки, а остается неизменным до следующей команды Copy или Cut.
Копирование или вырезание фрагмента нулевой длины не оказывает влияния на текст, но опустошает
буфер обмена. Курсор не смещается ни при копировании, ни при вырезании текста. Например,
после вырезания из текста ab|cdef фрагмента из трёх символов, получим текст ab|f.

Вам предстоит реализовать «ядро» текстового редактора, поддерживающего все описанные операции,
в виде класса Editor, имеющего следующий интерфейс:

Как можно заметить, каждой описанной команде сопоставлен метод класса Editor. Также введён метод
GetText(), позволяющий получить текущее содержимое редактора в виде строки. В комментариях к
методам Cut(size_t tokens) и Copy(size_t tokens) указано, что в буфер обмена попадает фрагмент
длиной не более tokens символов — это означает, что, если справа от курсора располагается менее,
чем tokens символов, методы Cut() и Copy() должны вырезать/скопировать все символы справа.

Ограничения

Реализация класса Editor должна обрабатывать 10^6 запросов не более чем за 1 секунду.
При этом гарантируется, что:

длина текста никогда не превышает 10^6 символов;
методы Copy() и Cut() суммарно копируют/вырезают не более 10^6 символов;
метод GetText() вызывается один раз в каждом из тестов.*/

#include <string>
#include <list>
#include <algorithm>
#include "test_runner.h"
using namespace std;

class Editor {
 public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor():pos(end(l)){

  }
  void Left(){
    if(pos != begin(l)){
      pos--;
    }
  }
  void Right(){
    if(pos != end(l)){
      pos++;
    }
  }
  void Insert(char token){
    l.insert(pos, token);
  }
  void Cut(size_t tokens = 1){
    buf.clear();
    buf = list<char>(tokens);
    list<char>::iterator it = Rewind(tokens);
    copy(pos, it, begin(buf));
    pos = l.erase(pos, it);
  }
  void Copy(size_t tokens = 1){
    buf.clear();
    buf = list<char>(tokens);
    list<char>::iterator it = Rewind(tokens);
    copy(pos, it, begin(buf));
  }
  void Paste(){
    list<char>::iterator it1 =
        l.insert(pos, begin(buf), end(buf));
  }
  string GetText() const{
    return string(begin(l), end(l));
  }
  list<char>::iterator Rewind(size_t tokens){
    list<char>::iterator it = pos;
    while(tokens-- > 0 && it != end(l)){
      it++;
    }
    return it;
  }
 private:
  list<char>::iterator pos;
  list<char> l;
  list<char> buf;
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    //cout << editor.GetText() << endl;
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }

    editor.Cut(first_part_len);
    //cout << editor.GetText() << endl;
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }

    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    //cout << editor.GetText() << endl;
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  //TestEditing();
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}
