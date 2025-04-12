#include "concurrency/thread_safe_int.h"
#include "util/random_generator.h"
#include "gtest/gtest.h"

#include <vector>

TEST(thread_safe_intTest, MultipleReaderWriter) {
  thread_safe_int thread_safe_int(0);
  random_generator rng;

  const int numberOfReaders = 50;
  const int numberOfWriters = 40;
  const int numberOfReadsPerThread = 5;
  const int numberOfWritesPerThread = 5;

  std::vector<std::thread> readers;
  std::vector<std::thread> writers;

  for (int i = 0; i < numberOfReaders; ++i) {
    readers.emplace_back([&thread_safe_int, numberOfReadsPerThread, &rng] {
      for (int j = 0; j < numberOfReadsPerThread; ++j) {
        thread_safe_int.readInt();
        int sleepTime = rng.nextInt(10, 60);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
      }
    });
  }

  for (int i = 0; i < numberOfWriters; ++i) {
    writers.emplace_back([&thread_safe_int, &rng, numberOfWritesPerThread] {
      for (int j = 0; j < numberOfWritesPerThread; ++j) {
        int number = rng.nextInt(1, 40);
        thread_safe_int.writeInt(number);
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
