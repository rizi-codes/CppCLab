#ifndef LOCK_FREE_STACK_H
#define LOCK_FREE_STACK_H

#include "common/list_node.h"
#include <atomic>
#include <memory>

template <typename T> class lock_free_stack {
public:
  explicit lock_free_stack() : head(nullptr) {}

  void push(const T &data) {
    list_node<T> *node = new list_node<T>(data);

    node->next = head.load(std::memory_order_relaxed);

    while (!head.compare_exchange_weak(node->next, node,
                                       std::memory_order_release,
                                       std::memory_order_relaxed)) {
    }
  }

  bool pop(T &result) {
    list_node<T> *node = head.load(std::memory_order_acquire);

    while (node != nullptr) {
      list_node<T> *next = node->next;

      if (head.compare_exchange_weak(node, next, std::memory_order_acq_rel,
                                     std::memory_order_acquire)) {
        result = node->data;
        delete node;
        return true;
      }
    }

    return false;
  }

  ~lock_free_stack() {
    list_node<T> *node = head.load();

    while (node != nullptr) {
      list_node<T> *next = node->next;
      delete node;
      node = next;
    }
  }

private:
  std::atomic<list_node<T> *> head;
};

#endif
