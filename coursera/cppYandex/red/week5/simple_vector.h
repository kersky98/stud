#pragma once

#include <cstdlib>
#include <algorithm>

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
  ~SimpleVector(){
    delete[] data;
  }

  T& operator[](size_t index){
    return data[index];
  }
  SimpleVector<T>& operator=(const SimpleVector<T>& other){
    if(&other == this){
      return *this;
    }else{
      size_ = other.Size();
      capacity_ = 2*size_;
      delete[] data;
      data = new T[capacity_];
      end_ = data + size_;
      std::copy(other.begin(), other.end(), begin());
      return *this;
    }
  }
  T* begin(){return data;};
  T* end(){return end_;};
  const T* begin() const {return data;};
  const T* end() const {return end_;};

  size_t Size() const {return size_;};
  size_t Capacity() const {return capacity_;};
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
