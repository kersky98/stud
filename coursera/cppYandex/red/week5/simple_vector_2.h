/*Решите задачу «Реализовать свой вектор» со следующими дополнительными требованиями:

метод PushBack должен позволять добавить элемент в вектор с помощью перемещения;
никакие методы вектора не должны осуществлять копирование элементов.

Таким образом, должен получиться вектор, позволяющий хранить некопируемые объекты.

Шаблон решения содержит юнит-тест, проверяющий работу вектора, состоящего из некопируемых
строк. Если вектор будет осуществлять копирования, благодаря указанному юнит-тесту
решение не скомпилируется.
*/
#include <cstdint>
#include <algorithm>

using namespace std;

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector():
    data(nullptr), end_(nullptr), size_(0), capacity_(0){
  };
  explicit SimpleVector(size_t size):
    size_(size), capacity_(2*size){
    data = new T[capacity_];
    end_ = data + size;
  }
  SimpleVector(SimpleVector&& other):
    data(other.begin()),
    end_(other.end()),
    size_(other.Size()),
    capacity_(other.Capacity()){
    other.nullSimpleVector();
  }
  ~SimpleVector(){
    delete[] data;
  }

  T& operator[](size_t index){
    return data[index];
  }
  /*SimpleVector<T>& operator=(const SimpleVector<T>& other){
    if(&other == this){
      return *this;
    }else{
      size_ = other.Size();
      capacity_ = 2*size_;
      delete[] data;
      data = new T[capacity_];
      end_ = data + size_;
      std::move(other.begin(), other.end(), begin());
      return *this;
    }
  }*/
  T* begin(){return data;};
  T* end(){return end_;};
  const T* begin() const {return data;};
  const T* end() const {return end_;};

  size_t Size() const {return size_;};
  size_t Capacity() const {return capacity_;};
  void nullSimpleVector(){
    data = nullptr;
    end_ = nullptr;
    size_ = capacity_ = 0;
  }

  void PushBack(T&& value){
    if(capacity_ == 0){
      size_ = 1;
      capacity_ = 1;
      data = new T[capacity_];
      end_ = data + size_;
      data[0] = move(value);
    }else{
      if(size_ < capacity_){
        size_++;
        end_ = data + size_;
        data[size_ - 1] = move(value);
      }else{
        capacity_ *= 2;
        T* new_data = new T[capacity_];
        std::move(data, data+size_, new_data);
        delete [] data;
        data = new_data;
        size_++;
        end_ = data + size_;
        data[size_ - 1] = move(value);
      }
    }
  }
  void PushBack(const T& value){
    if(capacity_ == 0){
      size_ = 1;
      capacity_ = 1;
      data = new T[capacity_];
      end_ = data + size_;
      data[0] = value;
    }else{
      if(size_ < capacity_){
        size_++;
        end_ = data + size_;
        data[size_ - 1] = value;
      }else{
        capacity_ *= 2;
        T* new_data = new T[capacity_];
        std::copy(data, data+size_, new_data);
        delete [] data;
        data = new_data;
        size_++;
        end_ = data + size_;
        data[size_ - 1] = value;
      }
    }
  }

private:
  // Добавьте поля для хранения данных вектора
  T* data;
  T* end_;
  size_t size_, capacity_;
};
