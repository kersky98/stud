#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0):sz(a_size){
    if(a_size > N){
      throw invalid_argument("invalid_argument");
    }
  }

  T& operator[](size_t index){
    return a[index];
  }
  const T& operator[](size_t index) const{
    return a[index];
  }

  typename array<T, N>::iterator begin(){
    return a.begin();
  }
  typename array<T, N>::iterator end(){
    return a.begin() + sz;
  }
  typename array<T, N>::const_iterator begin() const{
    return a.begin();
  }
  typename array<T, N>::const_iterator end() const{
    return a.begin() + sz;
  }

  size_t Size() const{
    return sz;
  }
  size_t Capacity() const{
    return N;
  }

  void PushBack(const T& value){
    if(sz >= N){
      throw overflow_error("overflow_error");
    }
    a[sz] = value;
    sz++;
  }
  T PopBack(){
    if(sz <= 0){
      throw underflow_error("underflow_error");
    }
    sz--;
    return a[sz];
  }

private:
  size_t sz;
  array<T, N> a;
};

