/*
Требования:
Worker
    метод SetNext должен принимать во владение следующий обработчик из цепочки
    метод PassOn должен вызывать метод Process следующего обработчика, если он
был установлен

Reader
    конструктор должен принимать входной поток (istream&), из которого нужно
читать сообщения метод Run должен читать из входного потока все e-mail'ы и
передавать дальше каждый из них. Один e-mail представляется во входном потоке
полями from, to, body, каждое из которых находится на своей строке.

Filter
    конструктор должен принимать предикат типа function<bool(const Email&)>
    метод Process должен передавать дальше только сообщения, удовлетворяющие
    предикату

Copier
    конструктор должен принимать строку-адрес получателя
    метод Process должен передавать сообщение как исходному получателю, так и
    указанному в конструкторе. В случае, если они совпадают, дублировать
сообщение не нужно

Sender
    конструктор должен принимать поток для записи сообщений
    метод Process должен записывать сообщения в поток в том же формате, в
котором они были прочитаны

Все обработчики должны передавать сообщения дальше, если обратное не требуется
явно.

PipelineBuilder

    Конструктор должен инициализировать цепочку обработчиков обработчиком Reader
с переданным потоком.

    Методы с типом возврата PipelineBuilder& должны возвращать ссылку на
экземпляр класса, для которого они были вызваны, а также добавлять в конец
цепочки новый обработчик, соответствующий вызванному методу (Filter для метода
FilterBy, Sender для метода Send и т.д.).

    Метод Build должен возвращать готовую цепочку обработчиков; подразумевается,
что после его завершения экземпляр PipelineBuilder больше использоваться не
будет.

*/

#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "test_runner.h"

using namespace std;

struct Email {
  string from;
  string to;
  string body;
};

class Worker {
 public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
    // только первому worker-у в пайплайне нужно это имплементировать
    throw logic_error("Unimplemented");
  }

 protected:
  // реализации должны вызывать PassOn, чтобы передать объект дальше
  // по цепочке обработчиков
  void PassOn(unique_ptr<Email> email) const {
    if (next_) {
      next_->Process(move(email));
    }
  }

 public:
  void SetNext(unique_ptr<Worker> next) {
    if (next_) {
      next_->SetNext(move(next));
    } else {
      next_ = move(next);
    }
  }

 private:
  unique_ptr<Worker> next_ = nullptr;
};

class Reader : public Worker {
 public:
  // реализуйте класс
  Reader(istream& in) : in_(in) {}

  void Run() {
    do {
      unique_ptr<Email> email = make_unique<Email>();
      if (!getline(in_, email->from)) {
        break;
      }
      if (!getline(in_, email->to)) {
        break;
      }
      if (!getline(in_, email->body)) {
        break;
      }
      PassOn(move(email));
    } while (true);
  }

  void Process(unique_ptr<Email> email) {}
  friend ostream& operator<<(ostream& os, const Reader& reader);

 private:
  istream& in_;
};

ostream& operator<<(ostream& os, const Email& email) {
  os << email.from << "\n";
  os << email.to << "\n";
  os << email.body;
  return os;
}

class Filter : public Worker {
 public:
  using Function = function<bool(const Email&)>;

 public:
  // реализуйте класс
  Filter(Function func) : func_(func) {}

  void Process(unique_ptr<Email> email) {
    if (func_(*email)) {
      PassOn(move(email));
    }
  }

 private:
  Function func_;
};

class Copier : public Worker {
 public:
  // реализуйте класс
  Copier(string recipient) : recipient_(recipient) {}

  void Process(unique_ptr<Email> email) {
    unique_ptr<Email> email2 = make_unique<Email>(*email);
    PassOn(move(email));
    if (email2->to != recipient_) {
      email2->to = recipient_;
      PassOn(move(email2));
    }
  }

 private:
  string recipient_;
};

class Sender : public Worker {
 public:
  // реализуйте класс
  Sender(ostream& os) : os_(os) {}

  void Process(unique_ptr<Email> email) {
    os_ << *email << "\n";
    PassOn(move(email));
  }

 private:
  ostream& os_;
};

// реализуйте класс
class PipelineBuilder {
 public:
  // добавляет в качестве первого обработчика Reader
  explicit PipelineBuilder(istream& in) { first_ = make_unique<Reader>(in); }

  // добавляет новый обработчик Filter
  PipelineBuilder& FilterBy(Filter::Function filter) {
    first_->SetNext(make_unique<Filter>(filter));
    return *this;
  }

  // добавляет новый обработчик Copier
  PipelineBuilder& CopyTo(string recipient) {
    first_->SetNext(make_unique<Copier>(recipient));
    return *this;
  };

  // добавляет новый обработчик Sender
  PipelineBuilder& Send(ostream& out) {
    first_->SetNext(make_unique<Sender>(out));
    return *this;
  }

  // возвращает готовую цепочку обработчиков
  unique_ptr<Worker> Build() { return move(first_); }

 private:
  unique_ptr<Worker> first_;
};

void TestSanity() {
  string input =
      ("erich@example.com\n"
       "richard@example.com\n"
       "Hello there\n"

       "erich@example.com\n"
       "ralph@example.com\n"
       "Are you sure you pressed the right button?\n"

       "ralph@example.com\n"
       "erich@example.com\n"
       "I do not make mistakes of that kind\n");
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy(
      [](const Email& email) { return email.from == "erich@example.com"; });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

  pipeline->Run();

  string expectedOutput =
      ("erich@example.com\n"
       "richard@example.com\n"
       "Hello there\n"

       "erich@example.com\n"
       "ralph@example.com\n"
       "Are you sure you pressed the right button?\n"

       "erich@example.com\n"
       "richard@example.com\n"
       "Are you sure you pressed the right button?\n");

  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}
