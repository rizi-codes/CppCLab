#ifndef THREAD_SAFE_STACK_H
#define THREAD_SAFE_STACK_H

#include "common/list_node.h"
#include <condition_variable>
#include <mutex>
#include <thread>

template <typename T> class thread_safe_stack {
public:
  explicit thread_safe_stack() : size(0), write_active(false), head(nullptr) {}

  int get_size() { return size; }

  void push(T data) {
    std::unique_lock<std::mutex> lock(mtx);

    size += 1;
    list_node<T> *node = new list_node<T>(data);
    node->next = head;
    head = node;
    cv.notify_all();
  }

  T pop() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] { return head != nullptr });

    size -= 1;
    list_node<T> *node = head;
    T data = node->data;
    head = node->next;
    delete node;
    cv.notify_all();

    return data;
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
  std::condition_variable cv;
  list_node<T> *head;
  int size;
};

#endif
