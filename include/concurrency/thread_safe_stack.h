#ifndef THREAD_SAFE_STACK_H
#define THREAD_SAFE_STACK_H

#include "common/list_node.h"
#include <condition_variable>
#include <mutex>
#include <thread>

template <typename T> class thread_safe_stack {
public:
  explicit thread_safe_stack() : head(nullptr), size(0) {}

  int get_size() {
    std::unique_lock<std::mutex> lock(mtx);
    return size;
  }

  void push(T data) {
    std::unique_lock<std::mutex> lock(mtx);

    size += 1;
    list_node<T> *node = new list_node<T>(data);
    node->next = head;
    head = node;
  }

  bool pop(T &result) {
    std::unique_lock<std::mutex> lock(mtx);

    if (head == nullptr) {
      return false;
    }

    size -= 1;
    list_node<T> *node = head;
    T data = node->data;
    head = node->next;
    delete node;
    result = data;
    return true;
  }

  ~thread_safe_stack() {
    std::unique_lock<std::mutex> lock(mtx);

    while (head != nullptr) {
      list_node<T> *current = head;
      head = head->next;
      delete current;
    }
  }

private:
  std::mutex mtx;
  list_node<T> *head;
  int size;
};

#endif
