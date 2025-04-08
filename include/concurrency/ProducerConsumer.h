#ifndef PRODUCERCONSUMER_H
#define PRODUCERCONSUMER_H


#include <vector>
#include <mutex>
#include <condition_variable>
#include "util/random-generator.h"

class ProducerConsumer {
public:
    ProducerConsumer(int maxSize);
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
