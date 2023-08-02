#ifndef S21_CONTAINERS_SRC_S21_VECTOR_H_
#define S21_CONTAINERS_SRC_S21_VECTOR_H_

#include <initializer_list>
#include <iostream>
#include <limits>

// Test vector class with some basic example operations and concepts
namespace s21 {
template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  using difference_type = std::ptrdiff_t;

  vector() {
    m_capacity = 0;
    m_size = 0;
    arr = nullptr;
  }  // default constructor (simplified syntax for assigning values to
     // attributes)
  explicit vector(size_type n) {
    if (n > 0) {
      m_capacity = n;
      m_size = n;
      arr = new value_type[m_capacity];
    }
  }  // parametrized constructor for fixed size vector
  vector(std::initializer_list<value_type> const &items) {
    arr = new value_type[items.size()];
    int i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
      arr[i] = *it;
      i++;
    }

    m_size = items.size();
    m_capacity = items.size();
  }  // initializer list constructor (allows creating lists
     // with initializer lists, see main.cpp)
  vector(const vector &v) {
    m_size = v.m_size;
    m_capacity = v.m_capacity;
    arr = new value_type[m_capacity];
    for (size_type i = 0; i < m_size; ++i) arr[i] = v.arr[i];
  }  // copy constructor with simplified syntax
  vector(vector &&v) noexcept {
    m_size = v.m_size;
    m_capacity = v.m_capacity;
    arr = v.arr;
    v.arr = nullptr;
    v.m_size = 0;
    v.m_capacity = 0;
  }  // move constructor with simplified syntax

  vector &operator=(const vector &v) {
    delete[] arr;
    m_size = v.m_size;
    m_capacity = v.m_capacity;
    arr = new value_type[m_capacity];
    for (size_type i = 0; i < m_size; ++i) arr[i] = v.arr[i];

    return *this;
  }  // assigment values from one vector to another one
  vector &operator=(vector &&v) {
    if (&v != this) {
      delete[] arr;
      arr = v.arr;
      m_size = v.m_size;
      m_capacity = v.m_capacity;
      v.arr = nullptr;
      v.m_size = 0;
      v.m_capacity = 0;
    }
    return *this;
  }  // assignment operator overload for moving object

  ~vector() {
    delete[] arr;
    m_capacity = 0;
    m_size = 0;
  }  // destructor

  inline value_type at(size_type i) const {
    if (i >= m_size) throw std::out_of_range("Index out of range");

    return arr[i];
  }  // element accessor
  inline reference operator[](size_type pos) const noexcept {
    return arr[pos];
  }  // access specified element
  inline const_reference front() const noexcept {
    return arr[0];
  }  // access the first element
  inline const_reference back() const noexcept {
    return arr[m_size - 1];
  }  // access the last element
  inline T *data() const noexcept {
    return arr;
  }  // direct access to the underlying array

  inline iterator begin() const noexcept {
    return arr;
  }  // returns an iterator to the beginning
  inline iterator end() noexcept {
    return arr + size();
  }  // returns an iterator to the end

  inline bool empty() const noexcept {
    bool result = true;
    if (m_size != 0) result = false;

    return result;
  }  // checks whether the container is empty
  inline size_type size() const noexcept { return m_size; }  // size getter
  inline size_type max_size() const {
    return std::numeric_limits<int>::max();
  }  // returns the maximum possible number of elements
  void reserve(size_type size) {
    value_type *buff = new value_type[size];

    for (size_t i = 0; i < m_size; ++i) buff[i] = std::move(arr[i]);

    delete[] arr;
    arr = buff;
    m_capacity = size;
  }  // allocate storage of size elements and copies current
     // array elements to a newely allocated array
  inline size_type capacity() const noexcept {
    return m_capacity;
  }  // capasity getter
  void shrink_to_fit() {
    value_type *buff = new value_type[m_size];

    for (size_t i = 0; i < m_size; ++i) buff[i] = std::move(arr[i]);

    delete[] arr;
    arr = buff;
    m_capacity = m_size;
  }  // reduces memory usage by freeing unused memory

  inline void clear() {
    delete[] arr;
    m_size = 0;
    arr = nullptr;
    value_type *buff = new value_type[m_capacity];
    arr = buff;
  }  // clears the contents

  iterator insert(iterator pos, const_reference value) {
    size_type index = pos - begin();

    if (m_size >= m_capacity) reserve(m_size * 2);

    value_type *tempArr = new value_type[m_capacity];

    for (size_type i = 0; i < index; ++i) tempArr[i] = arr[i];

    tempArr[index] = value;

    for (size_type i = index; i < m_size; ++i) tempArr[i + 1] = arr[i];

    delete[] arr;
    arr = tempArr;

    ++m_size;
    return begin() + index;
  }  // inserts elements into concrete pos and returns
     // the iterator that points to the new element
  void erase(iterator pos) {
    if (pos >= begin() && pos < end()) {
      size_t index = pos - begin();
      for (size_t i = index; i < m_size - 1; ++i) arr[i] = arr[i + 1];
      m_size--;
    }
  }  // erases element at pos
  inline void push_back(value_type v) {
    if (m_size != 0 && m_size >= m_capacity)
      reserve(m_size * 2);

    else if (m_size == 0)
      reserve(1);

    arr[m_size++] = v;
  }  // append new element
  inline void pop_back() {
    value_type *data = (value_type *)arr;
    data[m_size - 1].~T();
    m_size--;
  }  // removes the last element
  inline void swap(vector &other) {
    vector<T> temp(std::move(other));
    other = std::move(*this);
    *this = std::move(temp);
  }  // swap the contents

  template <typename... Args>
  inline iterator insert_many(const_iterator pos, Args &&...args) {
    size_type index = pos - arr;
    (insert_impl(index++, std::forward<Args>(args)), ...);
    return arr + index;
  }  // inserts new elements into the container directly before pos

  template <typename... Args>
  inline void insert_many_back(Args &&...args) {
    (push_back(std::forward<Args>(args)), ...);
  }  // appends new elements to the end of the container

 private:
  size_t m_size;
  size_t m_capacity;
  T *arr;

  void insert_impl(size_type index, const_reference value) {
    if (index > m_size) throw std::out_of_range("Index out of range");

    if (m_size == m_capacity) reserve(m_capacity == 0 ? 1 : m_capacity * 2);

    std::copy_backward(arr + index, arr + m_size, arr + m_size + 1);
    arr[index] = value;
    m_size++;
  }
};
}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_VECTOR_H_
