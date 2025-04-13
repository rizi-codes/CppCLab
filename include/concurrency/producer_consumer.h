#ifndef PRODUCER_CONSUMER_H
#define PRODUCER_CONSUMER_H

#include "util/random_generator.h"
#include <condition_variable>
#include <mutex>
#include <vector>

class producer_consumer {
public:
  explicit producer_consumer(int maxSize);
  void produce();
  void consume();

private:
  size_t maxSize;
  std::vector<int> buffer;
  std::mutex mtx;
  std::condition_variable cv;
  random_generator rng;
};

#endif
