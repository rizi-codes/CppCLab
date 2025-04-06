#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

void print_guard(const char *str, int id, mutex &m) {
    lock_guard<mutex> lock(m);
    cout << str << " from thread : " << id << endl;
}

void print(const char *str, int id, mutex &m) {
    m.lock();
    cout << str << " from thread : " << id << endl;
    m.unlock();
}
