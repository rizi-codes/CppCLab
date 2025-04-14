#include "concurrency/producer_consumer.h"
#include <benchmark/benchmark.h>
#include <thread>
#include <vector>

static void BM_ProducerConsumer(benchmark::State &state) {
  const int bufferSize = state.range(0);
  const int producerCount = state.range(1);
  const int consumerCount = state.range(2);
  const int opsPerThread = 1000;

  for (auto _ : state) {
    producer_consumer pc(bufferSize);

    std::vector<std::thread> producers, consumers;

    // Producers
    for (int i = 0; i < producerCount; ++i) {
      producers.emplace_back([&pc, opsPerThread] {
        for (int j = 0; j < opsPerThread; ++j) {
          pc.produce();
        }
      });
    }

    // Consumers
    for (int i = 0; i < consumerCount; ++i) {
      consumers.emplace_back([&pc, opsPerThread] {
        for (int j = 0; j < opsPerThread; ++j) {
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
  }
}

// Register benchmark: Buffer size, producers, consumers
BENCHMARK(BM_ProducerConsumer)->Args({50, 10, 10});
BENCHMARK(BM_ProducerConsumer)->Args({100, 20, 20});

BENCHMARK_MAIN();
