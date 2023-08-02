#ifndef S21_CONTAINERS_SRC_S21_QUEUE_H
#define S21_CONTAINERS_SRC_S21_QUEUE_H

#include "s21_list.h"

namespace s21 {
template <class T, class Container = s21::list<T>>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  queue() : que() {}
  queue(std::initializer_list<value_type> const &items) : que(items) {}
  queue(queue &&q) : que(std::move(q.que)) {}
  queue(const queue &q) : que(q.que) {}
  ~queue() {}

  queue &operator=(const queue &q) {
    if (this == &q) {
      return *this;
    }
    this->que = q.que;
    return *this;
  }

  queue &operator=(queue &&q) {
    this->que = std::move(q.que);
    return *this;
  }

  const_reference front() const { return que.front(); }
  const_reference back() const { return que.back(); }

  bool empty() { return que.empty(); }
  size_type size() { return que.size(); }

  void push(const_reference value) { que.push_back(value); }
  void pop() { que.pop_front(); }
  void swap(queue &other) { this->que.swap(other); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push(std::forward<Args>(args)), ...);
  }

 private:
  Container que;
};
}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_QUEUE_H