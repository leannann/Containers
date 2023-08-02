#ifndef S21_CONTAINERS_SRC_S21_ARRAY_H_
#define S21_CONTAINERS_SRC_S21_ARRAY_H_

#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array() = default;

  array(std::initializer_list<value_type> const &items) {
    std::copy(items.begin(), items.end(), arr);
  }

  array(const array &a) { std::copy(a.arr, a.arr + N, arr); }

  array(array &&a) { std::move(a.arr, a.arr + N, arr); }

  ~array() = default;

  array &operator=(array &&a) {
    std::move(a.arr, a.arr + N, arr);
    return *this;
  }

  inline reference at(size_type pos) {
    if (pos >= N) throw std::out_of_range("array::at");

    return arr[pos];
  }

  inline reference operator[](size_type pos) noexcept { return arr[pos]; }

  inline const_reference front() const noexcept { return arr[0]; }

  inline const_reference back() const noexcept { return arr[N - 1]; }

  inline iterator data() const noexcept { return arr; }

  inline iterator begin() noexcept { return arr; }

  inline iterator end() noexcept { return arr + N; }

  inline bool empty() const noexcept { return size() == 0; }

  inline size_type size() const noexcept { return N; }

  inline size_type max_size() const noexcept { return N; }

  inline void swap(array &other) { std::swap_ranges(arr, arr + N, other.arr); }

  inline void fill(const_reference value) { std::fill(arr, arr + N, value); }

 private:
  value_type arr[N];
};
}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_ARRAY_H_