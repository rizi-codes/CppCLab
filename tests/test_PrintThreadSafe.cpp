#include <gtest/gtest.h>
#include "concurrency/PrintThreadSafe.h"
#include <thread>

TEST(PrintThreadSafeTest, SimplePrintTest) {
    EXPECT_NO_THROW(PrintThreadSafe::print("Testing", 123, true));
}

TEST(PrintThreadSafeTest, ThreadSafetyTest) {
    auto worker = []() {
        for (int i = 0; i < 10; ++i) {
            PrintThreadSafe::print("Thread message ", i);
        }
    };

    std::thread t1(worker);
    std::thread t2(worker);
    t1.join();
    t2.join();

    SUCCEED();
}

