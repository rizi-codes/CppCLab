#ifndef LIST_NODE_H
#define LIST_NODE_H

template <typename T> struct list_node {
  T data;
  list_node<T> *next;
  explicit list_node(const T &value) : data(value), next(nullptr) {}
};

#endif
