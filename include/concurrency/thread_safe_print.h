#ifndef THREAD_SAFE_PRINT_H
#define THREAD_SAFE_PRINT_H

#include <iostream>
#include <mutex>

class thread_safe_print {
public:
  template <typename... Args> static void print(Args &&...args) {
    std::lock_guard<std::mutex> lock(mtx);
    (std::cout << ... << args) << '\n';
  }

private:
  static std::mutex mtx;
};

#endif
