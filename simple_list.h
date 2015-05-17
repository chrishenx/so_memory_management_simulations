/**
  This file defines a simple linked list.
  @author Chritian Gonzalez Leon : Aliases (chrishenx, CPlayMasH on youtube)
 */

#ifndef SIMPLE_LIST_H
#define SIMPLE_LIST_H

using uint = unsigned int;

#include <iostream>

template <typename T>
class SList {
  template <typename U>
  struct Node;
 public:
  struct Iterator;

  SList() {}
  SList(std::initializer_list<T> il);
  SList(const SList& other);
  SList(SList&& other) {
    first = other.first;
    mlength = other.mlength;
    other.first = nullptr;
    other.mlength = 0;
  }
  ~SList() { clear(); }
  SList& operator=(const SList& other);
  SList& operator=(SList&& other) {
    if (this != &other) {
      clear();
      first = other.first;
      mlength = other.mlength;
      other.first = nullptr;
      other.mlength = 0;
    }
    return *this;
  }
  void push_front(const T& value) {
    push_front(new Node<T>(value, first));
  }
  void push_front(T&& value) {
    push_front(new Node<T>(std::move(value), first));
  }
  bool pop_front() {
    if (first != nullptr) {
      Node<T>* node = first;
      first = first->next;
      delete node;
      mlength--;
      return true;
    }
    return false;
  }
  Iterator insert(const Iterator& it, const T& value) {
    return insert(it, new Node<T>(value, !it ? first : it.content->next));
  }
  Iterator insert(const Iterator& it, T&& value) {
    return insert(it, new Node<T>(std::move(value), !it ? first : it.content->next));
  }
  Iterator insert(const Iterator& it, uint n, const T& value);
  Iterator erase(const Iterator& it);
  bool contains(const T& value) const;
  void clear();
  const T& front() const { return first != nullptr ? first->value : T(); }
  bool empty() const { return first == nullptr; }
  uint length() const { return mlength; }
  Iterator begin() const { return Iterator(first); }
  Iterator end() const { return Iterator(nullptr); }
  Iterator before_begin() const { return Iterator(nullptr); }
  Iterator iterator(uint pos) const { return Iterator(getNode(pos)); }
 private:
  Node<T>* getNode(uint pos) const;
  void push_front(Node<T>* new_node) {
    first = new_node;
    mlength++;
  }
  Iterator insert(const Iterator& it, Node<T>* new_node) {
    if (it.content == nullptr) {
      push_front(new_node);
    } else {
      it.content->next = new_node;
      mlength++;
    }
    return Iterator(new_node);
  }

  Node<T>* first = nullptr;
  uint mlength = 0;
};

#include "simple_list.cpp"

template <typename T>
template <typename U>
struct SList<T>::Node {
  Node(const U& value, Node* next = nullptr) : value(value) {
    this->next = next;
  }
  Node(U&& value, Node* next = nullptr) : value(std::move(value)) {
    this->next = next;
  }
  U value;
  Node* next;
};

template <typename T>
struct SList<T>::Iterator {
  friend class SList<T>;
  Iterator(Node<T>* content) { this->content = content; }
  T& operator*() { return content->value; }
  T* operator->() { return &(content->value); }
  Iterator& operator++() {
    if (content) content = content->next;
    return *this;
  }
  Iterator operator++(int) {
    Iterator it(content);
    if (content) content = content->next;
    return it;
  }
  Iterator operator+=(uint n) {
    while (n-- > 0) (*this)++;
    return *this; 
  }
  bool is_nullptr() const { return content == nullptr; }
  bool has_next() const { return content == nullptr ? false : content->next != nullptr; }
  bool operator==(const Iterator& other) const { 
    return content == other.content;
  }
  bool operator!=(const Iterator& other) const {
    return content != other.content;
  }
  bool operator!() const { return content == nullptr; }
  operator bool() const { return content != nullptr; }
  operator T*() { return content == nullptr ? nullptr : &content->value; }
 private:
  Node<T>* content = nullptr;
};

#endif // SIMPLE_LIST_H