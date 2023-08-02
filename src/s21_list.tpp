// #include "s21_list.h"

template <typename T>
s21::list<T>::list() {
  head = nullptr;
  tail = nullptr;
  list_size = 0;
}

template <typename T>
s21::list<T>::list(size_type n) {
  list_size = n;
  for (size_t i = 0; i < n; i++) {
    Node* newNode = new Node;
    newNode->list_arr = T();
    newNode->next = nullptr;

    if (head == nullptr) {
      head = tail = newNode;
    } else {
      newNode->prev = tail;
      tail->next = newNode;
      tail = newNode;
    }
  }
}

template <typename T>
s21::list<T>::list(std::initializer_list<value_type> const& items) {
  head = nullptr;
  tail = nullptr;
  for (auto it = items.begin(); it != items.end(); ++it) {
    Node* newNode = new Node;
    newNode->list_arr = *it;
    newNode->next = nullptr;
    if (head == nullptr) {
      head = tail = newNode;
    } else {
      newNode->prev = tail;
      tail->next = newNode;
      tail = newNode;
    }
  }
  list_size = items.size();
}

template <typename T>
s21::list<T>::list(const list& l) {
  head = nullptr;
  tail = nullptr;
  list_size = 0;
  Node* current = l.head;
  while (current != nullptr) {
    push_back(current->list_arr);
    current = current->next;
  }
  list_size = l.list_size;
}

template <typename T>
s21::list<T>::list(list&& l) {
  head = l.head;
  tail = l.tail;
  list_size = l.list_size;
  l.tail = nullptr;
  l.head = nullptr;
  l.list_size = 0;
}

template <typename T>
s21::list<T>::~list() {
  Node* current = head;
  while (current != nullptr) {
    Node* tmp = current->next;
    delete current;
    current = tmp;
  }
  list_size = 0;
}

template <typename T>
s21::list<T>& s21::list<T>::operator=(const list& l) {
  this->head = nullptr;
  this->tail = nullptr;
  this->list_size = 0;
  Node* current = l.head;
  while (current != nullptr) {
    push_back(current->list_arr);
    current = current->next;
  }
  list_size = l.list_size;
  return *this;
}

template <typename T>
s21::list<T>& s21::list<T>::operator=(list&& l) {
  this->head = l.head;
  this->tail = l.tail;
  this->list_size = l.list_size;
  l.tail = nullptr;
  l.head = nullptr;
  l.list_size = 0;
  return *this;
}

template <typename T>
typename s21::list<T>::const_reference s21::list<T>::front() const {
  if (list_size == 0) {
    throw std::out_of_range("the list is empty");
  }
  return head->list_arr;
}

