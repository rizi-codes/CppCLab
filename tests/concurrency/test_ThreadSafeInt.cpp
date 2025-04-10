#include "concurrency/ThreadSafeInt.h"
#include "util/RandomGenerator.h"
#include "gtest/gtest.h"

#include <vector>

TEST(ThreadSafeIntTest, MultipleReaderWriter) {
  ThreadSafeInt threadSafeInt(0);
  RandomGenerator rng;

  const int numberOfReaders = 50;
  const int numberOfWriters = 40;
  const int numberOfReadsPerThread = 5;
  const int numberOfWritesPerThread = 5;

  std::vector<std::thread> readers;
  std::vector<std::thread> writers;

  for (int i = 0; i < numberOfReaders; ++i) {
    readers.emplace_back([&threadSafeInt, numberOfReadsPerThread, &rng] {
      for (int j = 0; j < numberOfReadsPerThread; ++j) {
        threadSafeInt.readInt();
        int sleepTime = rng.nextInt(10, 60);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
      }
    });
  }

  for (int i = 0; i < numberOfWriters; ++i) {
    writers.emplace_back([&threadSafeInt, &rng, numberOfWritesPerThread] {
      for (int j = 0; j < numberOfWritesPerThread; ++j) {
        int number = rng.nextInt(1, 40);
        threadSafeInt.writeInt(number);
        int sleepTime = rng.nextInt(20, 40);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
      }
    });
  }

  for (auto &t : readers) {
    t.join();
  }

  for (auto &t : writers) {
    t.join();
  }
}
