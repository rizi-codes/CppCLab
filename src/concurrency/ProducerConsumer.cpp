#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

#include "concurrency/ProducerConsumer.h"
#include "concurrency/ThreadSafePrint.h"
#include "util/RandomGenerator.h"

ProducerConsumer::ProducerConsumer(int maxSize) : maxSize(maxSize), rng() {
  buffer.reserve(maxSize);
}

void ProducerConsumer::consume() {
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this] { return !buffer.empty(); });
  int number = buffer.back();
  buffer.pop_back();
  ThreadSafePrint::print("consumed: ", number);
  cv.notify_all();
}

void ProducerConsumer::produce() {
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this] { return buffer.size() < maxSize; });
  int number = rng.nextInt(1, 40);
  buffer.push_back(number);
  ThreadSafePrint::print("produced: ", number);
  cv.notify_all();
}
