#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

#include "concurrency/producer_consumer.h"
#include "concurrency/thread_safe_print.h"
#include "util/random_generator.h"

producer_consumer::producer_consumer(int maxSize) : maxSize(maxSize), rng() {
  buffer.reserve(maxSize);
}

void producer_consumer::consume() {
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this] { return !buffer.empty(); });
  int number = buffer.back();
  buffer.pop_back();
  thread_safe_print::print("consumed: ", number);
  cv.notify_all();
}

void producer_consumer::produce() {
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this] { return buffer.size() < maxSize; });
  int number = rng.nextInt(1, 40);
  buffer.push_back(number);
  thread_safe_print::print("produced: ", number);
  cv.notify_all();
}
