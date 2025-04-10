#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

#include "concurrency/PrintThreadSafe.h"
#include "concurrency/ProducerConsumer.h"
#include "util/RandomGenerator.h"

ProducerConsumer::ProducerConsumer(int maxSize) : maxSize(maxSize), rng() {
  buffer.reserve(maxSize);
}

void ProducerConsumer::consume() {
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this] { return !buffer.empty(); });
  int number = buffer.back();
  buffer.pop_back();
  PrintThreadSafe::print("consumed: ", number);
  cv.notify_all();
}

void ProducerConsumer::produce() {
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this] { return buffer.size() < maxSize; });
  int number = rng.nextInt(1, 40);
  buffer.push_back(number);
  PrintThreadSafe::print("produced: ", number);
  cv.notify_all();
}