template <typename T>
typename s21::list<T>::const_reference s21::list<T>::back() const {
  if (list_size == 0) {
    throw std::out_of_range("the list is empty");
  }
  return tail->list_arr;
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::begin() {
  return iterator(head);
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::end() {
  return iterator(nullptr);
}

template <typename T>
typename s21::list<T>::const_iterator s21::list<T>::cbegin() const {
  return const_iterator(head);
}

template <typename T>
typename s21::list<T>::const_iterator s21::list<T>::cend() const {
  return const_iterator(nullptr);
}

template <typename T>
bool s21::list<T>::empty() {
  bool status = 0;
  if (list_size == 0) {
    status = 1;
  }
  return status;
}

template <typename T>
typename s21::list<T>::size_type s21::list<T>::size() {
  return list_size;
}

template <typename T>
typename s21::list<T>::size_type s21::list<T>::max_size() {
  return std::numeric_limits<int>::max();
}

template <typename T>
void s21::list<T>::clear() {
  Node* current = head;
  while (current != nullptr) {
    Node* tmp = current;
    current = current->next;
    delete tmp;
  }
  head = nullptr;
  tail = nullptr;
  list_size = 0;
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::insert(iterator pos,
                                                     const_reference value) {
  Node* newNode = new Node;
  newNode->list_arr = value;

  if (pos == begin()) {
    newNode->next = head;
    if (head != nullptr) {
      head->prev = newNode;
    }
    head = newNode;
  } else if (pos == end()) {
    if (tail != nullptr) {
      tail->next = newNode;
    } else {
      head = newNode;  // Если список пуст, новый элемент становится головой
    }
    newNode->prev = tail;
    tail = newNode;
  } else {
    newNode->next = pos.iter;
    newNode->prev = pos.iter->prev;
    pos.iter->prev->next = newNode;
    pos.iter->prev = newNode;
  }

  ++list_size;
  return iterator(newNode);
}

template <typename T>
void s21::list<T>::erase(iterator pos) {
  if (pos == end() || pos.iter == nullptr) {
    throw std::out_of_range(
        "Iterator is not valid or points to the end of the list");
  }

  Node* nodeToDelete = pos.iter;

  if (nodeToDelete == head) {
    head = nodeToDelete->next;
    if (head != nullptr) {
      head->prev = nullptr;
    }
  } else {
    nodeToDelete->prev->next = nodeToDelete->next;
    if (nodeToDelete->next != nullptr) {
      nodeToDelete->next->prev = nodeToDelete->prev;
    } else {
      tail = nodeToDelete->prev;
    }
  }

  delete nodeToDelete;
  list_size--;
}

template <typename T>
void s21::list<T>::push_front(const_reference value) {
  Node* tmp = new Node;
  tmp->list_arr = value;
  tmp->next = head;
  tmp->prev = nullptr;

  if (head == nullptr) {
    head = tmp;
    tail = tmp;
  } else {
    head->prev = tmp;
    head = tmp;
  }

  list_size++;
}

template <typename T>
void s21::list<T>::pop_front() {
  Node* tmp = nullptr;
  if (list_size == 0) {
    throw std::out_of_range("the list is empty");
  }
  tmp = head;
  head = head->next;
  if (head != nullptr) {
    head->prev = nullptr;
  }
  delete tmp;
  list_size--;
}

template <typename T>
void s21::list<T>::push_back(const_reference value) {
  Node* newNode = new Node;
  newNode->list_arr = value;
  newNode->next = nullptr;
  newNode->prev = nullptr;
  if (head == nullptr) {
    head = tail = newNode;
  } else {
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
  }
  list_size++;
}

template <typename T>
void s21::list<T>::pop_back() {
  if (list_size == 0) {
    throw std::out_of_range("the list is empty");
  }
  if (list_size == 1) {
    delete tail;
    head = nullptr;
    tail = nullptr;
  } else {
    Node* prev_tail = tail->prev;
    delete tail;
    tail = prev_tail;
    tail->next = nullptr;
  }

  list_size--;
}

template <typename T>
void s21::list<T>::swap(list& other) {
  s21::list<T> tmp(*this);
  *this = other;
  other = tmp;
}

template <typename T>
void s21::list<T>::merge(list& other) {
  Node* current = other.head;
  while (current != nullptr) {
    push_back(current->list_arr);
    current = current->next;
  }
  other.clear();
  sort();
}

template <typename T>
void s21::list<T>::splice(const_iterator pos, list& other) {
  if (!other.empty()) {
    iterator pos_ = iterator(pos.iter);
    iterator it = other.begin();
    for (size_t i = 0; i < other.size(); ++i) {
      insert(pos_, *it);
      ++it;
    }
    other.clear();  // Освобождаем память, занимаемую узлами other
  }
}

template <typename T>
void s21::list<T>::reverse() {
  Node* current = head;
  Node* temp = nullptr;
  while (current != nullptr) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }
  temp = head;
  head = tail;
  tail = temp;
}

template <typename T>
void s21::list<T>::unique() {
  if (head == nullptr || head->next == nullptr) {
    throw std::out_of_range("the list is empty");
  }

  Node* current = head;
  Node* next_node = current->next;

  while (next_node != nullptr) {
    if (current->list_arr == next_node->list_arr) {
      current->next = next_node->next;
      if (next_node->next != nullptr) {
        next_node->next->prev = current;
      }
      delete next_node;
      next_node = current->next;
      list_size--;
    } else {
      current = next_node;
      next_node = next_node->next;
    }
  }

  tail = current;
  ;
}

template <typename T>
void s21::list<T>::sort() {
  if (list_size <= 1) {
    return;
  }

  Node* sorted = nullptr;

  while (head != nullptr) {
    Node* current = head;
    head = head->next;
    current->next = nullptr;

    if (sorted == nullptr || current->list_arr < sorted->list_arr) {
      current->next = sorted;
      sorted = current;
    } else {
      Node* temp = sorted;
      while (temp->next != nullptr &&
             !(current->list_arr < temp->next->list_arr)) {
        temp = temp->next;
      }
      current->next = temp->next;
      temp->next = current;
    }
  }
  head = sorted;
}