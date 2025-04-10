#ifndef THREAD_SAFE_PRINT
#define THREAD_SAFE_PRINT

#include <iostream>
#include <mutex>

class ThreadSafePrint {
public:
  template <typename... Args> static void print(Args &&...args) {
    std::lock_guard<std::mutex> lock(mtx);
    (std::cout << ... << args) << '\n';
  }

private:
  static std::mutex mtx;
};

#endif
