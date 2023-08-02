#ifndef S21_CONTAINERS_SRC_S21_STACK_H
#define S21_CONTAINERS_SRC_S21_STACK_H

#include "s21_list.h"

namespace s21 {
template <class T, class Container = s21::list<T>>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;  // Fixed the type for size_type

  stack() : st() {}
  stack(std::initializer_list<value_type> const &items) : st(items) {}
  stack(stack &&s) : st(std::move(s.st)) {}
  stack(const stack &s) : st(s.st) {}
  ~stack() {}
  stack &operator=(stack &&s) {
    this->st = std::move(s.st);
    return *this;
  };

  stack &operator=(const stack &s) {
    if (this == &s) {
      return *this;
    }
    this->st = s.st;
    return *this;
  };

  const_reference top() const { return st.back(); }

  bool empty() { return st.empty(); }
  size_type size() { return st.size(); }

  void push(const_reference value) { this->st.push_back(value); }
  void pop() { this->st.pop_back(); }
  void swap(stack &other) { this->st.swap(other); }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    (push(std::forward<Args>(args)), ...);
  }

 private:
  Container st;
};

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_STACK_H