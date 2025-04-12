#ifndef THREAD_SAFE_INT_H
#define THREAD_SAFEI_NT_H

#include <condition_variable>
#include <mutex>
#include <thread>

class thread_safe_int {
public:
  explicit thread_safe_int(int value);
  void readInt();
  void writeInt(int newValue);

private:
  int data;
  std::mutex mtx;
  std::condition_variable reader_cv;
  std::condition_variable writer_cv;
  int readers_count = 0;
  bool writer_active = false;
};

#endif
