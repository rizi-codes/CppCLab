#include <iostream>
#include <thread>

#include "concurrency/PrintThreadSafe.h"

using namespace std;

int main(int argc, char *argv[]) {
    std::thread t1([]() {
        PrintThreadSafe::print("Hello from thread ", 1, "!");
    });

    std::thread t2([]() {
        PrintThreadSafe::print("Another message from thread ", 2, ":", 3.14);
    });

    PrintThreadSafe::print("Hello from the main thread!");

    t1.join();
    t2.join();

    return 0;
}
