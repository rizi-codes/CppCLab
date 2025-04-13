#include "concurrency/thread_safe_print.h"
#include <gtest/gtest.h>
#include <thread>

TEST(PrintThreadSafeTest, SimplePrintTest) {
  EXPECT_NO_THROW(thread_safe_print::print("Testing", 123, true));
}

TEST(PrintThreadSafeTest, ThreadSafetyTest) {
  auto worker = []() {
    for (int i = 0; i < 10; ++i) {
      thread_safe_print::print("Thread message ", i);
    }
  };

  std::thread t1(worker);
  std::thread t2(worker);
  t1.join();
  t2.join();

  SUCCEED();
}
