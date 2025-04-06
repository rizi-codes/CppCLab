#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

static mutex print_m;

void inc(int &number, mutex &op_m) {
    lock_guard<mutex> lock(op_m);
    number++;
}

void dec(int &number, mutex &op_m) {
    lock_guard<mutex> lock(op_m);
    number--;
}

