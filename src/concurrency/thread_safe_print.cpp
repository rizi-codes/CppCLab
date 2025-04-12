#include "concurrency/thread_safe_print.h"
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

std::mutex thread_safe_print::mtx;
