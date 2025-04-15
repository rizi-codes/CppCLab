#include "concurrency/thread_safe_print.h"
#include "concurrency/thread_safe_stack.h"
#include "util/random_generator.h"
#include "gtest/gtest.h"

#include <vector>

TEST(thread_safe_stack_test, test1) {
  thread_safe_stack<int> stack;
  random_generator rng;

  const int readers_number = 10;
  const int writers_number = 10;
  const int reader_read = 2;
  const int writer_write = 3;

  std::vector<std::thread> readers;
  std::vector<std::thread> writers;

  for (int i = 0; i < readers_number; i++) {
    readers.emplace_back([&stack, reader_read, &rng] {
      for (int j = 0; j < reader_read; j++) {
        int data = stack.pop();
        thread_safe_print::print("Pop: ", data);
        int sleep_time = rng.nextInt(10, 50);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
      }
    });
  }

  for (int i = 0; i < writers_number; i++) {
    writers.emplace_back([&stack, writer_write, &rng] {
      for (int j = 0; j < writer_write; j++) {
        int data = rng.nextInt(1, 30);
        stack.push(data);
        thread_safe_print::print("Push: ", data);
        int sleep_time = rng.nextInt(20, 60);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
      }
    });
  }

  for (std::thread &t : readers) {
    t.join();
  }

  for (std::thread &t : writers) {
    t.join();
  }
}
