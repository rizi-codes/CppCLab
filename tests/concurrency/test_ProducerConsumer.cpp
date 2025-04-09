#include "concurrency/ProducerConsumer.h"
#include "gtest/gtest.h"
#include <thread>
#include <vector>

TEST(ProducerConsumerTest, MultipleProducersConsumers) {
  ProducerConsumer pc(50);

  const int numProducers = 20;
  const int numConsumers = 10;

  const int itemsPerProducer = 10;
  const int itemsPerConsumer = 20;

  std::vector<std::thread> producers, consumers;

  for (int i = 0; i < numProducers; ++i) {
    producers.emplace_back([&pc, itemsPerProducer] {
      for (int j = 0; j < itemsPerProducer; ++j) {
        pc.produce();
      }
    });
  }

  for (int i = 0; i < numConsumers; ++i) {
    consumers.emplace_back([&pc, itemsPerConsumer] {
      for (int j = 0; j < itemsPerConsumer; ++j) {
        pc.consume();
      }
    });
  }

  for (auto &t : producers) {
    t.join();
  }

  for (auto &t : consumers) {
    t.join();
  }

  SUCCEED();
}
