/**
  This file implements a simple linked list.
  
  @author Chritian Gonzalez Leon : Aliases (chrishenx, CPlayMasH on youtube)
 */


// SIMPLE LIST IMPLEMENTATION

#include <ostream>

template <typename T>
SList<T>::SList(const SList& other) {
  auto last_it = begin();
  for (Node<T>* node = other.first; node != nullptr; node = node->next) {
    last_it = insert(last_it, node->value);
  }
}

template <typename T>
SList<T>::SList(std::initializer_list<T> il) {
  auto it = il.begin();
  for (int i = il.size() - 1; i >= 0; i--) {
    push_front(it[i]);
  }
}

template <typename T>
SList<T>& SList<T>::operator=(const SList& other) {
  clear();
  auto last_it = begin();
  for (Node<T>* node = other.first; node != nullptr; node = node->next) {
    last_it = insert(last_it, node->value);
  }
}

template <typename T>
void SList<T>::clear() {
  while (first != nullptr) {
    pop_front();
  }
}

template <typename T>
typename SList<T>::Iterator SList<T>::insert(const Iterator& it, uint n, 
    const T& value) {
  Iterator aux = it;
  for (uint i = 0; i < n; i++) {
    aux = insert(aux, value);
  } 
  return aux;
}

template <typename T>
typename SList<T>::Iterator SList<T>::erase(const Iterator& it) {
  Node<T>* to_return = nullptr;
  if (first != nullptr) {
    if (it.content == nullptr) {
      pop_front();
      if (first != nullptr) {
        to_return = first;
      }
    } else {
      if(it.content->next != nullptr) {
        Node<T>* node = it.content->next;
        it.content->next = it.content->next->next;
        delete node;
        mlength--;
        to_return = it.content->next;
      }
    }
  }
  return Iterator(to_return);
}

template <typename T>
bool SList<T>::contains(const T& value) const {
  for (Node<T>* node = first; node != nullptr; node = node->next) {
    if (node->value == value) {
      return true;
    }
  }
  return false;
}

template <typename T>
SList<T>::Node<T>* SList<T>::getNode(uint pos) const {
  Node<T>* node = first;
  if (pos < mlength and pos >= 0 and mlength > 0) {
    for (uint i  = 0; i < pos; i++) {
      node = node->next;
    }
  }
  return node;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const SList<T>& slist) {
  for (const T& value : slist) {
    os << value << ' ';
  }
  return os;
}