#include <algorithm>
#include <list>
#include <mutex>

#include "Common.h"

using namespace std;

class LruCache : public ICache {
 public:
  LruCache(shared_ptr<IBooksUnpacker> books_unpacker, const Settings& settings)
      : books_unpacker_(books_unpacker), settings_(settings), memory_used_(0) {
    // реализуйте метод
  }

  BookPtr GetBook(const string& book_name) override {
    // реализуйте метод
    lock_guard<mutex> lock(m);
    list<BookPtr>::iterator it =
        find_if(lbooks_.begin(), lbooks_.end(), [&book_name](BookPtr p) {
          return p->GetName() == book_name;
        });
    if (it == lbooks_.end()) {  // такой книги еще не было
      shared_ptr<IBook> p = books_unpacker_->UnpackBook(book_name);
      size_t current_size = p->GetContent().size();
      if(current_size > settings_.max_memory) { // если размер книги уже больше максимальной памяти, то выходим
        lbooks_.clear();
        memory_used_ = 0;
        return nullptr;
      }
      while((memory_used_ + current_size) > settings_.max_memory) { // удаляем старые элементы пока не будет хватать памяти
        memory_used_ -= lbooks_.back()->GetContent().size();
        lbooks_.pop_back();
      }
      memory_used_ += current_size;
      lbooks_.push_front(p);
    } else {  // такая книга уже есть
      BookPtr top = *it;
      lbooks_.erase(it);
      lbooks_.push_front(top);
    }

    return lbooks_.front();
  }

 private:
  shared_ptr<IBooksUnpacker> books_unpacker_;
  const Settings& settings_;
  list<BookPtr> lbooks_;
  mutex m;
  size_t memory_used_;
};

unique_ptr<ICache> MakeCache(shared_ptr<IBooksUnpacker> books_unpacker,
                             const ICache::Settings& settings) {
  // реализуйте функцию
  return make_unique<LruCache>(books_unpacker, settings);
}
