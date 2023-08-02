#ifndef S21_CONTAINERS_SRC_S21_LIST_H
#define S21_CONTAINERS_SRC_S21_LIST_H

#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {

template <typename T>
class list {
 private:
  struct Node {
    T list_arr;
    Node* next;
    Node* prev;
  };
  Node* head;
  Node* tail;
  std::size_t list_size;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  template <typename value_type>
  class ListIterator {
   private:
    Node* iter;

   public:
    ListIterator(Node* lst) { iter = lst; }
    ListIterator(const ListIterator& other) { this->iter = other.iter; }
    ListIterator(ListIterator&& other) { this->iter = other.iter; }
    ~ListIterator() { iter = nullptr; }
    reference operator*() {
      if (iter == nullptr) {
        throw std::out_of_range("the list is empty");
      }
      return iter->list_arr;
    }

    ListIterator& operator++() {
      if (iter == nullptr) {
        throw std::out_of_range("the list is empty");
      }
      iter = iter->next;
      return *this;
    }

    ListIterator& operator--() {
      if (iter->prev == nullptr) {
        throw std::out_of_range("the list is empty");
      }
      iter = iter->prev;
      return *this;
    }

    bool operator!=(ListIterator const& other) const {
      return this->iter != other.iter;
    }

    bool operator==(ListIterator const& other) const {
      return this->iter == other.iter;
    }

    void operator=(const ListIterator& other) { this->iter = other.iter; }

    void operator=(ListIterator&& other) { this->iter = other.iter; }

    friend class list<T>;
  };

  template <typename value_type>
  class ConstListIterator {
   private:
    Node* iter;

   public:
    ConstListIterator(Node* lst) { iter = lst; }
    ConstListIterator(const ConstListIterator& other) {
      this->iter = other.iter;
    }
    ConstListIterator(ConstListIterator&& other) { this->iter = other.iter; }
    ~ConstListIterator() { iter = nullptr; }
    reference operator*() {
      if (iter == nullptr) {
        throw std::out_of_range("the list is empty");
      }
      return iter->list_arr;
    }

    ConstListIterator& operator++() {
      if (iter == nullptr) {
        throw std::out_of_range("the list is empty");
      }
      iter = iter->next;
      return *this;
    }

    ConstListIterator& operator--() {
      if (iter->prev == nullptr) {
        throw std::out_of_range("the list is empty");
      }
      iter = iter->prev;
      return *this;
    }

    bool operator!=(ConstListIterator const& other) const {
      return this->iter != other.iter;
    }

    bool operator==(ConstListIterator const& other) const {
      return this->iter == other.iter;
    }

    void operator=(const ConstListIterator& other) { this->iter = other.iter; }

    void operator=(ConstListIterator&& other) { this->iter = other.iter; }

    friend class list<T>;
  };

  using iterator = ListIterator<T>;
  using const_iterator = ConstListIterator<T>;

  list();
  list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l);
  ~list();
  list& operator=(list&& l);
  list& operator=(const list& l);

  const_reference front() const;
  const_reference back() const;

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    iterator pos_ = iterator(pos.iter);
    iterator it = (insert(pos_, std::forward<Args>(args)), ...);
    return it;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (push_back(std::forward<Args>(args)), ...);
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    (push_front(std::forward<Args>(args)), ...);
  }
};

#include "s21_list.tpp"

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_LIST_H
