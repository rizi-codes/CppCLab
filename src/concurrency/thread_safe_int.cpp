#include "concurrency/thread_safe_int.h"
#include "concurrency/thread_safe_print.h"

thread_safe_int::thread_safe_int(int value) : data(value) {}

void thread_safe_int::readInt() {
  std::unique_lock<std::mutex> lock(mtx);
  writer_cv.wait(lock, [this] { return !writer_active; });

  readers_count++;
  lock.unlock();

  thread_safe_print::print("Read: ", data);

  lock.lock();
  readers_count--;

  if (readers_count == 0) {
    reader_cv.notify_all();
  }
}

void thread_safe_int::writeInt(int newValue) {
  std::unique_lock<std::mutex> lock(mtx);
  reader_cv.wait(lock, [this] { return readers_count == 0 && !writer_active; });

  writer_active = true;

  data = newValue;
  thread_safe_print::print("Write: ", newValue);

  writer_active = false;
  reader_cv.notify_all();
  writer_cv.notify_all();
}
