#ifndef THREADSAFEINT_H
#define THREADSAFEINT_H

#include <condition_variable>
#include <mutex>

class ThreadSafeData {
public:
  void readData();
  void writeData(int newValue);

private:
  int data;
  std::mutex mtx;
  std::condition_variable cv;
  int readersCount = 0;
  bool writerActive = false;
};
