#ifndef THREADSAFEINT_H
#define THREADSAFEINT_H

#include <condition_variable>
#include <mutex>
#include <thread>

class ThreadSafeInt {
public:
  void readInt();
  void writeInt(int newValue);

private:
  int data;
  std::mutex mtx;
  std::condition_variable reader_cv;
  std::condition_variable writer_cv;
  int readersCount = 0;
  bool writerActive = false;
};

#endif
