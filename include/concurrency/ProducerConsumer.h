#ifndef PRODUCERCONSUMER_H
#define PRODUCERCONSUMER_H

#include "util/random-generator.h"
#include <condition_variable>
#include <mutex>
#include <vector>

class ProducerConsumer {
public:
  explicit ProducerConsumer(int maxSize);
  void produce();
  void consume();

private:
  int maxSize;
  std::vector<int> buffer;
  std::mutex mtx;
  std::condition_variable cv;
  RandomGenerator rng;
};

#endif
