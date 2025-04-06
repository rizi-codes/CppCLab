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

int main(int argc, char *argv[]) {
    mutex m;

    cout << "print using locks on mutext:" << endl;

    thread threads_v1[3];
    for (int id = 0; id < 3; id++) {
        threads_v1[id] = thread (print, "Message", id, ref(m));
    }

    for (int id = 0; id < 3; id++) {
        threads_v1[id].join();
    }

    cout << "print using lock_guard:" << endl;

    thread threads_v2[3];
    for (int id = 0; id < 3; id++) {
        threads_v2[id] = thread (print_guard, "Message", id, ref(m));
    }

    for (int id = 0; id < 3; id++) {
        threads_v2[id].join();
    }
    
    return 0;
}
