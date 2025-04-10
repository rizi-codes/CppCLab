#include "concurrency/ThreadSafeInt.h"
#include "concurrency/ThreadSafePrint.h"

ThreadSafeInt::ThreadSafeInt(int value) : data(value) {}

void ThreadSafeInt::readInt() {
  std::unique_lock<std::mutex> lock(mtx);
  writer_cv.wait(lock, [this] { return !writerActive; });

  readersCount++;
  lock.unlock();

  ThreadSafePrint::print("Read: ", data);

  lock.lock();
  readersCount--;

  if (readersCount == 0) {
    reader_cv.notify_all();
  }
}

void ThreadSafeInt::writeInt(int newValue) {
  std::unique_lock<std::mutex> lock(mtx);
  reader_cv.wait(lock, [this] { return readersCount == 0 && !writerActive; });

  writerActive = true;

  data = newValue;
  ThreadSafePrint::print("Write: ", newValue);

  writerActive = false;
  reader_cv.notify_all();
  writer_cv.notify_all();
}
